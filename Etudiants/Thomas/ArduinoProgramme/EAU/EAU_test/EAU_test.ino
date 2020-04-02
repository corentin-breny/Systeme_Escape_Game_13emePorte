int CapteurHum = 0; // Le capteur est sur la pin A0  - Capteur H20
int readingH2O = 0;     // Contient la valeur lue sur la broche d'entrée
int EtatEau = 0;
int H2OInitial = 0;

void setup() {
  
  Serial.begin (9600);//Démarrage de la liaison série
  pinMode(2, OUTPUT);//LED H2O Vert
  pinMode(5, OUTPUT);//LED H2O Rouge
  pinMode(3, OUTPUT);//RELAIS H2O FRIGO
  pinMode(4, OUTPUT);//FONTAINE

}

void loop() {

  int var1;
  int var2;
  
  
  readingH2O = analogRead (CapteurHum);//Lecture de la valeur du capteur
  
  Serial.println(readingH2O);
  delay(500);

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


class Capteur
{
  
  private :
  
  int m_id;
  int ValeurCapteur;

  public : 

  void getValeurCapteur();
    
};


void getValeurCapteur(int ValeurCapteur)
{
   int CapteurHum = 0;//Le capteur est sur la pin A0  - Capteur H20
   
   ValeurCapteur = analogRead (CapteurHum);//Lecture de la valeur du capteur
   delay(500);//Attendre 1/2 secondes
}


class Led
{

  private :

  int m_id;

  public : 

  void AllumerLedTemoin();

};


void AllumerLedTemoin()
{
  if (var1 == var2 && var2 == 1)
  {
    
  }
}


class PorteFrigo
{

  public : 

  void RelaisPorteFrigo();
    
};


void RelaisPorteFrigo()
{
   int EtatEau = 0;
   int H2OInitial = 0;
   int var1;
   int var2;
   
   if(EtatEau == 0)
   {
      H2OInitial = getValeurCapteur();
      EtatEau = 1;
   }

   if ( EtatEau == 1)
    {
     
      if (getValeurCapteur() >= (H2OInitial + 180)) 
      {
         var1 = 1;
      }
      else 
      { 
        var1 = 0;
      }

      delay(3000);
      
      
      if (getValeurCapteur() >= (H2OInitial + 180)) 
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
  digitalWrite(3, HIGH);
}


class Fontaine 
{

  public : 

  void RelaisMoteurFontaine();
  
};


void RelaisMoteurFontaine()
{
  if (var1 == var2 && var2 == 1)
  {
    digitalWrite(4, LOW); //Activer Relais FONTAINE
  }
  else
  {
    digitalWrite(4, HIGH); //Desactiver Relais FONTAINE
  }
  
}
