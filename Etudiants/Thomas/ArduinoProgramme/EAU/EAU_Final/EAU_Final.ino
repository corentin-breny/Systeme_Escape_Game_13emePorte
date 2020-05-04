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
    bool sensor[1] = {C_Humidite};


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
  C_Humidite = false;
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
digitalWrite(SFontaine_PIN, HIGH);
}


void Eau::execute(){

int ValeurCapteur;
int ValeurCapteurInitial;
int Time_Meca = 0;


ValeurCapteur = analogRead (CHumidite_PIN); //Lecture de la valeur du capteur
C_Humidite = true;

if(mecanism_status == false)
{
   ValeurCapteurInitial = ValeurCapteur;
   mecanism_status == true;
}


if(mecanism_status == true)
  {

       if(ValeurCapteur >= (ValeurCapteurInitial + 180) && Time_Meca == 0)
       {
         Time_Meca = millis();
       }
       else if(ValeurCapteur < (ValeurCapteurInitial + 180))
       {
         Time_Meca = 0;
       }

       
       if(Time_Meca > DEBOUNCE)
       {
         digitalWrite(SLed_PIN, HIGH);
         S_Led = true;

         digitalWrite(SFontaine_PIN, LOW);
         S_Fontaine = true;

         digitalWrite(SFrigo_PIN, LOW);  //RELAIS H2O FRIGO
         delay(1000);
         digitalWrite(SFrigo_PIN, HIGH);
         S_Frigo = true;
         
         delay(1000);
         digitalWrite(SFrigo_PIN, LOW);  
         delay(1000);
         digitalWrite(SFrigo_PIN, HIGH);
         delay(1000);
         digitalWrite(SFrigo_PIN, LOW);
         delay(1000);
         digitalWrite(SFrigo_PIN, HIGH);
         delay(5000);
         digitalWrite(SFrigo_PIN, LOW);
         S_EAU = true;
         delay(20000);
         
         digitalWrite(SFrigo_PIN, HIGH);
         delay(1000)
         digitalWrite(SFrigo_PIN, LOW);
       }
  }
}


//MAIN

Eau Mecanisme = Eau();

void setup(){
 Mecanisme.setupMecanism();
}

void loop(){
 delay(100);
 Mecanisme.execute();
}
