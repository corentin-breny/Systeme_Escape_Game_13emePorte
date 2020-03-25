int CapteurHum = 0; // Le capteur est sur la pin A0  - Capteur H20
int H2OInitial = 0;
int readingH2O = 0;     // Contient la valeur lue sur la broche d'entrée
int etateau = 0; // 0 = non initialisé, 1 = initialisé, 2 = resolu
long timeEau = 0;
long debounce = 2000; // Temps de déparasitage (debounce time), a augmenter si la sortie clignote.



void setup() {
  Serial.begin (9600);// Démarrage de la liaison série
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);

  digitalWrite(4, HIGH);

}

void loop() {

  int var1;
  int var2;
  
  
  readingH2O = analogRead (CapteurHum);// Lecture de la valeur du capteur
  
  
  if (etateau == 0)
  {
    H2OInitial = readingH2O;
    etateau = 1;
  }
  
 
  if (etateau == 1)
  {
    if (readingH2O >= (H2OInitial + 180)) {
      var1 = 1;}
      else { var1 = 0;}

      delay(3000);
      
 if (readingH2O >= (H2OInitial + 180)) {
  var2 = 1;}
 else { var2 = 0;}

      

    if (var1 == var2 && var2 == 1)
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


Serial.println(readingH2O);

}


}
