int CapteurHum = 0; // Le capteur est sur la pin A0  - Capteur H20
int H2OInitial = 0;
int readingH2O = 0;     // Contient la valeur lue sur la broche d'entrée
int etateau = 0; // 0 = non initialisé, 1 = initialisé, 2 = resolu
long timeEau = 0;
long debounce = 2000; // Temps de déparasitage (debounce time), a augmenter si la sortie clignote.



void setup() {
  Serial.begin (9600);// Démarrage de la liaison série
  pinMode(2, OUTPUT); //LED H2O
  pinMode(3, OUTPUT);//RELAIS H2O FRIGO
  pinMode(4, OUTPUT);//FONTAINE

  digitalWrite(4, HIGH);

}

void loop() {

  int var1;
  int var2;
  
  
  readingH2O = analogRead (CapteurHum);// Lecture de la valeur du capteur
  
  Serial.println(CapteurHum);
  delay(300);

}
