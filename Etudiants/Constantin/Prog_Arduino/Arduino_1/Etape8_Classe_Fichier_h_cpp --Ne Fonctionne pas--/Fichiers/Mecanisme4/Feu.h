#pragma once

#include <Arduino.h>

#define CInterupteur_PIN 8  //interupteur a clef
#define SLed_PIN 9          //led controle
#define SDragon_PIN 10      //relais dragon
#define SFumee_PIN 11       //relais fumee
#define DEBOUNCE 500


int sensor_data = LOW;        
bool sd_previous = false;     //Last sensor data
long ms_time = 0;             //Last time mechanism_status has changed

class Feu{

  private :
    bool S_Dragon;
    bool S_Fumee;
    bool S_Led;
    bool S_Feu;
    bool C_Interupteur;
    bool mechanism_status;

  public :
    bool actuator[4] = {S_Dragon, S_Fumee, S_Led, S_Feu};
    bool sensor[1] = {C_Interupteur};
  
  public :
    Feu();
    void setupMechanism();
    void execute();
};
