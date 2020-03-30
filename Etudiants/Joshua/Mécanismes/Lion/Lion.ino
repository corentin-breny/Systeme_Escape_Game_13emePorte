const int halllionb = 6;
int pinlionb;

int LIONBstate = HIGH; // Etat actuel de la broche de sortie (la LED)
int readingLIONB;         // Contient la valeur lue sur la broche d'entrée
int previousLIONB = LOW;
long timeLIONB = 0;      // La dernière fois que la broche de sortie à changé d'état
int LedLIONB = LOW;
void setup() {
	
	pinMode( 8, OUTPUT ); // vers relais echec
	pinMode( 7, OUTPUT ); // vers led controle echec
	pinMode(10, OUTPUT); // vers led controle lionb
	pinMode( 3, OUTPUT); // Vers relais lionb
	pinMode( halllionb, INPUT); // pin 6
	pinMode(11, INPUT_PULLUP);
	pinMode(12, OUTPUT);
	pinMode(13, OUTPUT);

	digitalWrite(halllionb, HIGH);
	digitalWrite(3, HIGH);
	digitalWrite(8, HIGH);
}

void loop() {
	
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
  
}