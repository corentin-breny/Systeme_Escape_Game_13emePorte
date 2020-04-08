//Fichier Eau.H

#define CHumidite_PIN A0  //Capteur d'humidité
#define SLed_PIN 2       //Led controle
#define SFrigo_PIN 3     //Relais Frigo
#define SFontaine_PIN 4  //Relais Fontaine
#define DEBOUNCE 2000


class Eau{

  private : 
    bool S_Frigo;
    bool S_Fontaine;
    bool S_Led;
    bool S_Eau;
    bool C_Humidite;
    bool mecanism_status;
   

  private : 
    bool actuator[4] = {S_Frigo, S_Fontaine, S_Led, S_Eau};
    bool sensor[1] = {C_Humidite];


    public : 
      Eau();
      void setupMecanism();
      void execute();
};


//Fichier Eau.CPP

Eau::Eau(){
  S_Frigo = false;
  S_Fontaine = false;
  S_Led = false;
  S_Eau = false;
  C_Humidite = true;
  mecanism_status = false;
}


//SETUP
void Eau::setupMecanism(){

Serial.begin (9600);//Démarrage de la liaison série

pinMode(CHumidite_PIN, INPUT);

pinMode(SLed_PIN, OUTPUT);
digitalWrite(SLed_PIN, LOW);

pinMode(SFrigo_PIN, OUTPUT);
digitalWrite(SFrigo_PIN, HIGH);

pinMode(SFontaine_PIN, OUTPUT);
digitalWrite(SFontaine_PIN, LOW);
}


void Eau::execute(){

int ValeurCapteur;
int ValeurCapteurInitial;
int Time_Meca = 0;


ValeurCapteur = analogRead (CHumidite_PIN); //Lecture de la valeur du capteur

if(mecanism_status == false)
{
   ValeurCapteurInitial = ValeurCapteur;
   mecanism_status == true;
}


if(mecanism_status == true)
  {

       if(ValeurCapteur >= (ValeurCapteurInitial + 180) && TimeMeca == 0)
       {
         TimeMeca = millis();
       }
       else if(ValeurCapteur < (ValeurCapteurInitial + 180))
       {
         TimeMeca = 0;
       }

       
       if(TimeMeca > DEBOUNCE)
       {
         digitalWrite(SLed_PIN, HIGH);

         digitalWrite(SFontaine_PIN, LOW);

         digitalWrite(SFrigo_PIN, LOW);  //RELAIS H2O FRIGO
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
  }
digitalWrite(SFrigo_PIN, HIGH);
}

Eau Mecanisme = Eau();


void setup() {
 Mecanism.setupMechanism();
}

void loop() {
 delay(100);
 Mecanisme.execute();
}


/*class Capteur
{
  
  private :

  int m_id;
  int ValeurCapteur;

  public : 

  int getValeurCapteur(int ValeurCapteur);
    
};


int Capteur::getValeurCapteur()
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


void Led::AllumerLedTemoin()
{
  
  if (getEtatMecanisme() == 1)
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


void PorteFrigo::RelaisPorteFrigo()
{

   if (getEtatMecanisme() == 1)
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


void Fontaine::RelaisMoteurFontaine()
{
  
  if (getEtatMecanisme() == true)
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

  bool m_etatMecanisme;
  bool S_Frigo;
  bool S_Fontaine;
  bool S_Eau;
  bool actuator[] = {S_Frigo, S_Fontaine, S_Eau};

  public : 

  ArduinoMecanisme();
  int definirEtatMecanisme();
  bool gerEtatMecanisme();
  
  
};


ArduinoMecanisme::ArduinoMecanisme()
{
 m_etatMecanisme = false;
}



int ArduinoMecanisme::definirEtatMecanisme(bool m_etatMecanisme)
{
    
 int H2OInitial =  getValeurCapteur();
 
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
       m_etatMecanisme = true;
     }
}     

}


bool ArduinoMecanisme::getEtatMecanisme()
{
return m_etatMecanisme;
}*/
