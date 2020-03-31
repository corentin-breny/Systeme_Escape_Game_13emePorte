void setup() {
  pinMode(12, OUTPUT); //init pin led verte
  pinMode(11, OUTPUT); //init pin led rouge

}

void loop() {
  digitalWrite (12, HIGH); //allumer led verte
  delay (1000); //delais 1s
  digitalWrite (12, LOW); //éteindre led verte
  delay (1000); //delais 1s

  digitalWrite (11, HIGH); //allumer led rouge
  delay (1000); //delais 1s
  digitalWrite (11, LOW); //éteindre led rouge
  delay (1000); //delais 1s
}
