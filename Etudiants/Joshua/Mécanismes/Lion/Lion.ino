//Fichier LionB.h

#define C_EffetHall1_PIN A0 //Capteur à effet Hall 1
#define S_LedR_PIN 3 //Led de sortie

class LionB {

  private :
    const int C_EffetHall1;
    bool S_LedR;
    bool mecanism_status;
    int pin1;
    int pin2;

  private :
    bool actuator[3] = {S_LedR};
    bool sensor[1] = {C_EffetHall1};
    int LIONBstate = HIGH; // Etat actuel de la broche de sortie (la LED)
    int readingLIONB;         // Contient la valeur lue sur la broche d'entrée
    int previousLIONB = LOW;
    long timeLIONB = 0;      // La dernière fois que la broche de sortie à changé d'état
    int LedLIONB = LOW;

  public :
    LionB();
    void setupMecanism();
    void execute();
    void receive_order();
    void send_status();
};

//Fichier LionB.cpp

LionB::LionB(){  
  C_EffetHall_1 = false;
  S_LedR = false;
  mecanism_status = false;
}

void LionB::setupMechanism() {
  
  pinMode(10, OUTPUT); // vers led controle lionb
  digitalWrite(10, HIGH);
  
  pinMode( 3, OUTPUT); // Vers relais lionb
  digitalWrite(3, HIGH);
  
  pinMode(C_EffetHall, INPUT); // pin 6
  digitalWrite(C_EffetHall, HIGH);
  
  pinMode(11, INPUT_PULLUP);
  
  digitalWrite(hallPin, HIGH);  // Activation résistance pullUP
  digitalWrite(hallPin2, HIGH);
 
}

void LionB::execute(){
  
  pinlionb = digitalRead(C_EffetHall);

  readingLIONB = pinlionb;

  if (LIONBstate == HIGH)
  {
    if (readingLIONB != previousLIONB) 
    {  
      timeLIONB = millis();   // Remettre la minuterie/timer de déparasitage à 0
    }
    
    if ((millis() - timeLIONB) > (debounce)) // attendre que l'on ai dépassé le temps de déparasitage
    {    
      if (readingLIONB == HIGH) 
      {
        LIONBstate = LOW;
        digitalWrite(3, LIONBstate);    //reset pour defaire le solenoide
        timeLIONB = millis();
        LedLIONB = HIGH;
      }
    }

    previousLIONB = readingLIONB;   // Mémoriser la dernière lecture
  }
  else if ((millis() - timeLIONB) > debounce)
  {
    digitalWrite(3, HIGH);
    if (readingLIONB == LOW)
    LIONBstate = HIGH;
  }
  digitalWrite(10, LedLIONB);  
}
