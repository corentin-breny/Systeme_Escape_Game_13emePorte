//Fichier Air.H

#include "Wire.h"
#define SLAVE_ADDRESS 0x16  //initialisation de l’Arduino avec l’adresse 0x16

#define CBouton_PIN 5       //Bouton Poussoir Chien
#define SLedVerte_PIN 6     //Led Verte Chien
#define SLedRouge_PIN 7     //Led Rouge Chien
#define SChien_PIN 8          //Relais Souffle Chien
#define SAir_PIN 9          //Relais Sarbacane

long timeChien = 0;      // La dernière fois que la broche de sortie à changé d'état
long debounce = 2000; // Temps de déparasitage (debounce time), a augmenter si la sortie clignote.
long debouncechien = 150;
int first = 0;



class Air{

  private : 
    bool S_LedVerte; // Led verte pour prévenir la réussite de la combinaison des vannes
    bool S_Chien;     //L'actionneur où le chien souffle
    bool S_LedRouge;  //Led rouge pour prévenir l'échec de la combinaison des vannes 
    bool S_Air;   // L'actionneur du relai pour l'air de la sarbacanne
    bool C_Vanne1; //les actionneurs des 7 vannes
    bool C_Vanne2;
    bool C_Vanne3;
    bool C_Vanne4;
    bool C_Vanne5;
    bool C_Vanne6;
    bool C_Vanne7;
    bool C_Bouton;  // L'actionneur du bouton poussoir
    bool mecanism_status; // indique si le mécanisme est activé ou non

 public : 

 bool actuator[4]={S_LedRouge, S_Chien, S_LedVerte, S_Air};
 bool sensor[8] = {C_Vanne1, C_Vanne2, C_Vanne3, C_Vanne4, C_Vanne5, C_Vanne6, C_Vanne7, C_Bouton};

 public : 

 bool getMechanism_status();
 void setMechanism_status(bool ms);


    public : 
      Air();
      void setupMecanism();
      void execute();
      void receive_order();
      void send_status();
};


//Fichier Air.CPP

Air::Air(){
  S_LedRouge = false;
  S_Chien = false;
  S_LedVerte = false;
  S_Air = false;
  C_Vanne1 = false;
  C_Vanne2 = false;
  C_Vanne3 = false;
  C_Vanne4 = false;
  C_Vanne5 = false;
  C_Vanne6 = false;
  C_Vanne7 = false;
  mecanism_status = false;
}

bool Air::getMechanism_status(){ //On demande si le mécanisme a été réalisé ou non
  return mechanism_status;       //On retourne une réponse, true ou false
}

void Air::setMechanism_status(bool ms){ //On demande le dernier temps d'actualisation
  mechanism_status = ms;                //On retourne le temps d'actualisation
}

//SETUP
void Air::setupMecanism(){
pinMode(CBouton_PIN, INPUT_PULLUP);

pinMode(SLedVerte_PIN, OUTPUT);
 
pinMode(SLedRouge_PIN, OUTPUT);
digitalWrite(SLedRouge_PIN, LOW); // LED ROUGE
 
pinMode(SAir_PIN, OUTPUT);
digitalWrite(SAir_PIN, HIGH); //RELAIS CHIEN



void Air::execute(){


  int VanOkSeuil = 10;
  vanne1 = analogRead(S_Vanne1) >= VanOkSeuil ? 1 : 0; //Lis la valeur de la tension a la broche de la vanne 1, si celle-ci est ouverte ou fermée
  vanne2 = analogRead(S_Vanne2) >= VanOkSeuil ? 1 : 0; //Lis la valeur de la tension a la broche de la vanne 2, si celle-ci est ouverte ou fermée
  vanne3 = analogRead(S_Vanne3) >= VanOkSeuil ? 1 : 0; //Lis la valeur de la tension a la broche de la vanne 3, si celle-ci est ouverte ou fermée
  vanne4 = analogRead(S_Vanne4) >= VanOkSeuil ? 1 : 0; //Lis la valeur de la tension a la broche de la vanne 4, si celle-ci est ouverte ou fermée
  vanne5 = analogRead(S_Vanne5) >= VanOkSeuil ? 1 : 0; //Lis la valeur de la tension a la broche de la vanne 5, si celle-ci est ouverte ou fermée
  vanne6 = analogRead(S_Vanne6) >= VanOkSeuil ? 1 : 0; //Lis la valeur de la tension a la broche de la vanne 6, si celle-ci est ouverte ou fermée
  vanne7 = analogRead(S_Vanne7) >= VanOkSeuil ? 1 : 0; //Lis la valeur de la tension a la broche de la vanne 7, si celle-ci est ouverte ou fermée
  long resultCode = vanne1 * 1000000 + vanne2 * 100000 + vanne3 * 10000 + vanne4 * 1000 + vanne5 * 100 + vanne6 * 10 + vanne7; // On calcule le code 
  //afin de valider si les vannes sont bien coordonnées
  // 1 = ouvert, 0 = fermée
  long codeToDo = 1101011; // resultat du code de validitée
  // digitalWrite(SLedVerte_PIN, LOW);  // LED VERT

  readingchien = digitalRead(CBouton_PIN); // Lis l'etat du bouton poussoir

  if (readingchien != previouschien) {  // Remettre la minuterie/timer de déparasitage à 0
    timeChien = millis();
  }

  if ((millis() - timeChien) > debouncechien) {
    if (readingchien == 0) {
      if (codeToDo == resultCode) { // SI le code vanne correspond au code voulu

        if (firstchien == 0 ) {
          statechien = LOW;
          digitalWrite(SAir_PIN, LOW);  // On désactive le Relais sarbacane
          digitalWrite(SLedVerte_PIN , HIGH); // On active la LED vert
          delay(3000); // Attendre 3secondes
          firstchien = 1;
          digitalWrite(SAir_PIN, HIGH);  //On reactive le Relais sarbacane
        }
        else {
          digitalWrite(SLedVerte_PIN , LOW); //On désactive la LED verte
          delay(500); // Attendre 0,5 seconde
          digitalWrite(SLedVerte_PIN , HIGH);//On active la LED verte
          delay(500);// Attendre 0,5 seconde
          digitalWrite(SLedVerte_PIN , LOW); //On désactive la LED verte
          delay(500);// Attendre 0,5 seconde
          digitalWrite(SLedVerte_PIN , HIGH); //On active la LED verte
          delay(500);// Attendre 0,5 seconde
        }
      }
      else {
        if (firstchien == 0 ) {
          digitalWrite(SLedRouge_PIN, HIGH);  // On active la LED ROUGE
          digitalWrite(SChien_PIN, LOW);  // On désactive le RELAIS SOUFFLE CHIEN
          delay(200); // Attendre 0,2 seconde
          digitalWrite(SChien_PIN, HIGH);  //On reactive le RELAIS SOUFFLE CHIEN
          digitalWrite(SLedRouge_PIN, HIGH);  //On désactive la LED ROUGE
          delay(1000); // Attendre 1 seconde
          digitalWrite(SLedRouge_PIN, LOW);  //On active la LED ROUGE
       }
        else {
          digitalWrite(SLedVerte_PIN , LOW); //On désactive la LED verte
          delay(500); // Attendre 0,5 seconde
          digitalWrite(SLedVerte_PIN , HIGH); //On active la LED verte
          delay(500); // Attendre 0,5 seconde
          digitalWrite(SLedVerte_PIN , LOW); //On désactive la LED verte
          delay(500); // Attendre 0,5 seconde
          digitalWrite(SLedVerte_PIN , HIGH); //On active la LED verte
          delay(500); // Attendre 0,5 seconde
        }
      }
    }
  }

  digitalWrite(SLedVerte_PIN, not(statechien));  // LED VERT

  previouschien = readingchien;




   Serial.print("vanne1 = "); // Imprime les données sur le port série sous forme de texte
    Serial.print(vanne1); // the raw analog reading
  Serial.print(" vanne2: ");// Imprime les données sur le port série sous forme de texte
  Serial.print(vanne2);
  Serial.print(" vanne3: ");// Imprime les données sur le port série sous forme de texte
  Serial.print(vanne3);
  Serial.print(" vanne4: ");// Imprime les données sur le port série sous forme de texte
  Serial.print(vanne4);
  Serial.print(" vanne5: ");// Imprime les données sur le port série sous forme de texte
  Serial.print(vanne5);
  Serial.print(" vanne6: ");// Imprime les données sur le port série sous forme de texte
  Serial.print(vanne6);
  Serial.print(" vanne7: ");// Imprime les données sur le port série sous forme de texte
  Serial.println(vanne7);
  Serial.println(readingchien);

  //  if (vanne2 < 10) {
  //    Serial.println(" - Noir");
  //  } else if (vanne2 < 200) {
  //    Serial.println(" - Sombre");
  //  } else if (vanne2 < 500) {
  //    Serial.println(" - Lumiere");
  //  } else if (vanne2 < 800) {
  //    Serial.println(" - Lumineux");
  //  } else {
  //    Serial.println(" - Tres lumineux");
  //  }

}
//MAIN

Air Mecanisme = Air();

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
