//Fichier Katana.H

#include "Wire.h"
#define SLAVE_ADDRESS 0x16  //initialisation de l’Arduino avec l’adresse 0x16

#define CInterrupteur_PIN 10 // Interrupteur Katana
#define SLed_PIN 11 // Led de contrôle
#define SKatana_PIN  12    //Relai Katana



int statekatana = HIGH; // Etat actuel de la broche de sortie (la LED)
int readingkatana;         // Contient la valeur lue sur la broche d'entrée
int previouskatana = LOW;  // Contient la précédente valeur lue sur la broche d'entrée
int firstkatana = 0;
long timeKatana;


class Katana{

  private : 
    bool S_Katana;
    bool S_Led;
    bool C_Interrupteur;
    bool mecanism_status;

 public : 

 bool actuator[2]={S_Katana, S_Led};
 bool sensor[1] = {C_Interrupteur};

 public : 

 bool getMechanism_status();
 void setMechanism_status(bool ms);


    public : 
      Katana();
      void setupMecanism();
      void execute();
      void receive_order();
      void send_status();
};


//Fichier Katana.CPP

Katana::Katana(){
  S_Katana = false;
  S_Led = false;
  C_Interrupteur = false;
  mecanism_status = false;
}

bool Katana::getMechanism_status(){
  return mechanism_status;  //Retourner si le mécanisme a ét fait ou non
}

void Katana::setMechanism_status(bool ms){
  mechanism_status = ms; //Affiche le temps de la dernière actualisation
}

//SETUP
void Katana::setupMecanism(){

 pinMode(CInterrupteur_PIN 10, INPUT_PULLUP);
 pinMode(SLed_PIN 11, OUTPUT);
 
 pinMode(SKatana_PIN 12, OUTPUT);
 digitalWrite(SKatana_PIN 12, HIGH); // relai doigt



void Katana::execute(){

  readingkatana = digitalRead(CInterruppteur_PIN ); // Lis l'état de l'interrupteur

  //on tient à vérifier si il y a eu un changement de position ou un parasite (bille qui trésaute)...
  if (readingkatana != previouskatana) { // Remettre la minuterie/timer de déparasitage à 0
    timeKatana = millis();
  }

  if ((millis() - timeKatana) > ((debounce))) { //On vérifie s'il y a eu un changement de position positif
    if (readingkatana == 0) {
      if (firstkatana == 0) {
        statekatana = LOW;
        digitalWrite(SKatana_PIN , LOW); // On désactive le relai katana
        delay(500); // attendre 0,5 seconde
        digitalWrite(SKatana_PIN , HIGH); // On réactive le relai katana
        firstkatana = 1; // On change la valeur du katana
      }
    }
    else {
      firstkatana = 0 ;
    }
  }
  digitalWrite(SLed_PIN 11, not(statekatana));
  previouskatana = readingkatana;
}
//MAIN

Katana Mecanisme = Katana();

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

  //A DECOMMENTER SI LES CAPTEURS SONT DES VALEURS BOOLEAN
  for(int i=0; i<sizeof(mechanism.sensor); i++){    //Pour chaque capteur du mécanisme
    if (mechanism.sensor[i] == true){       //Si le capteur est validé
      sd_I2Cmessage += "T";           //On ajoute T au message i2c
    }else{                      //Si le capteur est invalidé
      sd_I2Cmessage += "F";           //On ajoute F au message i2c
    }
  }

  //A DECOMMENTER SI LES CAPTEURS SONT DES VALEURS NUMERIQUE
  /*for(int i=0; i<sizeof(sensor)/2; i++){        //Pour chaque capteur du mécanisme
    sd_I2Cmessage += sensor[i];           //On ajoute la valeur du capteur au message i2c
    sd_I2Cmessage += "X";             //Et on ajoute aussi X
  }*/
  
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
