//Fichier Echec.h

#include "Wire.h"

#define SLAVE_ADDRESS 0x12
#define CEffetHall1_PIN A0 //Capteur à effet Hall 1
#define CEffetHall2_PIN 2 //Capteur à effet Hall 2
#define SLed_PIN 7 //Led de sortie
#define SEchiquier_PIN 8 //Led de sortie
#define DEBOUNCE 2000

int sd_reading = HIGH;        //Valeur actuelle du capteur
int sd_previous = HIGH;       //Valeur précédente du capteur
long ms_time = 0;
int pin2 = HIGH;
 
class Echec{

  private :
    bool C_EffetHall1;
    bool C_EffetHall2;
    bool S_Echiquier;
    bool S_Led;
    bool mechanism_status;

  public :
    bool actuator[2] = {S_Echiquier, S_Led};
    int sensor[2] = {C_EffetHall2, C_EffetHall2};
    bool getMechanism_status();
    void setMechanism_status(bool ms);    

  public :
    Echec();
    void setupMechanism();
    void execute();
};

//Fichier Echec.cpp

Echec::Echec(){
  
  C_EffetHall1 = false;
  C_EffetHall2 = false;
  S_Echiquier = false;
  S_Led = false;
  mechanism_status = false;
  
}

bool Echec::getMechanism_status(){
  return mechanism_status;
}

void Echec::setMechanism_status(bool ms){
  mechanism_status = ms;
}

void Echec::setupMechanism() {

  digitalWrite(CEffetHall1_PIN, HIGH);  // Activation résistance pullUP
  digitalWrite(CEffetHall2_PIN, HIGH);

  pinMode(SEchiquier_PIN, OUTPUT);            //On initialise le pin du relais de l'électroaimant de la ventouse dragon
  if (S_Echiquier = false){                   //Suivant la valeur de l'attribut
    digitalWrite(SEchiquier_PIN , LOW);       //On active le relais de l'électroaimant par défaut
  }else{
    digitalWrite(SEchiquier_PIN , HIGH);      //On désactive le relais de l'électroaimant par défaut
    }
  
  pinMode(SLed_PIN, OUTPUT);        //On initialise le pin du relais de l'électroaimant de la ventouse dragon
  if (S_Led = false){               //Suivant la valeur de l'attribut
    digitalWrite(SLed_PIN, LOW);    //On éteint la led par défaut
  }else{
    digitalWrite(SLed_PIN, HIGH);   //On allume la led par défaut
    }
}

void Echec::execute(){

  sd_reading = digitalRead(CEffetHall1_PIN);       //On récupère la valeur du capteur intérupteur à clef
  pin2 = digitalRead(CEffetHall2_PIN);       //On récupère la valeur du capteur intérupteur à clef

  //on tient à vérifier si il y a eu un changement de position ou un parasite (bille qui trésaute)... 
  if (sd_reading != sd_previous) {
    ms_time = millis();               //On remet le timer de déparasitage à 0
  }
  
  sd_previous = sd_reading;
  
  if (sd_reading == LOW && pin2 == LOW
  && (millis() - ms_time) > DEBOUNCE){      //On vérifie s'il y a eu un changement de position positif
      
    C_EffetHall1 = true;             //On fixe la valeur de l'attribut capteur
    C_EffetHall2 = true;             //On fixe la valeur de l'attribut capteur
      
    if (mechanism_status == false) {        //Si il y a eu le premier changement de position
        
      S_Echiquier = true;             //On active l'électroaimant de la ventouse dragon                        
      S_Led = true;                   //On allume la led rouge                     
      mechanism_status = true;        //On valide le mécanisme
    } 
  }else{                        //Si il n'y a pas eu de changement de position positif
  
    C_EffetHall1 = false;             //On fixe la valeur de l'attribut capteur
    C_EffetHall2 = false;             //On fixe la valeur de l'attribut capteur
  } 
  
  if ( S_Echiquier == true ){              //Pour désactiver l'electroaimant de la ventouse
    delay(100);                   //On attend 0.1 seconde
    digitalWrite(SEchiquier_PIN, LOW);    // Écriture du statut sur la ventouse (LOW = on libere l'electroaimant)
    delay(500);
    digitalWrite(SEchiquier_PIN, HIGH);
    delay(4000);                       //On attend 4 secondes
    S_Echiquier = false;               //On change la valeur de l'attribut
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

Echec mechanism = Echec();

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
  Wire.onReceive(receive_order);      //On récupère le message s'ordre reçu sur le bus i2c via la fonction receive order
  Wire.onRequest(send_status);      //On envoie le messagei2c sur le bus i2c
  mechanism.setupMechanism();       //On donne une configuration de base au mécanisme
}

void loop() {
  delay(100);                     //On attends 0.1 seconde
  mechanism.execute();                //On exécute le mécanisme
}
