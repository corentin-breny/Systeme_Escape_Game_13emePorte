#include <Arduino.h>
#include "Feu.h"

Feu::Feu(){
  S_Dragon = false;
  S_Fumee = false;
  S_Led = false;
  S_Feu = true;
  C_Interupteur = false;
  mechanism_status = false;
}

void Feu::setupMechanism() {
  pinMode(CInterupteur_PIN , INPUT_PULLUP); 
  
  pinMode(SLed_PIN, OUTPUT); 
  digitalWrite(SLed_PIN , LOW);
    
  pinMode(SDragon_PIN, OUTPUT);
  digitalWrite(SDragon_PIN, HIGH);
  
  pinMode(SFumee_PIN, OUTPUT);
  digitalWrite(SFumee_PIN, HIGH);
}

void Feu::execute(){
  sensor_data = digitalRead(CInterupteur_PIN);   // INTERUPTEUR CLEF
  
  if (sensor_data == HIGH){
    C_Interupteur = true;
  }
  
  // Si le contact à changé, est-ce causé par un changement de position OU un parasite (bille qui trésaute)... 
  if (C_Interupteur != sd_previous) {
  // Remettre la minuterie/timer de déparasitage à 0
    ms_time = millis();
  }
  
  // attendre que l'on ai dépassé le temps de déparasitage 
  if ((millis() - ms_time) > ((DEBOUNCE)/2)) {  
    Serial.print(digitalRead(CInterupteur_PIN));

    if (mechanism_status==false && C_Interupteur == true){
      //cathode_high();  //eteind led 7 digit //Envoyer un ordre à une autre arduino
        
      digitalWrite(SDragon_PIN, LOW); // Ventouse dragon
      delay(1000);
      digitalWrite(SDragon_PIN, HIGH);
      S_Dragon = true;
        
      delay(4000); // attend 5 sec
      digitalWrite(SFumee_PIN, LOW); //fumée on
      delay(1000);
      digitalWrite(SFumee_PIN,HIGH);//fumée off
      S_Fumee = true;
        
      delay(5000);
      mechanism_status = true; 
      digitalWrite(SLed_PIN, HIGH);
      S_Led = true;
      S_Dragon = true;
    } 
  }
  sd_previous = C_Interupteur;
}
