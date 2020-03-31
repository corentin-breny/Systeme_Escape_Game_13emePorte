int CapteurHum = 0; // Le capteur est sur la pin A0  - Capteur H20
int readingH2O = 0;     // Contient la valeur lue sur la broche d'entrée
int EtatEau = 0;
int H2OInitial = 0;

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
  
  Serial.println(readingH2O);
  delay(300);

 if(EtatEau == 0)
 {
    H2OInitial = readingH2O;
    EtatEau = 1;
 }
    
    if ( EtatEau == 1)
    {
     
      if (readingH2O >= (H2OInitial + 180)) 
      {
         var1 = 1;
      }
      else 
      { 
        var1 = 0;
      }

      delay(3000);
      
      
      if (readingH2O >= (H2OInitial + 180)) 
      {
        var2 = 1;
      }
      else 
      {
        var2 = 0;
      }
    }
 

  
  if (var1 == var2 && var2 == 1)
  {
      EtatEau = 2;
      digitalWrite(2, HIGH); //LED H2O
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
      digitalWrite(3, HIGH);
   }



}
