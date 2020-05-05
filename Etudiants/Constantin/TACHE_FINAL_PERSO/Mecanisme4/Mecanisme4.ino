//FICHIER Feu H

#include "Wire.h"
#define SLAVE_ADDRESS 0x15  //initialisation de l’Arduino avec l’adresse 0x15

#define CInterupteur_PIN 8  	//interupteur a clef
#define SLed_PIN 9          	//led controle
#define SDragon_PIN 10      	//relais dragon
#define SFumee_PIN 11       	//relais fumee
#define DEBOUNCE 500

int sd_reading = HIGH;        	//Valeur actuelle du capteur
int sd_previous = HIGH;     	//Valeur précédente du capteur
long ms_time = 0;             	//Dernière fois que le statut du mécanisme a changé

class Feu{

  private :
    bool S_Dragon;							//actionneur qui active/désactive l'électroaimant de la ventouse dragon
    bool S_Fumee;							//actionneur qui active/désactive la fumée
    bool S_Led;								//actionneur qui active/désactive la led de controle
    bool S_Feu;								//actionneur de l'élément FEU sur la tablette des 4 éléments
    bool C_Interupteur;						//état de la position détecter par l'interupteur à clef
    bool mechanism_status;					//indique si le mécanisme est activé ou non

  public :
    bool actuator[4] = {S_Dragon, S_Fumee, S_Led, S_Feu};//tableau des actionneurs
    bool sensor[1] = {C_Interupteur};		//tableau des capteurs
      
  public :
    bool getMechanism_status();				//récupérer l'état du mécanisme
    void setMechanism_status(bool ms);		//modifier l'état du mécanisme

  public :
    Feu();									//constructeur de la classe
    void setupMechanism();					//configuration de base du mécanisme
    void execute();							//méthode qui fait fonctionner le mécanisme
    
};

//FICHIER FEU CPP

Feu::Feu(){
	S_Dragon = false;
	S_Fumee = false;
	S_Led = false;
	S_Feu = false;
	C_Interupteur = false;
	mechanism_status = false;
}

bool Feu::getMechanism_status(){
	return mechanism_status;
}

void Feu::setMechanism_status(bool ms){
	mechanism_status = ms;
}

void Feu::setupMechanism() {
	pinMode(CInterupteur_PIN , INPUT_PULLUP); 
  
	pinMode(SLed_PIN, OUTPUT); 
	digitalWrite(SLed_PIN , LOW);
    
	pinMode(SDragon_PIN, OUTPUT);
	digitalWrite(SDragon_PIN, HIGH);
  
	pinMode(SFumee_PIN, OUTPUT);
	digitalWrite(SFumee_PIN, HIGH);
}

void Feu::execute(){
	sd_reading = digitalRead(CInterupteur_PIN);   		//On récupère la valeur du capteur intérupteur à clef

	//on tient à vérifier si il y a eu un changement de position ou un parasite (bille qui trésaute)... 
	if (sd_reading != sd_previous) {
		ms_time = millis();								//On remet le timer de déparasitage à 0
	}
	
	sd_previous = sd_reading;
	
	if (sd_reading == LOW
	&& (millis() - ms_time) > ((DEBOUNCE)/2)){ 			//On vérifie s'il y a eu un changement de position positif
			
		C_Interupteur = true;							//On fixe la valeur de l'attribut capteur
			
		if (mechanism_status == false) {				//Si il y a eu le premier changement de position
			  
			S_Dragon = true;							//On active l'électroaimant de la ventouse dragon		
			S_Fumee = true;								//On active la fumée			
			S_Led = true;								//On allume la led verte		
			S_Feu = true;								//On allume l'element FEU des 4 éléments		
			mechanism_status = true; 					//On valide le mécanisme
		} 
	}else{												//Si il n'y a pas eu de changement de position positif
	
		C_Interupteur = false;							//On fixe la valeur de l'attribut capteur
	}	
	
	if ( S_Dragon == true ){							//Pour désactiver l'electroaimant de la ventouse dragon
		delay(100);										//On attend 0.1 seconde
		digitalWrite(SDragon_PIN, LOW); 				//On désactive l'electroaimant de la trappe dragon
		delay(1000);									//On attend 1 seconde
		digitalWrite(SDragon_PIN, HIGH);				//On réactive l'electroaimant
		delay(4000); 									//On attend 4 secondes
		S_Dragon = false;								//On change la valeur de l'attribut
	}
	
	if ( S_Fumee == true ){								//Pour activer la fumée
		delay(100);										//On attend 0.1 seconde
		digitalWrite(SFumee_PIN, LOW); 					//On allume la fumée
		delay(5000);									//On attend 5 secondes
		digitalWrite(SFumee_PIN, HIGH);					//On éteint la fumée
		S_Fumee = false;								//On change la valeur de l'attribut
	}
	
	if ( S_Led == true ){								//Pour allumer la led témoin
		delay(100);										//On attend 0.1 seconde
		digitalWrite(SLed_PIN, HIGH);					//On allume la led de contrôle
	}else{												//Pour éteindre la led témoin
		delay(100);										//On attend 0.1 seconde
		digitalWrite(SLed_PIN, LOW);					//On éteint la led de contrôle
	}
	
	if ( mechanism_status == false ){					//En cas de reset
		S_Led = false;									//On change la valeur de l'attribut
		S_Feu = false;									//On change la valeur de l'attribut
	}
}

//MAIN
Feu mechanism = Feu();									//On instancie un objet de type Feu

void execute_order(String order){
	
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
  
	while(Wire.available() > 0) {						//Tant que le message n'est pas fini
		char c = Wire.read();							//On lit le message
		data_received += String(c);
	}
  
	if(data_received != "2") {
	  
		String order = data_received;
		Serial.print("Order received : ");
		Serial.println(order);//412221

		execute_order(order);							//On exécute les ordres du message d'ordre
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

	//A DECOMMENTER SI LES CAPTEURS SONT DES VALEURS BOOLEAN
	for(int i=0; i<sizeof(mechanism.sensor); i++){		//Pour chaque capteur du mécanisme
		if (mechanism.sensor[i] == true){				//Si le capteur est validé
			sd_I2Cmessage += "T";						//On ajoute T au message i2c
		}else{											//Si le capteur est invalidé
			sd_I2Cmessage += "F";						//On ajoute F au message i2c
		}
	}

	/*//A DECOMMENTER SI LES CAPTEURS SONT DES VALEURS NUMERIQUE
	for(int i=0; i<sizeof(sensor)/2; i++){				//Pour chaque capteur du mécanisme
		sd_I2Cmessage += sensor[i];						//On ajoute la valeur du capteur au message i2c
		sd_I2Cmessage += "X";							//Et on ajoute aussi X
	}*/
  
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
	Wire.onReceive(receive_order);			//On récupère le message s'ordre envoyé sur le bus i2c
	Wire.onRequest(send_status);			//On envoie le messagei2c sur le bus i2c
	mechanism.setupMechanism();				//On donne une configuration de base au mécanisme
}

void loop() {
	delay(100);								//On attends 0.1 seconde
	mechanism.execute();					//On exécute le mécanisme
}