
void setup() {
  
  Serial.begin (9600);//Démarrage de la liaison série
  pinMode(2, OUTPUT);//LED H2O Vert
  pinMode(5, OUTPUT);//LED H2O Rouge
  pinMode(3, OUTPUT);//RELAIS H2O FRIGO
  pinMode(4, OUTPUT);//FONTAINE

}

void loop() 
{

void getValeurCapteur();

void getEtatMecanisme();

int definirEtatMecanisme();

void RelaisPorteFrigo();

void RelaisMoteurFontaine();

void AllumerLedTemoin();
  
}


class Capteur
{
  
  private :

 
  int m_id;
  int ValeurCapteur;

  public : 

  int getValeurCapteur(int ValeurCapteur);
    
};


int getValeurCapteur(int ValeurCapteur)
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


void AllumerLedTemoin(int m_etatMecanismeLedTemoin, int m_etatMecanisme)
{
  
  m_etatMecanismeLedTemoin = getEtatMecanisme(m_etatMecanisme);
  
  if (m_etatMecanismeLedTemoin == 1)
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


void RelaisPorteFrigo(int m_etatMecanismePorteFrigo, int m_etatMecanisme)
{

 m_etatMecanismePorteFrigo = getEtatMecanisme(m_etatMecanisme);
   
   if (m_etatMecanismePorteFrigo == 1)
    {
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


void RelaisMoteurFontaine(int m_etatMecanismeMoteurFontaine, int m_etatMecanisme)
{
  
  m_etatMecanismeMoteurFontaine = getEtatMecanisme(m_etatMecanisme);
  
  if (m_etatMecanismeMoteurFontaine == 1)
  {
    digitalWrite(4, LOW); //Activer Relais FONTAINE
  }
  else
  {
    digitalWrite(4, HIGH); //Desactiver Relais FONTAINE
  }
}



class ArduinoMecanisme 
{

  private : 

  int m_etatMecanisme;
  String m_dernierEtatMecanisme;
  int m_tempsDernierEnvoieValeurCapteur;


  public : 

  void calculerTempsDernierEnvoieEtatMecanisme();
  void redefinirDernierEtatMecanisme();
  void calculerTempsDernierEnvoieValeurCapteur();
  int definirEtatMecanisme();
  
};


int definirEtatMecanisme(int m_etatMecanisme, int ValeurCapteur)
{
    
 int H2OInitial =  getValeurCapteur(ValeurCapteur);
 
 int tab[] = { 0 , 0 };
   
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

     if(tab[0] == 1 && tab[1] == 1)
     {
       m_etatMecanisme = 1;
     }
}     


}


int getEtatMecanisme(int m_etatMecanisme)
{

this.m_etatMecanisme = m_etatMecanisme;

return m_etatMecanisme;
  
}






class Eau : public ArduinoMecanisme
{

   private : 

   boolean m_EAU;
  
};
