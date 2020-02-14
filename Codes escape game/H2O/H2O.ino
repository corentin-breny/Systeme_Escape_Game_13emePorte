// Pin AO (analog) = Signal capteur H2O
// PIN 2 = LED TEMOIN H20
// PIN 3 = RELAIS H20
// PIN 4 = RELAIS FONTAINE
// PIN 5 = BOUTON POUSSOIR CHIEN
// PIN 6 = LED VERT CHIEN
// PIN 7 = LED ROUGE CHIEN
// PIN 8 = RELAIS soufle CHIEN
// PIN 9 = RELAIS SARBACANNE
// PIN 10 = Intérupteur KATANA
// PIN 11 = vers LED controle KATANA (DOIGT)
// PIN 12 = Vers RELAIS DOIGT


// A1 = Vanne Entrée
// A2 = Vanne Ilot Bas (sous la Sarbacane)
// A3 = Vanne ilot Haut
// A4 = Vanne stock
// A5 = Vanne frigo
// A6 = Vanne Trappe
// A7 = Vanne Mur Alcool


int capteur = 0; // Le capteur est sur la pin A0  - Capteur H20
int H2OInitial = 0;
int readingH2O = 0;     // Contient la valeur lue sur la broche d'entrée
int etateau = 0; // 0 = non initialisé, 1 = initialisé, 2 = resolu
long timeEau = 0;


long timeChien = 0;      // La dernière fois que la broche de sortie à changé d'état
long debounce = 2000; // Temps de déparasitage (debounce time), a augmenter si la sortie clignote.
long debouncechien = 150;
int first = 0;

int statechien = HIGH; // Etat actuel de la broche de sortie (la LED)
int readingchien;         // Contient la valeur lue sur la broche d'entrée
int previouschien = LOW;  // Contient la précédente valeur lue sur la broche d'entrée
int firstchien = 0;


int statekatana = HIGH; // Etat actuel de la broche de sortie (la LED)
int readingkatana;         // Contient la valeur lue sur la broche d'entrée
int previouskatana = LOW;  // Contient la précédente valeur lue sur la broche d'entrée
int firstkatana = 0;
long timeKatana;


// Capteur VANNES
//int photocellPin = 1; // the cell and 10K pulldown are connected to a0
int van1; // the analog reading from the analog resistor divider
int van2;
int van3;
int van4;
int van5;
int van6;
int van7;



void setup ()
{
  Serial.begin (9600);// Démarrage de la liaison série
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);

  digitalWrite(4, HIGH);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, INPUT_PULLUP);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);

  digitalWrite(2, LOW); //LED H2O
  digitalWrite(3, HIGH); // relai H20 frigo
  digitalWrite(4, HIGH); //FONTAINE

  digitalWrite(7, LOW); // LED ROUGE
  digitalWrite(8, HIGH); //RELAIS CHIEN
  digitalWrite(9, HIGH); // RELAIS sarbacane

  digitalWrite(12, HIGH); // relai doigt


}


void loop ()
{


  // @@@@@@@  CAPTEUR H²0   @@@@@@@@@@@@
  readingH2O = analogRead (capteur);// Lecture de la valeur du capteur
  if (etateau == 0)
  {
    H2OInitial = readingH2O;
    etateau = 1;
  }
  if (etateau == 1)
  {
    if (readingH2O >= (H2OInitial + 180) && timeEau == 0)
      timeEau = millis();
    else if (readingH2O < (H2OInitial + 180))
      timeEau = 0;
    if (timeEau > debounce)
    {
      etateau = 2;
      digitalWrite(2, HIGH); //LED H2O
      digitalWrite(4, LOW); //FONTAINE
      digitalWrite(3, LOW);  //RELAIS H2O FRIGO
      delay(1000);
      digitalWrite(3, HIGH);
      delay(1000);
      digitalWrite(3, LOW);  //RELAIS H2O FRIGO
      delay(1000);
      digitalWrite(3, HIGH);
      delay(1000);
      digitalWrite(3, LOW);
      delay(1000);
      digitalWrite(3, HIGH);
      delay(5000);
      digitalWrite(3, LOW);
      delay(20000);
    }
  }
  digitalWrite(3, HIGH);


  //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

  //  @@@ 7 Vannes @@

  int VanOkSeuil = 10;
  van1 = analogRead(1) >= VanOkSeuil ? 1 : 0;
  van2 = analogRead(2) >= VanOkSeuil ? 1 : 0;
  van3 = analogRead(3) >= VanOkSeuil ? 1 : 0;
  van4 = analogRead(4) >= VanOkSeuil ? 1 : 0;
  van5 = analogRead(5) >= VanOkSeuil ? 1 : 0;
  van6 = analogRead(6) >= VanOkSeuil ? 1 : 0;
  van7 = analogRead(7) >= VanOkSeuil ? 1 : 0;
  long resultCode = van1 * 1000000 + van2 * 100000 + van3 * 10000 + van4 * 1000 + van5 * 100 + van6 * 10 + van7;
  // 1 = ouvert, 0 = fermée
  long codeToDo = 1101011;
  // digitalWrite(6, LOW);  // LED VERT

  readingchien = digitalRead(5);

  if (readingchien != previouschien) {
    // Remettre la minuterie/timer de déparasitage à 0
    timeChien = millis();
  }

  if ((millis() - timeChien) > debouncechien) {
    if (readingchien == 0) {
      if (codeToDo == resultCode) { // SI le code vanne correspond au code voulu

        if (firstchien == 0 ) {
          statechien = LOW;
          digitalWrite(9, LOW);  // Relais sarbacane
          digitalWrite(6 , HIGH); // LED vert
          delay(3000);
          firstchien = 1;
          digitalWrite(9, HIGH);  // Relais sarbacane
        }
        else {
          digitalWrite(6 , LOW);
          delay(500);
          digitalWrite(6 , HIGH);
          delay(500);
          digitalWrite(6 , LOW);
          delay(500);
          digitalWrite(6 , HIGH);
          delay(500);
        }
      }
      else {
        if (firstchien == 0 ) {
          digitalWrite(7, HIGH);  // LED ROUGE
          digitalWrite(8, LOW);  // RELAIS SOUFFLE CHIEN
          delay(200);
          digitalWrite(8, HIGH);  // RELAIS SOUFFLE CHIEN
          digitalWrite(7, HIGH);  // LED ROUGE
          delay(1000);
          digitalWrite(7, LOW);  // LED ROUGE
       }
        else {
          digitalWrite(6 , LOW);
          delay(500);
          digitalWrite(6 , HIGH);
          delay(500);
          digitalWrite(6 , LOW);
          delay(500);
          digitalWrite(6 , HIGH);
          delay(500);
        }
      }
    }
  }

  digitalWrite(6, not(statechien));  // LED VERT

  previouschien = readingchien;




   Serial.print("van1 = ");
    Serial.print(van1); // the raw analog reading
  Serial.print(" van2: ");
  Serial.print(van2);
  Serial.print(" van3: ");
  Serial.print(van3);
  Serial.print(" van4: ");
  Serial.print(van4);
  Serial.print(" van5: ");
  Serial.print(van5);
  Serial.print(" van6: ");
  Serial.print(van6);
  Serial.print(" van7: ");
  Serial.println(van7);
  Serial.println(readingchien);

  //  if (van2 < 10) {
  //    Serial.println(" - Noir");
  //  } else if (van2 < 200) {
  //    Serial.println(" - Sombre");
  //  } else if (van2 < 500) {
  //    Serial.println(" - Lumiere");
  //  } else if (van2 < 800) {
  //    Serial.println(" - Lumineux");
  //  } else {
  //    Serial.println(" - Tres lumineux");
  //  }


  // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ KATANA @@@@@@@@@@@@@@@@@@@@@@@@@@@

  readingkatana = digitalRead(10);

  if (readingkatana != previouskatana) {
    // Remettre la minuterie/timer de déparasitage à 0
    timeKatana = millis();
  }

  if ((millis() - timeKatana) > ((debounce))) {
    if (readingkatana == 0) {
      if (firstkatana == 0) {
        statekatana = LOW;
        digitalWrite(12, LOW);
        delay(500);
        digitalWrite(12, HIGH);
        firstkatana = 1;
      }
    }
    else {
      firstkatana = 0 ;
    }
  }
  digitalWrite(11, not(statekatana));
  previouskatana = readingkatana;
}
