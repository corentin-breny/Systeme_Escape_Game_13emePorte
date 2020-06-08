//Fichier Eau.H

#include "Wire.h"
#define SLAVE_ADDRESS 0x16  //initialisation de l’Arduino avec l’adresse 0x16

#define CHumidite_PIN A0         //Capteur d'humidité au pin A0
#define SLed_PIN 2               //Led de contrôle au pin 2
#define SFrigo_PIN 3             //Relais Frigo au pin 3
#define SFontaine_PIN 4          //Relais Fontaine au pin 4
#define SLedElements_PIN 5       //Led 4 elements au pin 5

int ValeurCapteur = 0;
int EtatEau = 0;
int ValeurCapteurInitial;
int var1 = 0;
int var2 = 0; 

class Eau{

  private : 
    
    bool S_Frigo;                   //Actionneurs qui active/désactive l'électro-aimant de la porte du frigo
    bool S_Fontaine;                //Actionneurs qui active/désactive le moteur de la fontaine 
    bool S_Led;                     //Actionneurs qui active/désactive la led de contrôle
    bool S_Eau;                     //Actionneurs de l'élément Eau sur la tablette des 4 éléments
    int C_Humidite;                 //Valeur numérique détécter par le capteur d'humidité 
    bool mechanism_status;           //indique si le mécanisme est activé ou non 

 public : 

 bool actuator[4]={S_Frigo, S_Fontaine,S_Led, S_Eau};
 int sensor[1] = {C_Humidite};

 public : 

 bool getMechanism_status();
 void setMechanism_status(bool ms);
 int getC_Humidite();

    public :    
      Eau();                        //Constructeur par défaut de la classe
      void setupMecanism();         //Configuration de la base du mécanisme
      void execute();               //Méthode qui fait fonctionner le mécanisme

};


//Fichier Eau.CPP

Eau::Eau(){
  S_Frigo = false;
  S_Fontaine = false;
  S_Led = false;
  S_Eau = false;
  C_Humidite = 0;
  mechanism_status = false;
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

pinMode(CHumidite_PIN, INPUT);             //On initialise le pin du capteur d'Humidité en entrée

pinMode(SLed_PIN, OUTPUT);                 //On initialise la led du tableau de commande en sortie
digitalWrite(SLed_PIN, LOW);               //On éteint la led par défaut 

pinMode(SFrigo_PIN, OUTPUT);               //On initialise le pin du relais frigo en sortie
digitalWrite(SFrigo_PIN, HIGH);            //On désactive le relais du frigo par défaut

pinMode(SFontaine_PIN, OUTPUT);            //On initialise le pin du relais de la fontaine 
digitalWrite(SFontaine_PIN, HIGH);         //On désactive le relais de la fontaine par défaut

pinMode(SLedElements_PIN, OUTPUT);         //On initialise la led des 4 éléments en sortie
digitalWrite(SLedElements_PIN, LOW);       //On éteint la led par défaut 
}


void Eau::execute(){

ValeurCapteur = analogRead (CHumidite_PIN); //On récupère la valeur du capteur d'humidité

if(EtatEau == 0)
{
ValeurCapteurInitial = ValeurCapteur;
EtatEau = 1; 
}


if(EtatEau == 1)
{

        if(ValeurCapteur >= (ValeurCapteurInitial + 180))
        {
           var1 = 1;   
        }

        delay(3000);

        if(ValeurCapteur >= (ValeurCapteurInitial + 180))
        {
            var2 = 1;
        }
       
       
         if (var1 == var2){             //Si la valeur du capteur est supérieur ou éguale à 180 points de base
       
          S_Fontaine = true;                //On active le moteur de la fontaine
          S_Frigo = true;                   //On active l'électro-aimant de la porte du frigo
          S_Led = true;                     //On allume la led du panneau de contrôle
          S_Eau = true;                     //On allume l'élément Eau des 4 éléments
          mechanism_status = true;          //On valide le mécanisme 
        }

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
         delay(1000);
         digitalWrite(SFrigo_PIN, LOW);
         delay(3600000); 
}


if (S_Fontaine == true)
{
      delay(100);
      digitalWrite(SFontaine_PIN, LOW); //FONTAINE
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
  
if(S_Eau == true)
{
   digitalWrite(SLedElements_PIN, HIGH);   
}



if (mechanism_status == false )//En cas de reset
  {         
    S_Frigo = false;
    S_Fontaine = false;
    S_Led = false;                  //On change la valeur de l'attribut
    S_Eau = false;                  //On change la valeur de l'attribut
    EtatEau = 0;
  }

}

//MAIN

Eau mechanism = Eau();

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
  mechanism.setupMecanism();       //On donne une configuration de base au mécanisme
}

void loop() {
  delay(100);               //On attends 0.1 seconde
  mechanism.execute();          //On exécute le mécanisme
}
