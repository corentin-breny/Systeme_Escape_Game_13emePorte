//Fichier Echec.h

#include "WIRE.H"
#define SLAVE_ADDRESS 0x12
#define C_EffetHall1_PIN A0 //Capteur à effet Hall 1
#define C_EffetHall2_PIN 2 //Capteur à effet Hall 2
#define S_LedR_PIN 3 //Led de sortie

int ECHECstate = HIGH; // Etat actuel de la broche de sortie (la ventouse HIGH maintiens de la ventouse fermée)
int readingECHEC;         // Contient la valeur lue sur la broche d'entrée
int previousECHEC = LOW;  // Contient la précédente valeur lue sur la broche d'entrée
long timeECHEC = 0;      // La dernière fois que la broche de sortie à changé d'état
long time = 0;      // La dernière fois que la broche de sortie à changé d'état 
long debounce = 2000;

class Echec{

  private :
    const int C_EffetHall1;
    const int C_EffetHall2;
    bool S_Echiquier;
    bool mecanism_status;

  public :
    bool actuator[1] = {S_Echiquier};
    int sensor[2] = {C_EffetHall2, C_EffetHall2};
    bool getMechanism_status();
    void setMechanism_status(bool ms);    

  public :
    Echec();
    void setupMecanism();
    void execute();
    
};

//Fichier Echec.cpp

Echec::Echec(){
  
  C_EffetHall_1 = false;
  C_EffetHall_2 = false;
  S_Echiquier = false;
  mecanism_status = false;
  
}

bool Echec::getMechanism_status(){
  return mechanism_status;
}

void Echec::setMechanism_status(bool ms){
  mechanism_status = ms;
}

void Echec::setupMechanism() {
  
  pinMode( 8, OUTPUT ); // Relais echec
  digitalWrite(8, HIGH);
  
  pinMode( 7, OUTPUT ); // Led controle echec
  digitalWrite(7, HIGH);

  pinMode(11, INPUT_PULLUP);

  digitalWrite(hallPin, HIGH);  // Activation résistance pullUP
  digitalWrite(hallPin2, HIGH);
 
}

void Echec::execute(){

  int pin1 = digitalRead(C_EffetHall_1);    // On lit les deux capteurs à effet Hall
  int pin2 = digitalRead(C_EffetHall_2);
  
  readingECHEC = pin1;

  if (ECHECstate == HIGH)   // Si ECHECstate est à HIGH, ça signifie que la ventouse est maintenue fermée
  {
    if (readingECHEC != previousECHEC) {    
      
      timeECHEC = millis();   // Remettre la minuterie/timer de déparasitage à 0
    }
    
    if ((millis() - timeECHEC) > debounce)    // Attendre que l'on ai dépassé le temps de déparasitage
    {
      
      if ((pin1 == LOW) && (pin2 == LOW))     // Si les deux pieces sont à la bonne place
      {  
        ECHECstate = LOW; // On valide l'enigme
      } else LEDstate = HIGH;
      
    previousECHEC = readingECHEC;     // Mémoriser la dernière lecture
    }  
  digitalWrite(7, not(ECHECstate));   // Écriture du statut sur la led (HIGH = allumé soit l'inverse de la ventouse)
  digitalWrite(8, ECHECstate);    // Écriture du statut sur la ventouse (LOW = on libere l'electroaimant)
  delay(500);
  digitalWrite(8, not(ECHECstate));
  }

  if ( mechanism_status == false ){          //En cas de reset
    S_Echiquier = false;                  //On change la valeur de l'attribut
  }
}

Echec mechanism = Echec();

void receive_order(int numBytes) {
  String data_received;
  
  while(Wire.available() > 0) {           //Tant que le message n'est pas fini
    char c = Wire.read();             //On lit le message
    data_received += String(c);
  }
  
  if(data_received != "2") {
    
    String order = data_received;
    Serial.print("Order received : ");
    Serial.println(order);//412221

    if(order[1] == '1'){              //Si le 2eme caractère est 1
      mechanism.setMechanism_status(true);    //On valide le mécanisme
    }else if(order[1] == '0'){            //Si le 2eme caractère est 0
      mechanism.setMechanism_status(false);   //On invalide le mécanisme
    }
    
    for(int i=2; i<sizeof(order); i++) {      //Pour chaque actionneur
      if(order[i] == '1'){            //Si le caractère est 1
        mechanism.actuator[i-1] = true;     //On valide l'actionneur
      }else if(order[i] == '0'){          //Si le caractère est 0
        mechanism.actuator[i-1] = false;    //On invalide l'actionneur
      }
    }
  }
}

void send_status() {
  String ms_I2Cmessage = "ms";
  String as_I2Cmessage = "as";
  String sd_I2Cmessage = "sd";
  String I2Cmessage;

  if(mechanism.getMechanism_status() == true){    //Si le mécanisme est validé
    ms_I2Cmessage += "T";             //On ajoute T au message i2c
  }else{                        //Si le mécanisme est invalide
    ms_I2Cmessage += "F";             //On ajoute F au message i2c
  }
  
  for(int i=0; i<sizeof(mechanism.actuator); i++){  //Pour chaque actionneur du mécanisme
    if (mechanism.actuator[i] == true){       //Si l'actionneur est validé
      as_I2Cmessage += "T";           //On ajoute T au message i2c
    }else{                      //Si l'actionneur est invalidé
      as_I2Cmessage += "F";           //On ajoute F au message i2c
    }
  }
  if(as_I2Cmessage.length() < 6){
    for(int i=as_I2Cmessage.length()-1; i<5; i++){  //Tant que le message est inférieur à 6 caractere
      as_I2Cmessage += "X";           //On ajoute X au message i2c
    }
  }

  /*//A COMMENTER SI LES CAPTEURS SONT DES VALEURS BOOLEAN
  for(int i=0; i<sizeof(mechanism.sensor); i++){    //Pour chaque capteur du mécanisme
    if (mechanism.sensor[i] == true){       //Si le capteur est validé
      sd_I2Cmessage += "T";           //On ajoute T au message i2c
    }else{                      //Si le capteur est invalidé
      sd_I2Cmessage += "F";           //On ajoute F au message i2c
    }
  }*/

  //A COMMENTER SI LES CAPTEURS SONT DES VALEURS NUMERIQUE
  for(int i=0; i<sizeof(sensor)/2; i++){        //Pour chaque capteur du mécanisme
    sd_I2Cmessage += sensor[i];           //On ajoute la valeur du capteur au message i2c
    sd_I2Cmessage += "X";             //Et on ajoute aussi X
  }
  
  I2Cmessage = ms_I2Cmessage + as_I2Cmessage + sd_I2Cmessage;//msFasFFFFsdF
  
  Wire.write(I2Cmessage.c_str());           //On envoie le message i2c
  Serial.print("Message send to Raspberry : ");
  Serial.println(I2Cmessage);
}

void setup() {
  Serial.begin(9600);
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receive_order);
  Wire.onRequest(send_status);
  mechanism.setupMechanism();
}

void loop() {
  delay(100);                     //On attends 0.1 seconde
  mechanism.execute();                //On exécute le mécanisme
}
