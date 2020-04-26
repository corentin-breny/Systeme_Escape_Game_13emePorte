//Fichier Echec.h

#define C_EffetHall1_PIN A0 //Capteur à effet Hall 1
#define C_EffetHall2_PIN 2 //Capteur à effet Hall 2
#define S_LedR_PIN 3 //Led de sortie

class Echec{

  private :
    bool C_EffetHall1;
    bool C_EffetHall2;
    bool S_LedR;
    bool mecanism_status;

  private :
    bool actuator[3] = {S_LedR};
    bool sensor[1] = {C_EffetHall1};
    bool sensor[2] = {C_EffetHall2};    

  public :
    Echec();
    void setupMecanism();
    void execute();
    void receive_order();
    void send_status();    
};

//Fichier Echec.cpp

Echec::Echec(){
  
  C_EffetHall1 = false;
  C_EffetHall2 = false;
  S_LedR = false;
  mecanism_status = false;
}
