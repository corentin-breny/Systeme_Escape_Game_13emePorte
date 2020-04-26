







void setup() {
 
pinMode(7, INPUT); //feu
pinMode(8, INPUT); // vent
pinMode(9, OUTPUT); // Vers led controle doigt
pinMode(10, INPUT_PULLUP); // bouton exit

pinMode (A0 , OUTPUT);
digitalWrite (A0, LOW);  // LED exit vert
 
pinMode (A2 , OUTPUT);
digitalWrite (A2, LOW);  // LED exit rouge

}

void loop() {

  
  
  int feu = digitalRead(7);
  int vent = digitalRead(8);
  int terre = digitalRead(9);
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


}
