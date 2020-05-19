//FICHIER 4Elements.H

#define CPoussoir_PIN 1        //Bouton poussoir au pin 1
#define SLed_PIN 2             //Led rouge des 4 éléments au pin 2
#define SPorteFinal_PIN 3      //Relais de l'électro-aimant de la porte final au pin 3
#define ETerre_PIN 4           //Liaison de l'arduino Terre au pin 4
#define EFeu_PIN 5             //Liaison de l'arduino Feu au pin 5
#define EEau_PIN 6             //Liaison de l'arduino Eau au pin 6
#define EAir_PIN 7             //Liaison de l'arduino Air au pin 7

class 4Elements{

  private :
   bool E_Terre;             //Variable qui informe si ETerre_PIN = TRUE ou FALSE
   bool E_Feu;               //Variable qui informe si EFeu_PIN = TRUE ou FALSE
   bool E_Eau;               //Variable qui informe si EEau_PIN = TRUE ou FALSE
   bool E_Air;               //Variable qui informe si EAir_PIN = TRUE ou FALSE
   bool S_Led;               //Actionneur qui allume ou éteint la led des 4 éléments
   bool C_Poussoir;          //Etat de la position détécter par le bouton poussoir
   bool mecanism_status;     //Indique si le mécanisme est activé ou non
   
   


public : 
    4Elements();              //Constructeur par défaut de la classe
    void setupMecanism();     //Configuration de base du mécanisme
    void execute();           //Méthode qui fais fonctionner le mécanisme
  
};


4Elements::4Elements(){
  S_Terre = false;
  S_Feu = false;
  S_Eau = false; 
  S_Air = false;
  C_Poussoir = false;
  mecanism_status = false;  
  
}



void 4Elements::setupMecanism(){

pinMode(CPoussoir_PIN, INPUT);          //On initialise le pin du bouton poussoir en entrée

pinMode(SLed_PIN, OUTPUT);              //On intialise le pin de la led des 4 éléments en sortie
digitalWrite(SLed_PIN, LOW);            //On éteint la led par défaut

pinMode(SPorteFinal_PIN, OUTPUT);       //On initialise le pin du relais de la porte final en sortie
digitalWrite(SPorteFinal_PIN, HIGH);    //On désactive le relais de la porte final par défaut

pinMode(ETerre_PIN, INPUT);             //On initialise le pin de la liaison de l'arduino Terre en entrée

pinMode(EFeu_PIN, INPUT);               //On initialise le pin de la liaison de l'arduino Feu en entrée

pinMode(EEau_PIN, INPUT);               //On initialise le pin de la liaison de l'arduino Eau en entrée

pinMode(EAir_PIN, INPUT);               //On initialise le pin de la liaison de l'arduino Air en entrée



  
}


void 4Elements::execute()
{



  
}






4Elements Mecanisme = 4Elemnts();        //On instancie un objet de type 4Elemnts 

void setup() {
  Mecanisme.setupMecanism();             //On donne un configuration de base au mécanisme
}

void loop() {
  delay(100);                           //On attend 0,1 sec
  Mecanisme.execute();                  //On exécute le mécanisme
}
