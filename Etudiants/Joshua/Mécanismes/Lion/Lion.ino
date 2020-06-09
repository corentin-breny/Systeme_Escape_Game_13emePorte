#include <Wire.h>

//Fichier LionB.h
#define SLAVE_ADDRESS 0x13
#define CEffetHall1_PIN A0 //Capteur à effet Hall 1
#define SLed_PIN A3 //Led de sortie
#define SLion_PIN 3 //Actionneur
#define DEBOUNCE 2000

int sd_reading = HIGH;        //Valeur actuelle du capteur
int sd_previous = HIGH;       //Valeur précédente du capteur
long ms_time = 0;

class LionB {

  private :
    bool C_EffetHall;
    bool S_Lion;
    bool S_Led;
    bool mechanism_status;

  public :
    bool actuator[2] = {S_Lion, S_Led};
    bool sensor[1] = {C_EffetHall};
    bool getMechanism_status();
    void setMechanism_status(bool ms);

  public :
    LionB();
    void setupMechanism();
    void execute();
};

//Fichier LionB.cpp

LionB::LionB(){  
  C_EffetHall = false;
  S_Led = false;
  S_Lion = false;
  mechanism_status = false;
}

bool LionB::getMechanism_status(){
  return mechanism_status;
}

void LionB::setMechanism_status(bool ms){
  mechanism_status = ms;
}

void LionB::setupMechanism() {

  pinMode(C_EffetHall, INPUT); // pin 6
  digitalWrite(C_EffetHall, HIGH);
  
  pinMode(SLion_PIN, OUTPUT); // Vers relais lionb
  digitalWrite(SLion_PIN, HIGH);

  pinMode(SLion_PIN, OUTPUT);         //On initialise le pin du relais de l'électroaimant de la ventouse pour le tiroir
  if (S_Lion = false){               //Suivant la valeur de l'attribut
    digitalWrite(SLion_PIN, LOW);       //On active le relais de l'électroaimant par défaut
  }else{
    digitalWrite(SLion_PIN, HIGH);      //On désactive le relais de l'électroaimant par défaut
    }
  
  pinMode(SLed_PIN, OUTPUT);          //On initialise le pin de la Led
  if (S_Led = false){             //Suivant la valeur de l'attribut
    digitalWrite(SLed_PIN, HIGH);       //On désactive la Led
  }else{
    digitalWrite(SLed_PIN, LOW);       //On active la Led
  }
}

void LionB::execute(){


  sd_reading = digitalRead(CEffetHall1_PIN);       //On récupère la valeur du capteur à effet Hall

  //on tient à vérifier si il y a eu un changement de position ou un parasite (bille qui trésaute)... 
  if (sd_reading != sd_previous) {
    ms_time = millis();               //On remet le timer de déparasitage à 0
  }
  
  sd_previous = sd_reading;
  
  if (sd_reading == HIGH
  && (millis() - ms_time) > DEBOUNCE){      //On vérifie que la statuette est tournée depuis un certain temps (DEBOUNCE)
      
    C_EffetHall = false;             //On fixe la valeur de l'attribut capteur
      
    if (mechanism_status == false) {        //Si il y a eu le premier changement de position
        
      S_Lion = true;                  //On active l'électroaimant du tiroir                        
      S_Led = true;                   //On allume la led rouge                     
      mechanism_status = true;        //On valide le mécanisme
    } 
  }else{                        //Si il n'y a pas eu de changement de position positif
  
    C_EffetHall = false;             //On fixe la valeur de l'attribut capteur
  } 
  
  if (S_Lion == true ){              //Pour désactiver l'electroaimant du tiroir 
    digitalWrite(SLion_PIN, HIGH);    //reset pour defaire le solenoide
    digitalWrite(SLed_PIN, HIGH);    
  }else
  {
    digitalWrite(SLion_PIN, LOW);    //reset pour defaire le solenoide
    digitalWrite(SLed_PIN, LOW);
  }
  
  if (S_Led == true ){                    //Pour allumer la led témoin
    delay(100);                           //On attend 0.1 seconde
    digitalWrite(SLed_PIN, HIGH);         //On allume la led de contrôle
  }else{                                  //Pour éteindre la led témoin
    delay(100);                           //On attend 0.1 seconde
    digitalWrite(SLed_PIN, LOW);          //On éteint la led de contrôle
  }
  
  if ( mechanism_status == false ){         //En cas de reset
    S_Led = false;                  //On change la valeur de l'attribut
    S_Lion = false;    //La led correspondante sur le panneau du superviseur est allumée
  }

}

LionB mechanism = LionB();

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
/*
  for(int i=0; i<sizeof(mechanism.sensor)/2; i++){        //Pour chaque capteur du mécanisme
    sd_I2Cmessage += mechanism.getC_Poids();//mechanism.sensor[i];            //On ajoute la valeur du capteur au message i2c
    sd_I2Cmessage += "X";             //Et on ajoute aussi X
  }
  */
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
  delay(100);               //On attends 0.1 seconde
  mechanism.execute();          //On exécute le mécanisme
}
