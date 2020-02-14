 
// Senseur à Hall Effect
//
//  Pour rappel du capteur HALL:
//  gauche = GND
//  millieu = +
//  droite = pin 2 et pin 3 ,etc..




//PIN 2 = SIGNAL Récepteur doigt coupé  
//PIN 3 = RELAIS DOIGT 
// PIN 4 = LED CONTROLE DOIGT 


//PIN 7 = LECTURE FEU
//  PIN 8 = LECTURE Vent
//  PIN 4 = LECTURE terre aussi
//  PIN 10 = bouton porte
//  pin 11 = led feu
//  pin 12 = led vent
//  pin 13 = relais porte
//
//  PIN A4 = BOUTTON TRAPPE GM
//  PIN A6 = VERS RELAIS TRAPPE GM


  

const int halldoigt = 2;
int pindoigt;

int DOIGTstate = HIGH; // Etat actuel de la broche de sortie (la LED)
int readingDOIGT;      // Contient la valeur lue sur la broche d'entrée
int previousDOIGT = LOW;
long timeDOIGT = 0;      // La dernière fois que la broche de sortie à changé d'état
// Les variables suivantes sont de type "long" parce que nous allons mesure le temps (en milisecondes).
// Ce temps deviendra vite de grands nombres qui ne pourrons pas être stockés dans un simple entier (type "int").
long time = 0;      // La dernière fois que la broche de sortie à changé d'état
long debounce = 2000; // Temps de déparasitage (debounce time), a augmenter si la sortie clignote.


int state = HIGH; // Etat actuel de la broche de sortie (la LED)
int reading;      // Contient la valeur lue sur la broche d'entrée
int previous = LOW;




void setup() {

  pinMode(4, OUTPUT); // Vers led controle doigt
  pinMode (3 , OUTPUT); // Vers relais doigt
  pinMode (halldoigt , INPUT); // pin2
  digitalWrite(halldoigt, HIGH);



  pinMode(7, INPUT); //feu
  pinMode(11, OUTPUT);
  digitalWrite(11, LOW);

  pinMode(8, INPUT); // vent
  pinMode(12, OUTPUT);
  digitalWrite(12, LOW);

  pinMode(10, INPUT_PULLUP); // bouton exit

  pinMode(13, OUTPUT); // relais porte
  digitalWrite(13, HIGH);
 
  pinMode (A0 , OUTPUT);
  digitalWrite (A0, LOW);  // LED exit vert

  pinMode (A2 , OUTPUT);
  digitalWrite (A2, LOW);  // LED exit rouge



  pinMode (A4, INPUT_PULLUP);  // bouton trappe GM
  pinMode (A3, OUTPUT); // vers relais trappe GM
  digitalWrite(A3, HIGH );


}

void loop() {

  
  pindoigt = digitalRead( halldoigt );  // lecture du capteur a Effet Hall


   // @@ RECEPTEUR DOIGT COUPÉ @@


  readingDOIGT = pindoigt;
  // Si le contact à changé, est-ce causé par un changement de
  // position OU un parasite (bille qui trésaute)...
  if (readingDOIGT != previousDOIGT) {
    // Remettre la minuterie/timer de déparasitage à 0
    timeDOIGT = millis();
  }
  // attendre que l'on ai dépassé le temps de déparasitage
  if ((millis() - timeDOIGT) > (debounce / 3)) {

    if ((pindoigt == LOW)) {
      digitalWrite(4, HIGH); //LED CONTROLE doigt
      DOIGTstate = LOW;
    }
  }
  if (pindoigt == HIGH)
    DOIGTstate = HIGH;

  digitalWrite(3, DOIGTstate );

  previousDOIGT = readingDOIGT;




  // @@@@@@@@@@@@@@@  4 elements récepteur @@@@@@@@@@@@@
  
  int feu = digitalRead(7);
  int vent = digitalRead(8);
  int terre = digitalRead(4);
  int reading = digitalRead(10);

  if (feu == 1) {
    digitalWrite (11, HIGH);
  }
  else {
    digitalWrite (11, LOW);
  }


  if (vent == 1) {
    digitalWrite (12, HIGH);
  }
  else {
    digitalWrite (12, LOW);
  }



  if (reading != previous) {
    // Remettre la minuterie/timer de déparasitage à 0
    time = millis();
  }


  if ((millis() - time) > debounce) {

    if (reading == 0) {

      if ( (feu == 1 ) && (vent == 1 ) && (terre == 1)) {

        state = LOW;
        digitalWrite(A2, LOW); // led rouge exit
      }
      else {
        digitalWrite(A2, HIGH); // led rouge exit
        delay(500);
        digitalWrite(A2, LOW);
        state = HIGH;

      }
    }
  }

  digitalWrite(A0, not(state)); // LED vert exit
  digitalWrite(13, state);
  previous = reading;


  // @@@@@@@@@@@@@@@@@@@@@ trappe GM

  int trap = digitalRead(A4);


  if (trap == 0) {

    delay(500);
    int trap2 =  digitalRead(A4);

    if (trap == trap2) {
      delay(10000);
      digitalWrite(A3, LOW);
      delay(5000);
    }
  }
  else {
    digitalWrite(A3, HIGH);
  }

  Serial.print(trap);




}
