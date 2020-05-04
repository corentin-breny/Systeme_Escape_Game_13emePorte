//FICHIER 4Elements.H

#define CPoussoir_PIN 1
#define SLed_PIN 2
#define SPorteFinal_PIN 3
#define SLedTerre_PIN 4
#define SLedFeu_PIN 5
#define SLedEau_PIN 6
#define SLedAir_PIN 7



class 4Elements{

  private :
   bool S_Terre;
   bool S_Feu;
   bool S_Eau;
   bool S_Air;
   bool C_Poussoir;
   bool mecanism_status;
   
   


public : 
    4Elements();
    void setupMecanism();
    void execute();
  
};


4Elements::4Elements(){
  S_Terre = false;
  S_Feu = false;
  S_Eau = false; 
  S_Air = false;
  C_Poussoir = false;
  mecanism_status = false;  
  
}



void 4Elements::setupMecanism(){

Serial.begin (9600);//Démarrage de la liaison série

pinMode(CPoussoir_PIN, INPUT);

pinMode(SLedTerre_PIN, INPUT);
digitalWrite(SLedTerre_PIN, LOW);

pinMode(SLedFeu_PIN, INPUT);
digitalWrite(SLedFeu_PIN, LOW);

pinMode(SLedEau_PIN, INPUT);
digitalWrite(SLedEau_PIN, LOW);

pinMode(SLedAir_PIN, INPUT);
digitalWrite(SLedAir_PIN, LOW);

pinMode(SLed_PIN, OUTPUT);
digitalWrite(SLed_PIN, LOW);

pinMode(SPorteFinal_PIN, OUTPUT);
digitalWrite(SPorteFinal_PIN, HIGH);
  
}












void setup() {
  

}

void loop() {
  

}
