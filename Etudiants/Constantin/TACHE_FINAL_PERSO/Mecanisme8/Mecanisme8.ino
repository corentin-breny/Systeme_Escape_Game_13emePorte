//FICHIER RIZ H

#include "Wire.h"
#include "HX711.h"  //You must have this library in your arduino library folder
#define SLAVE_ADDRESS 0x19  //initialisation de l’Arduino avec l’adresse 0x19

#define STableau_PIN 6   //relais tableau
#define SLedV_PIN 4      //led verte
#define SLedR_PIN 5      //led rouge
#define CPoids_DOUT 3    //capteur de poids
#define CPoids_CLK 2     //capteur de poids
//Change this calibration factor as per your load cell once it is found you many need to vary it in thousands
#define calibration_factor 20180; //-106600 worked for my 40Kg max scale setup

HX711 scale(CPoids_DOUT, CPoids_CLK);
float sd_reading = 0;       //Valeur actuelle du capteur
int sd_previous = 0;     	//Valeur précédente du capteur

class Riz{

  private :
    bool S_Tableau;							//actionneur qui active/désactive l'électroaimant de la chute de tableau
    bool S_Led;								//actionneur qui active/désactive la led de controle
    int C_Poids;							//valeur mesuré par le capteur de poids
    bool mechanism_status;					//indique si le mécanisme est activé ou non

  public :
    bool actuator[2] = {S_Tableau, S_Led};	//tableau des actionneurs
    int sensor[1] = {C_Poids};				//tableau des capteurs
  
  public :
    bool getMechanism_status();				//récupérer l'état du mécanisme
    void setMechanism_status(bool ms);		//modifier l'état du mécanisme

  public :
    Riz();									//constructeur de la classe
    void setupMechanism();					//configuration de base du mécanisme
    void execute();							//méthode qui fait fonctionner le mécanisme
};

//FICHIER Riz CsPP

Riz::Riz(){
	S_Tableau = false;
	S_Led = false;
	C_Poids = 0;
	mechanism_status = false;
}

bool Riz::getMechanism_status(){
	return mechanism_status;
}

void Riz::setMechanism_status(bool ms){
	mechanism_status = ms;
}

void Riz::setupMechanism() {
	Serial.begin(9600);

	scale.set_scale();
	scale.tare(); 										//Reset "scale"

	pinMode(STableau_PIN, OUTPUT);
	digitalWrite(STableau_PIN, HIGH);
  
	pinMode(SLedV_PIN, OUTPUT); 
	digitalWrite(SLedV_PIN , LOW);

	pinMode(SLedR_PIN, OUTPUT);
	digitalWrite(SLedR_PIN, HIGH);
}

void Riz::execute(){
	scale.set_scale(calibration_factor); 				//On ajuste la balance au facteur d'étalonnage

    sd_reading = (scale.get_units() / 2.0); 			//On récupère une 1ere mesure du capteur de poids
    delay(1000);										//On attend 1 seconde
    float sd_reading_verif = (scale.get_units() / 2.0);	//On récupère une 2eme mesure du capteur de poids

    if ( (sd_reading_verif >= (sd_reading - 0.03)) 
	&& (sd_reading_verif <= (sd_reading + 0.03)) ) { 	//On vérifie que les 2 mesures sont quasi égales

		C_Poids = (int) sd_reading;						//On fixe la valeur de l'attribut capteur
		sd_previous = C_Poids;
		
		if ( (sd_reading >= 0.48) 
		&& (sd_reading <= 0.52 )
		&& mechanism_status == false ) {				//Si la mesure est comprise entre 0.48 et 0.52 pour la 1ere fois
									
			S_Led = true;								//On allume la led verte et on éteint la rouge	
			S_Tableau = true;							//On libère la chute du tableau			
			mechanism_status = true; 					//On valide le mécanisme		
		}
	}else{												//Si les 2 mesures ne sont pas quasi égales
		
        C_Poids = sd_previous;							//On fixe la valeur de l'attribut capteur
    }
		
	if ( S_Led == true ){								//Pour allumer la led verte et éteindre la rouge
		delay(100);										//On attend 0.1 seconde
		digitalWrite(SLedV_PIN, HIGH);  				//On allume la Led Verte
		digitalWrite(SLedR_PIN, LOW);     				//On éteint la Led Rouge
	}else{												//Pour allumer la led rouge et éteindre la verte
		delay(100);										//On attend 0.1 seconde
		digitalWrite(SLedR_PIN, HIGH);  				//On allume la Led Rouge
		digitalWrite(SLedV_PIN, LOW);     				//On éteint la Led Verte
	}
	
	if ( S_Tableau == true ){							//Pour libérer la chute du tableau
		delay(100);										//On attend 0.1 seconde
		digitalWrite(STableau_PIN, LOW);   				//On désactive l'electroaimant du tableau
		delay(200);										//On attend 0.2 seconde
		digitalWrite(STableau_PIN, HIGH);  				//On active l'electroaimant du tableau
		delay(500);										//On attend 0.5 seconde
		digitalWrite(STableau_PIN, LOW);   				//On désactive l'electroaimant du tableau
		delay(200);										//On attend 0.2 seconde
		digitalWrite(STableau_PIN, HIGH);  				//On active l'electroaimant du tableau
		delay(500);										//On attend 0.5 seconde
		digitalWrite(STableau_PIN, LOW);   				//On désactive l'electroaimant du tableau
		delay(200);										//On attend 0.2 seconde
		digitalWrite(STableau_PIN, HIGH);  				//On active l'electroaimant du tableau
		delay(4000); 									//On attend 4 secondes
		S_Tableau = false;								//On change la valeur de l'attribut
	}
	
	if ( mechanism_status == false ){					//En cas de reset
		S_Led = false;									//On change la valeur de l'attribut
	}
}


//MAIN
Riz mechanism = Riz();									//On instancie un objet de type Riz

void execute_order(String order){
	
	Serial.print("Order received : ");
	Serial.println(data_received);//412221
	
	if(order[1] == '1'){								//Si le 2eme caractère est 1
		mechanism.setMechanism_status(true);			//On valide le mécanisme
	}else if(order[1] == '0'){							//Si le 2eme caractère est 0
		mechanism.setMechanism_status(false);			//On invalide le mécanisme
	}
	  
	for(int i=2; i<sizeof(order); i++) {				//Pour chaque actionneur
		if(order[i] == '1'){							//Si le caractère est 1
			mechanism.actuator[i-1] = true;				//On valide l'actionneur
		}else if(order[i] == '0'){						//Si le caractère est 0
			mechanism.actuator[i-1] = false;			//On invalide l'actionneur
		}
	}
}

void receive_order(int numBytes) {
	String data_received;
  
	while(Wire.available() > 0) {						//Tant que le message i2c reçu n'est pas fini
		char c = Wire.read();							//On lit le caractère suivant du message sur le bus i2c
		data_received += String(c);						//On ajoute le caractère du message aux données reçus
	}
  
	if(data_received != "2") {							//Si les données reçues sont bien un message d'ordre
		execute_order(data_received);					//On exécute les ordres du message d'ordre
	}
}

void getMessagei2c() {
	String ms_I2Cmessage = "ms";
	String as_I2Cmessage = "as";
	String sd_I2Cmessage = "sd";
	String I2Cmessage;

	if(mechanism.getMechanism_status() == true){		//Si le mécanisme est validé
		ms_I2Cmessage += "T";							//On ajoute T au message i2c
	}else{												//Si le mécanisme est invalide
		ms_I2Cmessage += "F";							//On ajoute F au message i2c
	}
  
	for(int i=0; i<sizeof(mechanism.actuator); i++){	//Pour chaque actionneur du mécanisme
		if (mechanism.actuator[i] == true){				//Si l'actionneur est validé
			as_I2Cmessage += "T";						//On ajoute T au message i2c
		}else{											//Si l'actionneur est invalidé
			as_I2Cmessage += "F";						//On ajoute F au message i2c
		}
	}
	if(as_I2Cmessage.length() < 6){
		for(int i=as_I2Cmessage.length()-1; i<5; i++){	//Tant que le message est inférieur à 6 caractere
			as_I2Cmessage += "X";						//On ajoute X au message i2c
		}
	}

	/*//A DECOMMENTER SI LES CAPTEURS SONT DES VALEURS BOOLEAN
	for(int i=0; i<sizeof(mechanism.sensor); i++){		//Pour chaque capteur du mécanisme
		if (mechanism.sensor[i] == true){				//Si le capteur est validé
			sd_I2Cmessage += "T";						//On ajoute T au message i2c
		}else{											//Si le capteur est invalidé
			sd_I2Cmessage += "F";						//On ajoute F au message i2c
	}*/

	//A DECOMMENTER SI LES CAPTEURS SONT DES VALEURS NUMERIQUE
	for(int i=0; i<sizeof(sensor)/2; i++){				//Pour chaque capteur du mécanisme
		sd_I2Cmessage += sensor[i];						//On ajoute la valeur du capteur au message i2c
		sd_I2Cmessage += "X";							//Et on ajoute aussi X
	}
  
	I2Cmessage = ms_I2Cmessage + as_I2Cmessage + sd_I2Cmessage;//msFasFFFFsdF
	
	Serial.print("Message send to Raspberry : ");
	Serial.println(I2Cmessage);
	
	return I2Cmessage.c_str()
}

void send_status() {
	
	Wire.write(getMessagei2c());			//On écris le message i2c dans l'objet Wire
}

void setup() {
	Serial.begin(9600);
	Wire.begin(SLAVE_ADDRESS);				//On indique à l'objet Wire l'adresse esclave utilisé par l'Arduino
	Wire.onReceive(receive_order);			//On récupère le message s'ordre reçu sur le bus i2c via la fonction receive order
	Wire.onRequest(send_status);			//On envoie le messagei2c sur le bus i2c
	mechanism.setupMechanism();				//On donne une configuration de base au mécanisme
}

void loop() {
	delay(100);								//On attends 0.1 seconde
	mechanism.execute();					//On exécute le mécanisme
}
