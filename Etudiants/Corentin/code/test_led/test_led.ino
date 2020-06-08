void setup() {
  //pinMode(10, OUTPUT);
 pinMode(11, OUTPUT);
  //pinMode(12, OUTPUT);
}

void loop() {
  if (digitalRead(10)== HIGH)
 {
  digitalWrite(11, LOW);
 }
else 
{
 delay(1000);
  digitalWrite(11, HIGH);
 }
 delay (1000);
}
