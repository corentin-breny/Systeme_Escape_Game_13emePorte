#pragma once

#include <Arduino.h>
#include "Wire.h"
//#include "Feu.h"

#define SLAVE_ADDRESS 0x15  //initialisation de l’Arduino avec l’adresse 0x15

class i2c{

  private :
    //Feu mecanisme;
  public :
    i2c();
    void setupI2C();
    void receive_order();
    void send_status();
}

