    /* Senseur à Hall Effect

  Pour rappel du capteur HALL:
  gauche = GND
  millieu = +
  droite = pin 2 et pin 3 ,etc..


  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@ ECHEC @@@@@@@@@@@@@@@@@@@

  Jaune (x2) = +
  Voilet (x2) = -
  Rouge / Orange = Vers pin

  PIN 2 = Signal ECHEC
  PIN 3 = RELAIS LION B
  PIN 4 = Signal ECHEC
  PIN 5 =
  PIN 6 = SIGNAL LION B
  PIN 7 = LED CONTROLE ECHEC
  PIN 8 = RELAIS ECHEC
  PIN 10 = LED CONTROLE LION B
 PIN 11 = Intérupteur KATANA
PIN 12 = vers LED controle KATANA (DOIGT)
PIN 13 = Vers RELAIS DOIGT





*/

const int hallPin = 2;
const int hallPin2 = 4;
const int halllionb = 6;
const int halldoigt = 13;

int pin1;
int pin2;
int pin3;
int pinlionb;
int pindoigt;
int firstlionb = 0;


int statekatana = HIGH; // Etat actuel de la broche de sortie (la LED)
int readingkatana;         // Contient la valeur lue sur la broche d'entrée
int previouskatana = LOW;  // Contient la précédente valeur lue sur la broche d'entrée
int firstkatana = 0;
long timeKatana;


int ECHECstate = HIGH; // Etat actuel de la broche de sortie (la ventouse HIGH maintiens de la ventouse fermée)
int readingECHEC;         // Contient la valeur lue sur la broche d'entrée
int previousECHEC = LOW;  // Contient la précédente valeur lue sur la broche d'entrée
long timeECHEC = 0;      // La dernière fois que la broche de sortie à changé d'état

int LIONBstate = HIGH; // Etat actuel de la broche de sortie (la LED)
int readingLIONB;         // Contient la valeur lue sur la broche d'entrée
int previousLIONB = LOW;
long timeLIONB = 0;      // La dernière fois que la broche de sortie à changé d'état
int LedLIONB = LOW;


// Les variables suivantes sont de type "long" parce que nous allons mesure le temps (en milisecondes).
// Ce temps deviendra vite de grands nombres qui ne pourrons pas être stockés dans un simple entier (type "int").
long time = 0;      // La dernière fois que la broche de sortie à changé d'état
long debounce = 2000; // Temps de déparasitage (debounce time), a augmenter si la sortie clignote.

void setup() {
  pinMode( 8, OUTPUT ); // vers relais echec
  pinMode( 7, OUTPUT ); // vers led controle echec
  pinMode(10, OUTPUT); // vers led controle lionb
  pinMode( 3, OUTPUT); // Vers relais lionb
  pinMode( hallPin, INPUT);  // pin 2
  pinMode( hallPin2, INPUT ); // pin 4
  pinMode( halllionb, INPUT); // pin 6
  pinMode(11, INPUT_PULLUP);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

  digitalWrite(hallPin, HIGH);  // Activation résistance pullUP
  digitalWrite(hallPin2, HIGH);
  digitalWrite(halllionb, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(12, LOW); //LED doigt
  digitalWrite(13, HIGH); //relais doigt
}
   
void loop() {
  // lecture du capteur a Effet Hall
  pin1 = digitalRead( hallPin );
  pin2 = digitalRead( hallPin2 );
  pinlionb = digitalRead( halllionb );



  // senseurValue = HIGH sans aimant
  // senseurValue = LOW  quand POLE SUD aimant
  // pin1 = not( pin1 );
  // pin2 = not( pin2 );
  // pinlionb = not (pinlionb );
 





  // @@@@@ ECHEC @@@


  readingECHEC = pin1;
  // Si le contact à changé, est-ce causé par un changement de
  // position OU un parasite (bille qui trésaute)...
  // SI on a pas reolu l'enigme
  if (ECHECstate == HIGH)
  {
    if (readingECHEC != previousECHEC) {
      // Remettre la minuterie/timer de déparasitage à 0
      timeECHEC = millis();
    }
    // attendre que l'on ai dépassé le temps de déparasitage
    if ((millis() - timeECHEC) > debounce)
    {
      // di les deux pieces sont à la bonne place
      if ((pin1 == LOW) && (pin2 == LOW)){
        ECHECstate = LOW; // On valide l'enigme
      //else
      //  LEDstate = HIGH; }
    }
    // Mémoriser la dernière lecture
    previousECHEC = readingECHEC;
  }

  // ecriture du statut sur la led (HIGH = allumé donc inverse de la ventouse)
  digitalWrite(7, not(ECHECstate));
  // ecriture du statut sur la ventouse (LOW = on libere l'electroaimant)
  digitalWrite(8, ECHECstate);
delay(500);
digitalWrite(8, not(ECHECstate));

}

  // @@@ LON BASCULANT @@@



  readingLIONB = pinlionb;
  // Si le contact à changé, est-ce causé par un changement de
  // position OU un parasite (bille qui trésaute)...
  if (LIONBstate == HIGH)
  {
    if (readingLIONB != previousLIONB) {
      // Remettre la minuterie/timer de déparasitage à 0
      timeLIONB = millis();
    }
    // attendre que l'on ai dépassé le temps de déparasitage
    if ((millis() - timeLIONB) > (debounce)) {
      if (readingLIONB == HIGH) {
        LIONBstate = LOW;
        digitalWrite(3, LIONBstate);
        //reset pour defaire le solenoide
        timeLIONB = millis();
        LedLIONB = HIGH;
      }
    }
    // Mémoriser la dernière lecture
    previousLIONB = readingLIONB;
  }
  else if ((millis() - timeLIONB) > debounce)
  {
    digitalWrite(3, HIGH);
    if (readingLIONB == LOW)
      LIONBstate = HIGH;
  }
  digitalWrite(10, LedLIONB);


   // @@@@@@@@@ KATANA @@@@@@@@@@@

  readingkatana = digitalRead(11);

  if (readingkatana != previouskatana) {
    // Remettre la minuterie/timer de déparasitage à 0
    timeKatana = millis();
  }

  if ((millis() - timeKatana) > ((debounce))) {
    if (readingkatana == 0) {
      if (firstkatana == 0) {
        statekatana = LOW;
        digitalWrite(13, LOW);
        delay(500);
        digitalWrite(13, HIGH);
        firstkatana = 1;
      }
    }
    else {
      firstkatana = 0 ;
    }
  }
  digitalWrite(12, not(statekatana));
  previouskatana = readingkatana;





  


}
