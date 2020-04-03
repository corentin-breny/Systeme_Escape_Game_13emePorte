
void setup() {
  
  Serial.begin (9600);//Démarrage de la liaison série
  pinMode(2, OUTPUT);//LED H2O Vert
  pinMode(5, OUTPUT);//LED H2O Rouge
  pinMode(3, OUTPUT);//RELAIS H2O FRIGO
  pinMode(4, OUTPUT);//FONTAINE

}

void loop() 
{

void getValeurCapteur(int ValeurCapteur);

void RelaisPorteFrigo();

void RelaisMoteurFontaine();

void AllumerLedTemoin();
  
}


class Capteur
{
  
  private :

  //int H2OInitial = ValeurCapteur;
  int m_id;
  int ValeurCapteur;

  public : 

  int getValeurCapteur();
    
};


int getValeurCapteur()
{
   int CapteurHum = 0;//Le capteur est sur la pin A0  - Capteur H20
   
   ValeurCapteur = analogRead (CapteurHum);//Lecture de la valeur du capteur
   delay(500);//Attendre 1/2 secondes
   return ValeurCapteur;
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
    digitalWrite(5, LOW); //Eteindre LED H2O Rouge
    digitalWrite(2, HIGH); //Allumer LED H2O Vert
  }
  else
  {
    digitalWrite(2, LOW); //Eteindre LED H2O Vert
    digitalWrite(5, HIGH); //Allumer LED H2O Rouge
  }
}


class PorteFrigo
{

  
  
  public : 

  void RelaisPorteFrigo();
    
};


void RelaisPorteFrigo()
{
   
  tab[] = { var1 , var2 }
   
for(int i = 1; i<3; i++)
{
    if (ValeurCapteur >= (H2OInitial + 180)) 
      {
         tab[i] = 1;
      }
      else 
      { 
        tab[i] = 0;
      }

      delay(3000);
}     

   if (var1 == true && var2 == true)
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
