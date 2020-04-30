//Fichier Terre.h

#define C_EffetHall1_PIN 2 //Capteur à effet Hall 1
#define S_LedR_PIN A2 //Led de sortie
#define S_LedV_PIN A0 //Led de sortie

class LionB {

  private :
    const int C_EffetHallD;
    bool S_LedR;
    bool S_LedV;
    bool mecanism_status;

  private :
    bool actuator[3] = {S_LedR};
    bool sensor[1] = {C_EffetHall1};
    const int halldoigt = 2;
    int pindoigt;
    int DOIGTstate = HIGH; // Etat actuel de la broche de sortie (la LED)
    int readingDOIGT;      // Contient la valeur lue sur la broche d'entrée
    int previousDOIGT = LOW;
    long timeDOIGT = 0;      // La dernière fois que la broche de sortie à changé d'état
    long time = 0;      // La dernière fois que la broche de sortie à changé d'état
    long debounce = 2000; // Temps de déparasitage (debounce time), a augmenter si la sortie clignote.
    // Les variables suivantes sont de type "long" parce que nous allons mesure le temps (en milisecondes).
    // Ce temps deviendra vite de grands nombres qui ne pourrons pas être stockés dans un simple entier (type "int").
    int state = HIGH; // Etat actuel de la broche de sortie (la LED)
    int reading;      // Contient la valeur lue sur la broche d'entrée
    int previous = LOW;

  public :
    Terre();
    void setupMecanism();
    void execute();
    void receive_order();
    void send_status();
};

//Fichier Terre.cpp

Terre::Terre(){  
  C_EffetHall_1 = false;
  S_LedR = false;
  S_LedV = false;
  mecanism_status = false;
}

void LionB::setupMechanism() {
  
  pinMode(4, OUTPUT); // Vers led controle doigt
  pinMode (3 , OUTPUT); // Vers relais doigt
  pinMode (C_EffetHallD, INPUT); // pin2
  digitalWrite(C_EffetHallD, HIGH);
  
  pinMode (A0 , OUTPUT);
  digitalWrite (A0, LOW);  // LED exit vert

  pinMode (A2 , OUTPUT);
  digitalWrite (A2, LOW);  // LED exit rouge
 
}

void LionB::execute(){
  
  pindoigt = digitalRead( halldoigt );  // lecture du capteur a Effet Hall

  readingDOIGT = pindoigt;

  if (readingDOIGT != previousDOIGT) 
  { 
    timeDOIGT = millis();  // Remettre la minuterie/timer de déparasitage à 0
  }
  
  if ((millis() - timeDOIGT) > (debounce / 3)) // attendre que l'on ai dépassé le temps de déparasitage
  {
    if ((pindoigt == LOW)) 
    {
      digitalWrite(4, HIGH); //LED CONTROLE doigt
      DOIGTstate = LOW;
    }
  }
  if (pindoigt == HIGH)
  {
    DOIGTstate = HIGH;
  }

  digitalWrite(3, DOIGTstate );

  previousDOIGT = readingDOIGT;  
}
