//Fichier Eau.H

#include "Wire.h"
#define SLAVE_ADDRESS 0x16  //initialisation de l’Arduino avec l’adresse 0x16

#define CHumidite_PIN A0  //Capteur d'humidité
#define SLed_PIN 2       //Led controle
#define SFrigo_PIN 3     //Relais Frigo
#define SFontaine_PIN 4  //Relais Fontaine


int ValeurCapteur = 0;
int EtatEau = 0;


class Eau{

  private : 
    bool S_Frigo;
    bool S_Fontaine;
    bool S_Led;
    bool S_Eau;
    int C_Humidite;
    bool mecanism_status;

 public : 

 bool actuator[4]={S_Frigo, S_Fontaine,S_Led, S_Eau};
 int sensor[1] = {C_Humidite};

 public : 

 bool getMechanism_status();
 void setMechanism_status(bool ms);
 int getC_Humidite();

    public : 
      Eau();
      void setupMecanism();
      void execute();
};


//Fichier Eau.CPP

Eau::Eau(){
  S_Frigo = false;
  S_Fontaine = false;
  S_Led = false;
  S_Eau = false;
  C_Humidite = 0;
  mecanism_status = false;
}

bool Eau::getMechanism_status(){
  return mechanism_status;
}

void Eau::setMechanism_status(bool ms){
  mechanism_status = ms;
}


int Eau::getC_Humidite(){
  return C_Humidite;
}


//SETUP
void Eau::setupMecanism(){

pinMode(CHumidite_PIN, INPUT);

pinMode(SLed_PIN, OUTPUT);
digitalWrite(SLed_PIN, LOW);

pinMode(SFrigo_PIN, OUTPUT);
digitalWrite(SFrigo_PIN, HIGH);

pinMode(SFontaine_PIN, OUTPUT);
digitalWrite(SFontaine_PIN, HIGH);
}


void Eau::execute(){


ValeurCapteur = analogRead (CHumidite_PIN); //Lecture de la valeur du capteur


switch(EtatEau){
    case 0 :
         int ValeurCapteurInitial = ValeurCapteur;
         EtatEau = 1;
         break;
    case 1 : 
         C_Humidite = ValeurCapteur - ValeurCapteurInitiale;

         if (C_Humidite >=180){
       
          S_Fontaine = true; 
          S_Frigo = true;
          S_Led = true; 
          S_Eau = true;
          mechanism_status = true;
        }
  } 


if (S_Fontaine == true)
{
      delay(100);
      digitalWrite(SFontaine_PIN, LOW); //FONTAINE
}
       


if (S_Frigo == true){
        
         digitalWrite(SFrigo_PIN, LOW);  //RELAIS Frigo Activer
         delay(1000);
         digitalWrite(SFrigo_PIN, HIGH); //RELAIS Frigo Désactiver
         
         delay(1000);
         digitalWrite(SFrigo_PIN, LOW);  
         delay(1000);
         digitalWrite(SFrigo_PIN, HIGH);
         delay(1000);
         digitalWrite(SFrigo_PIN, LOW);
         delay(1000);
         digitalWrite(SFrigo_PIN, HIGH);
         delay(5000);
         digitalWrite(SFrigo_PIN, LOW);
         delay(20000);
         
         digitalWrite(SFrigo_PIN, HIGH);
         delay(1000)
         digitalWrite(SFrigo_PIN, LOW); 
}


if ( S_Led == true )//Pour allumer la led témoin
  {                
    delay(100);                           //On attend 0.1 seconde
    digitalWrite(SLed_PIN, HIGH);         //On allume la led de contrôle
  }
else
  {                        //Pour éteindre la led témoin
    delay(100);                           //On attend 0.1 seconde
    digitalWrite(SLed_PIN, LOW);          //On éteint la led de contrôle
  }
  

if ( mechanism_status == false )//En cas de reset
  {         
    S_Frigo = false;
    S_Fontaine = false;
    S_Led = false;                  //On change la valeur de l'attribut
    S_Eau = false;                  //On change la valeur de l'attribut
    etateau = 0;
  }
}


//MAIN

Eau Mecanisme = Eau();

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

  for(int i=0; i<sizeof(mechanism.sensor)/2; i++){        //Pour chaque capteur du mécanisme
    sd_I2Cmessage += mechanism.getC_Humidite();//mechanism.sensor[i];            //On ajoute la valeur du capteur au message i2c
    sd_I2Cmessage += "X";             //Et on ajoute aussi X
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
  delay(100);               //On attends 0.1 seconde
  mechanism.execute();          //On exécute le mécanisme
}
