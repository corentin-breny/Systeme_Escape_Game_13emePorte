int etateau = 0;

void loop() {

	int valeurCapteur = analogRead (CHumidite_PIN);// Lecture de la valeur du capteur

	switch(etateau){
		case 0 :
			int valeurCapteurInitiale = valeurCapteur;
			etateau = 1;
			break;
		case 1 :
			C_Humidite = valeurCapteur - valeurCapteurInitiale
			if (C_Humidite >=180) {
				
				S_Fontaine = true; 
				S_Frigo = true;
				S_Led = true; 
				S_Eau = true;
				mechanism_status = true;
			}
	}
	if (S_Fontaine == true){
		delay(100);
		digitalWrite(SFontaine_PIN, LOW); //FONTAINE
	}
			  
	if (S_Frigo == true){
		delay(100);
		digitalWrite(SFrigo_PIN, LOW);  //LOW désactive electroaiamant
		delay(1000);
		digitalWrite(SFrigo_PIN, HIGH);
		delay(1000);
		digitalWrite(SFrigo_PIN, LOW);  //RELAIS H2O FRIGO
		delay(1000);
		digitalWrite(SFrigo_PIN, HIGH);
		delay(1000);
		digitalWrite(SFrigo_PIN, LOW);
		delay(1000);
		digitalWrite(SFrigo_PIN, HIGH);
		delay(5000);
		digitalWrite(SFrigo_PIN, LOW);
		delay(20000);
	}
			  
	if ( S_Led == true ){								//Pour allumer la led témoin
		delay(100);										//On attend 0.1 seconde
		digitalWrite(SLed_PIN, HIGH);					//On allume la led de contrôle
	}else{												//Pour éteindre la led témoin
		delay(100);										//On attend 0.1 seconde
		digitalWrite(SLed_PIN, LOW);					//On éteint la led de contrôle
	}
	
	if ( mechanism_status == false ){					//En cas de reset
		S_Frigo = false;
		S_Fontaine = false;
		S_Led = false;									//On change la valeur de l'attribut
		S_Eau = false;									//On change la valeur de l'attribut
	}
}