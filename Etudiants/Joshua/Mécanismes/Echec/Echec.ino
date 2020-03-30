int ECHECstate = HIGH; // Etat actuel de la broche de sortie (la ventouse HIGH maintiens de la ventouse fermée)
int readingECHEC;         // Contient la valeur lue sur la broche d'entrée
int previousECHEC = LOW;  // Contient la précédente valeur lue sur la broche d'entrée
long timeECHEC = 0;      // La dernière fois que la broche de sortie à changé d'état

void setup() {
	
  digitalWrite(hallPin, HIGH);  // Activation résistance pullUP
  digitalWrite(hallPin2, HIGH);

}

void loop() {
	
    // lecture du capteur a Effet Hall
	
	pin1 = digitalRead( hallPin );
	pin2 = digitalRead( hallPin2 );
	
	readingECHEC = pin1;
	
    // Si le contact à changé, est-ce causé par un changement de
    // position OU un parasite (bille qui trésaute)...
	
   
	if (ECHECstate == HIGH)	 // SI on a pas reolu l'enigme
	{
		if (readingECHEC != previousECHEC) 
		{	// Remettre la minuterie/timer de déparasitage à 0
		timeECHEC = millis();
		}
	
    // attendre que l'on ai dépassé le temps de déparasitage
	
    if ((millis() - timeECHEC) > debounce)
    {
        if ((pin1 == LOW) && (pin2 == LOW))	// si les deux pieces sont à la bonne place
		{
			ECHECstate = LOW; // On valide l'enigme
			//else
			//  LEDstate = HIGH; }
		}
	
		previousECHEC = readingECHEC;	// Mémoriser la dernière lecture
	
	}

    digitalWrite(7, not(ECHECstate));	// ecriture du statut sur la led (HIGH = allumé donc inverse de la ventouse)
	
    // ecriture du statut sur la ventouse (LOW = on libere l'electroaimant)
	
    digitalWrite(8, ECHECstate);
    delay(500);
    digitalWrite(8, not(ECHECstate));
	}
}