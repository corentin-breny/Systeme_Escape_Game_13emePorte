//Fichier LionB.h

#include "Wire.h"
#define SLAVE_ADDRESS 0x13
#define CEffetHall1_PIN A0 //Capteur à effet Hall 1
#define SLed_PIN 10 //Led de sortie
#define SLion_PIN 3 //Led de sortie
#define DEBOUNCE 2000

int sd_reading = HIGH;        //Valeur actuelle du capteur
int sd_previous = HIGH;       //Valeur précédente du capteur
long ms_time = 0;

class LionB {

  private :
    bool C_EffetHall_1;
    bool S_Lion;
    bool S_Led;
    bool mecanism_status;

  private :
    bool actuator[2] = {S_Lion, S_Led};
    bool sensor[1] = {C_EffetHall_1};
    bool getMechanism_status();
    void setMechanism_status(bool ms);

  public :
    LionB();
    void setupMechanism();
    void execute();
};

//Fichier LionB.cpp

LionB::LionB(){  
  C_EffetHall_1 = false;
  S_LedR = false;
  mecanism_status = false;
}

bool Echec::getMechanism_status(){
  return mechanism_status;
}

void Echec::setMechanism_status(bool ms){
  mechanism_status = ms;
}

void LionB::setupMechanism() {
  
  pinMode(SLed_PIN, OUTPUT); // vers led controle lionb
  digitalWrite(SLed_PIN, HIGH);
  
  pinMode(SLion_PIN, OUTPUT); // Vers relais lionb
  digitalWrite(SLion_PIN, HIGH);
  
  pinMode(C_EffetHall, INPUT); // pin 6
  digitalWrite(C_EffetHall, HIGH);

  digitalWrite(hallPin, HIGH);  // Activation résistance pullUP
 
}

void LionB::execute(){


  sd_reading = digitalRead(CEffetHall1_PIN);       //On récupère la valeur du capteur intérupteur à clef

  //on tient à vérifier si il y a eu un changement de position ou un parasite (bille qui trésaute)... 
  if (sd_reading != sd_previous) {
    ms_time = millis();               //On remet le timer de déparasitage à 0
  }
  
  sd_previous = sd_reading;
  
  if (sd_reading == LOW
  && (millis() - ms_time) > DEBOUNCE){      //On vérifie s'il y a eu un changement de position positif
      
    C_EffetHall_1 = true;             //On fixe la valeur de l'attribut capteur
      
    if (mechanism_status == false) {        //Si il y a eu le premier changement de position
        
      S_Lion = true;             //On active l'électroaimant de la ventouse dragon                        
      S_Led = true;                   //On allume la led rouge                     
      mechanism_status = true;        //On valide le mécanisme
    } 
  }else{                        //Si il n'y a pas eu de changement de position positif
  
    C_EffetHall_1 = false;             //On fixe la valeur de l'attribut capteur
  } 
  
  if ( S_Lion == true ){              //Pour désactiver l'electroaimant de la ventouse dragon
    S_Lion = LOW;   //Ce qui valide la réussite de l'énigme
    digitalWrite(3, S_Lion);    //reset pour defaire le solenoide
    ms_time = millis();
    S_Led = HIGH;    //La led correspondante sur le panneau du superviseur est allumée
  }
  
  if ( S_Led == true ){                   //Pour allumer la led témoin
    delay(100);                           //On attend 0.1 seconde
    digitalWrite(SLed_PIN, HIGH);         //On allume la led de contrôle
  }else{                                  //Pour éteindre la led témoin
    delay(100);                           //On attend 0.1 seconde
    digitalWrite(SLed_PIN, LOW);          //On éteint la led de contrôle
  }
  
  if ( mechanism_status == false ){         //En cas de reset
    S_Led = false;                  //On change la valeur de l'attribut
  }

}

LionB mechanism = LionB();

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
