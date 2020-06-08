
//Fichier Katana.H

#include "Wire.h"
#define SLAVE_ADDRESS 0x16  //initialisation de l’Arduino avec l’adresse 0x16

#define CInterupteur_PIN 10 // Interrupteur Katana
#define SLed_PIN 11         // Led de contrôle
#define SKatana_PIN  12     //Relai Katana

#define DEBOUNCE 2000           // Temps de déparasitage (debounce time), a augmenter si la sortie clignote.
int sd_reading = HIGH;          //Valeur actuelle du capteur
int sd_previous = HIGH;       //Valeur précédente du capteur
long ms_time = 0;               //Dernière fois que le statut du mécanisme a changé



class Katana{

  private : 
    bool S_Katana;
    bool S_Led;
    bool C_Interupteur;
    bool mechanism_status;

 public : 

 bool actuator[2]={S_Katana, S_Led};
 bool sensor[1] = {C_Interupteur};

 public : 

 bool getMechanism_status();
 void setMechanism_status(bool ms);


    public : 
      Katana();
      void setupMechanism();
      void execute();

};


//Fichier Katana.CPP

Katana::Katana(){
  S_Katana = false;
  S_Led = false;
  C_Interupteur = false;
  mechanism_status = false;
}

bool Katana::getMechanism_status(){
  return mechanism_status;  //Retourner si le mécanisme a ét fait ou non
}

void Katana::setMechanism_status(bool ms){
  mechanism_status = ms; //Affiche le temps de la dernière actualisation
}

//SETUP
void Katana::setupMechanism(){

 pinMode(CInterupteur_PIN , INPUT_PULLUP);     //On initialise le pin de l'interrupteur

 pinMode(SLed_PIN, OUTPUT);            //On initialise le pin de la led
  if (S_Led = false){               //Suivant la valeur de l'attribut
    digitalWrite(SLed_PIN , LOW);       //On éteint la led par défaut
  }else{
    digitalWrite(SLed_PIN , HIGH);        //On allume la led par défaut
    }
    
    pinMode(SKatana_PIN, OUTPUT);          //On initialise le pin du relais de l'électroaimant du Katana
  if (S_Katana = false){               //Suivant la valeur de l'attribut
    digitalWrite(SKatana_PIN, LOW);       //On active le relais de l'électroaimant par défaut
  }else{
    digitalWrite(SKatana_PIN, HIGH);      //On désactive le relais de l'électroaimant par défaut
}
}

void Katana::execute(){

sd_reading = digitalRead(CInterupteur_PIN); // Lis l'état de l'interrupteur

   //on tient à vérifier si il y a eu un changement de position ou un parasite (bille qui trésaute)...
  if (sd_reading != sd_previous) { // Remettre la minuterie/timer de déparasitage à 0
    ms_time = millis();
  
  sd_previous = sd_reading;
  
  if (sd_reading == LOW
  && (millis() - ms_time) > ((DEBOUNCE)/2)){      //On vérifie s'il y a eu un changement de position positif
      
    C_Interupteur = true;             //On fixe la valeur de l'attribut capteur
      
    if (mechanism_status == false) {        //Si il y a eu le premier changement de position
        
      S_Katana = true;              //On active l'électroaimant du katana        
      S_Led = true;               //On allume la led verte    
      mechanism_status = true;          //On valide le mécanisme
    } 
  }else{                        //Si il n'y a pas eu de changement de position positif
  
    C_Interupteur = false;              //On fixe la valeur de l'attribut capteur
   
  }
 if ( S_Katana == true ){             //Pour désactiver l'electroaimant du Katana
    delay(100);                   //On attend 0.1 seconde
    digitalWrite(SKatana_PIN, HIGH);        //On désactive l'electroaimant du Katana
    delay(500);                  //On attend 0,5 seconde
    digitalWrite(SKatana_PIN, LOW);         //On réactive l'electroaimant
    delay(4000);                  //On attend 4 secondes
    S_Katana = false;               //On change la valeur de l'attribut
  }

  
    if ( S_Led == true ){               //Pour allumer la led témoin
    delay(100);                   //On attend 0.1 seconde
    digitalWrite(SLed_PIN, LOW);         //On allume la led de contrôle
  }else{                        //Pour éteindre la led témoin
    delay(100);                   //On attend 0.1 seconde
    digitalWrite(SLed_PIN, HIGH);          //On éteint la led de contrôle
  }
  
  if ( mechanism_status == false ){         //En cas de reset
    S_Led = false;                  //On change la valeur de l'attribut
    S_Katana = false;                  //On change la valeur de l'attribut
  }
}
}



//MAIN

Katana mechanism = Katana();

void execute_order(String order){
  
  Serial.print("Order received : ");
  Serial.println(order);//412221
  
  if(order[1] == '1'){                //Si le 2eme caractère est 1
    mechanism.setMechanism_status(true);      //On valide le mécanisme
  }else if(order[1] == '0'){              //Si le 2eme caractère est 0
    mechanism.setMechanism_status(false);     //On invalide le mécanisme
  }
    
  for(int i=2; i<sizeof(order); i++) {        //Pour chaque actionneur
    if(order[i] == '1'){              //Si le caractère est 1
      mechanism.actuator[i-1] = true;       //On valide l'actionneur
    }else if(order[i] == '0'){            //Si le caractère est 0
      mechanism.actuator[i-1] = false;      //On invalide l'actionneur
    }
  }
}

void receive_order(int numBytes) {
  String data_received;
  
  while(Wire.available() > 0) {           //Tant que le message i2c reçu n'est pas fini
    char c = Wire.read();             //On lit le caractère suivant du message sur le bus i2c
    data_received += String(c);           //On ajoute le caractère du message aux données reçus
  }
  
  if(data_received != "2") {              //Si les données reçues sont bien un message d'ordre
    execute_order(data_received);         //On exécute les ordres du message d'ordre
  }
}

String getMessagei2c() {
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

  for(int i=0; i<sizeof(mechanism.sensor); i++){    //Pour chaque capteur du mécanisme
    if (mechanism.sensor[i] == true){       //Si le capteur est validé
      sd_I2Cmessage += "T";           //On ajoute T au message i2c
    }else{                      //Si le capteur est invalidé
      sd_I2Cmessage += "F";           //On ajoute F au message i2c
    }
  }
  
  I2Cmessage = ms_I2Cmessage + as_I2Cmessage + sd_I2Cmessage;//msFasFFFFsdF
  
  Serial.print("Message send to Raspberry : ");
  Serial.println(I2Cmessage);
  
  return I2Cmessage;
}

void send_status() {
  Wire.write(getMessagei2c().c_str());  //On écrit le message i2c dans l'objet Wire
}

void setup() {
  Serial.begin(9600);
  Wire.begin(SLAVE_ADDRESS);        //On indique à l'objet Wire l'adresse esclave utilisé par l'Arduino
  Wire.onRequest(send_status);      //On envoie le messagei2c sur le bus i2c
  Wire.onReceive(receive_order);      //On récupère le message s'ordre reçu sur le bus i2c via la fonction receive order
  mechanism.setupMechanism();       //On donne une configuration de base au mécanisme
}

void loop() {
  delay(100);               //On attends 0.1 seconde
  mechanism.execute();          //On exécute le mécanisme
}
