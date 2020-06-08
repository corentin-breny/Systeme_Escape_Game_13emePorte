//Fichier Air.H

#include "Wire.h"
#define SLAVE_ADDRESS 0x17  //initialisation de l’Arduino avec l’adresse 0x16

#define CBouton_PIN 5       //Bouton Poussoir Chien
#define SLedVerte_PIN 6     //Led Verte Chien
#define SLedRouge_PIN 7     //Led Rouge Chien
#define SChien_PIN 8          //Relais Souffle Chien
#define SAir_PIN 9          //Relais Sarbacane

#define DEBOUNCE 2000 // Temps de déparasitage (debounce time), a augmenter si la sortie clignote.

int sd_reading = HIGH;          //Valeur actuelle du capteur
int sd_previous = HIGH;       //Valeur précédente du capteur
long ms_time = 0;               //Dernière fois que le statut du mécanisme a changé




class Air{

  private : 
    bool S_Vanne;
    bool S_Led; // Led  pour prévenir la réussite ou non de la combinaison des vannes
    bool S_Chien;     //L'actionneur où le chien souffle
    bool S_Air;   // L'actionneur du relai pour l'air de la sarbacanne
    bool C_Vanne1; //les actionneurs des 7 vannes
    bool C_Vanne2;
    bool C_Vanne3;
    bool C_Vanne4;
    bool C_Vanne5;
    bool C_Vanne6;
    bool C_Vanne7;
    bool C_Bouton;  // L'actionneur du bouton poussoir
    bool mechanism_status; // indique si le mécanisme est activé ou non
  
  
 public : 

 bool actuator[4]={S_Vanne, S_Chien, S_Led, S_Air};
 bool sensor[8] = {C_Vanne1, C_Vanne2, C_Vanne3, C_Vanne4, C_Vanne5, C_Vanne6, C_Vanne7, C_Bouton};

 public : 

 bool getMechanism_status();
 void setMechanism_status(bool ms);


    public : 
      Air();
      void setupMechanism();
      void execute();
};


//Fichier Air.CPP

Air::Air(){
  S_Vanne = false;
  S_Chien = false;
  S_Led = false;
  S_Air = false;
  C_Vanne1 = false;
  C_Vanne2 = false;
  C_Vanne3 = false;
  C_Vanne4 = false;
  C_Vanne5 = false;
  C_Vanne6 = false;
  C_Vanne7 = false;
  C_Bouton = false;
  mechanism_status = false;
}

bool Air::getMechanism_status(){ //On demande si le mécanisme a été réalisé ou non
  return mechanism_status;       //On retourne une réponse, true ou false
}

void Air::setMechanism_status(bool ms){ //On demande le dernier temps d'actualisation
  mechanism_status = ms;                //On retourne le temps d'actualisation
}

//SETUP
void Air::setupMechanism(){
pinMode(CBouton_PIN, INPUT_PULLUP);

pinMode(SLedVerte_PIN, OUTPUT);
 if (S_Led = false){               //Suivant la valeur de l'attribut
    digitalWrite(SLedVerte_PIN , LOW);       //On éteint la led par défaut
  }else{
    digitalWrite(SLedVerte_PIN , HIGH);        //On allume la led par défaut
    }
 
pinMode(SLedRouge_PIN, OUTPUT);
 if (S_Led = false){               //Suivant la valeur de l'attribut
    digitalWrite(SLedRouge_PIN , LOW);       //On éteint la led par défaut
  }else{
    digitalWrite(SLedRouge_PIN , HIGH);        //On allume la led par défaut
    }
 
pinMode(SAir_PIN, OUTPUT);
 if (S_Air = false){               //Suivant la valeur de l'attribut
    digitalWrite(SAir_PIN , LOW);       //On active l'électroaimant de la sarbacane
  }else{
    digitalWrite(SAir_PIN , HIGH);        //On désactive l'électroaimant de la sarbacane
    }

}

void Air::execute(){


    int VanOkSeuil = 10;
int vanne1 = analogRead(C_Vanne1) >= VanOkSeuil ? 1 : 0; //Lis la valeur de la tension a la broche de la vanne 1, si celle-ci est ouverte ou fermée
  if (vanne1 == 1){
    C_Vanne1 = true;
  }else{
    C_Vanne1 = false;
  }
 int  vanne2 = analogRead(C_Vanne2) >= VanOkSeuil ? 1 : 0; //Lis la valeur de la tension a la broche de la vanne 2, si celle-ci est ouverte ou fermée
   if (vanne2 == 1){
    C_Vanne2 = true;
  }else{
    C_Vanne2 = false;
  }
  int vanne3 = analogRead(C_Vanne3) >= VanOkSeuil ? 1 : 0; //Lis la valeur de la tension a la broche de la vanne 3, si celle-ci est ouverte ou fermée
   if (vanne3 == 0){
    C_Vanne3 = true;
  }else{
    C_Vanne3 = false;
  }
   int vanne4 = analogRead(C_Vanne4) >= VanOkSeuil ? 1 : 0; //Lis la valeur de la tension a la broche de la vanne 4, si celle-ci est ouverte ou fermée
   if (vanne4 == 1){
    C_Vanne4 = true;
  }else{
    C_Vanne4 = false;
  }
  int vanne5 = analogRead(C_Vanne5) >= VanOkSeuil ? 1 : 0; //Lis la valeur de la tension a la broche de la vanne 5, si celle-ci est ouverte ou fermée
   if (vanne5 == 0){
    C_Vanne5 = true;
  }else{
    C_Vanne5 = false;
  }
 int  vanne6 = analogRead(C_Vanne6) >= VanOkSeuil ? 1 : 0; //Lis la valeur de la tension a la broche de la vanne 6, si celle-ci est ouverte ou fermée
   if (vanne6 == 1){
    C_Vanne6 = true;
  }else{
    C_Vanne6 = false;
  }
  int vanne7 = analogRead(C_Vanne7) >= VanOkSeuil ? 1 : 0; //Lis la valeur de la tension a la broche de la vanne 7, si celle-ci est ouverte ou fermée
   if (vanne7 == 1){
    C_Vanne7 = true;
  }else{
    C_Vanne7 = false;
  }
  


  if (C_Vanne1 == true && C_Vanne2 == true && C_Vanne3 == true && C_Vanne4 == true && C_Vanne5 == true && C_Vanne6 == true && C_Vanne7 == true ){
    S_Vanne = true;
  }else{
    S_Vanne == false;
  }
  
  sd_reading = digitalRead(CBouton_PIN); // Lis l'etat du bouton poussoir





if (sd_reading != sd_previous) {
    ms_time = millis();               //On remet le timer de déparasitage à 0
  }
  
  sd_previous = sd_reading;
  
  if (sd_reading == LOW
  && (millis() - ms_time) > DEBOUNCE){      //On vérifie s'il y a eu un changement de position positif
      
    C_Bouton = true;             //On fixe la valeur de l'attribut capteur
      
    if (mechanism_status == false
    && S_Vanne == true) {        //Si il y a eu le premier changement de position et Si le code vanne correspond au code voulu)   
      S_Chien = true;              //On active l'électroaimant de la statue de chien         
      S_Led = true;               //On allume la led verte    
      S_Air = true;               //On allume l'element Air des 4 éléments    
      mechanism_status = true;}          //On valide le mécanisme
  }else{                        //Si il n'y a pas eu de changement de position positif
    C_Bouton = false; }              //On fixe la valeur de l'attribut capteur
  if ( S_Air == true ){             //Pour désactiver l'electroaimant de la sarbacane
    delay(100);                     //On attend 0.1 seconde
    digitalWrite(SAir_PIN, HIGH);   //On désactive l'electroaimant de la sarbacane
    delay(3000);                    // Attendre 3secondes
    digitalWrite(SAir_PIN, LOW);    //On réactive l'electroaimant
    delay(4000);                    //On attend 4 secondes
    S_Air = false;                  //On change la valeur de l'attribut
  }
  if ( S_Chien == true ){           //Pour désactiver l'électroaimant de la statue de chien
    delay(200);                     // Attendre 0,2 seconde
    digitalWrite(SChien_PIN, LOW);  //On désactive l'électroaimant de la statue de chien
    delay(1000);                    // Attendre 1 seconde
    digitalWrite(SChien_PIN, HIGH); //On réactive l'électroaimant
    S_Chien = false;                //On change la valeur de l'attribut
  }
  if ( S_Led == true ){             //Pour allumer la led témoin
    delay(100);                     //On attend 0.1 seconde
    digitalWrite(SLedVerte_PIN, HIGH);   //On allume la led de contrôle
    digitalWrite(SLedRouge_PIN, LOW);    //On éteint la led de contrôle
  }else{                            //Pour éteindre la led témoin
    delay(100);                     //On attend 0.1 seconde
    digitalWrite(SLedVerte_PIN, LOW);    //On éteint la led de contrôle
    digitalWrite(SLedRouge_PIN, HIGH);    //On allume la led rouge
  }
   if ( mechanism_status == false ){ //En cas de reset
    S_Led = false;                  //On change la valeur de l'attribut
    S_Air = false;                  //On change la valeur de l'attribut
    S_Chien = false;
    S_Vanne = false;
  }}





//MAIN

Air mechanism = Air();

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
