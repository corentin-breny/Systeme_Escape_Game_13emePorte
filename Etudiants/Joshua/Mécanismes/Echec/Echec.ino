//Fichier Echec.h

#define C_EffetHall1_PIN A0 //Capteur à effet Hall 1
#define C_EffetHall2_PIN 2 //Capteur à effet Hall 2
#define S_LedR_PIN 3 //Led de sortie

class Echec{

  private :
    const int C_EffetHall1;
    const int C_EffetHall2;
    bool S_LedR;
    bool mecanism_status;
    int pin1;
    int pin2;

  private :
    bool actuator[3] = {S_LedR};
    bool sensor[1] = {C_EffetHall1};
    bool sensor[2] = {C_EffetHall2};
    int ECHECstate = HIGH; // Etat actuel de la broche de sortie (la ventouse HIGH maintiens de la ventouse fermée)
    int readingECHEC;         // Contient la valeur lue sur la broche d'entrée
    int previousECHEC = LOW;  // Contient la précédente valeur lue sur la broche d'entrée
    long timeECHEC = 0;      // La dernière fois que la broche de sortie à changé d'état
    long time = 0;      // La dernière fois que la broche de sortie à changé d'état
    long debounce = 2000; // Temps de déparasitage (debounce time), a augmenter si la sortie clignote.     

  public :
    Echec();
    void setupMecanism();
    void execute();
    void receive_order();
    void send_status();
   
};

//Fichier Echec.cpp

Echec::Echec(){
  
  C_EffetHall_1 = false;
  C_EffetHall_2 = false;
  S_LedR = false;
  mecanism_status = false;
}


void Echec::setupMechanism() {
  
  pinMode( 8, OUTPUT ); // Relais echec
  digitalWrite(8, HIGH);
  
  pinMode( 7, OUTPUT ); // Led controle echec
  digitalWrite(7, HIGH);

  pinMode(11, INPUT_PULLUP);

  digitalWrite(hallPin, HIGH);  // Activation résistance pullUP
  digitalWrite(hallPin2, HIGH);
 
}

void Echec::execute(){

  pin1 = digitalRead(C_EffetHall_1);
  pin2 = digitalRead(C_EffetHall_2);
  
  readingECHEC = pin1;

  if (ECHECstate == HIGH)
  {
    if (readingECHEC != previousECHEC) {    
      
      timeECHEC = millis();   // Remettre la minuterie/timer de déparasitage à 0
    }
    
    if ((millis() - timeECHEC) > debounce)    // Attendre que l'on ai dépassé le temps de déparasitage
    {
      
      if ((pin1 == LOW) && (pin2 == LOW))     // Si les deux pieces sont à la bonne place
      {  
        ECHECstate = LOW; // On valide l'enigme
      } else LEDstate = HIGH;
      
    previousECHEC = readingECHEC;     // Mémoriser la dernière lecture
    }  
  }

  digitalWrite(7, not(ECHECstate));   // Écriture du statut sur la led (HIGH = allumé soit l'inverse de la ventouse)
  digitalWrite(8, ECHECstate);    // Écriture du statut sur la ventouse (LOW = on libere l'electroaimant)
  delay(500);
  digitalWrite(8, not(ECHECstate));
}
