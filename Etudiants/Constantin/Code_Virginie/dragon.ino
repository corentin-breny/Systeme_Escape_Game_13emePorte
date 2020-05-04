etatclef = digitalRead( clef );   // INTERUPTEUR CLEF
  reading = etatclef;
       // Si le contact à changé, est-ce causé par un changement de 
       // position OU un parasite (bille qui trésaute)... 
       if (reading != previous) {
         // Remettre la minuterie/timer de déparasitage à 0
         time = millis();
       }
       // attendre que l'on ai dépassé le temps de déparasitage 
       if ((millis() - time) > ((debounce)/2)) {

    
Serial.print(digitalRead(8));

if (first==0){


if (etatclef==LOW){

  

  cathode_high();  //eteind led 7 digit
  digitalWrite(10 , LOW); // Ventouse dragon
  delay(1000);
  digitalWrite(10, HIGH);
 // delay(4000); // attend 5 sec
 
  digitalWrite(11, LOW); //fumée on
  delay(1000);
  digitalWrite(11,HIGH);//fumée off
  //delay(5000);
  first++; 
  state = LOW;
  }
//  else
//  {
//  digitalWrite(LED, LOW);  // LED CONTROLE
//  digitalWrite(7, HIGH);
//  }

} 
}

 digitalWrite(LED, not(state) ); // LED CONTROLE + LED Dragon
 previous= reading;
}