//FICHIER RIZ H

#include "Wire.h"
#include <HX711.h>  //You must have this library in your arduino library folder

#define STableau_PIN 6   //relais tableau
#define SLedV_PIN 4      //led verte
#define SLedR_PIN 5      //led rouge
#define CPoids_DOUT 3    //capteur de poids
#define CPoids_CLK 2     //capteur de poids
//Change this calibration factor as per your load cell once it is found you many need to vary it in thousands
#define calibration_factor 20180; //-106600 worked for my 40Kg max scale setup

class Riz{

  private :
    bool S_Tableau;
    bool S_LedV;
    bool S_LedR;
    bool C_Poids;
    bool mechanism_status;

  private :
    bool actuator[3] = {S_Tableau, S_LedV, S_LedR};
    bool sensor[1] = {C_Poids};
  
  public :
    Riz();
    void setupMechanism();
    void execute();
    void receive_order();
    void send_status();
};

//FICHIER Riz CsPP

Riz::Riz(){
  S_Tableau = false;
  S_LedV = false;
  S_LedR = true;
  C_Poids = 0;
  mechanism_status = false;
}

void Riz::setupMechanism() {
  Serial.begin(9600);

  HX711 scale(DOUT, CLK);
  scale.set_scale();
  scale.tare(); //Reset the scale to 0

  pinMode(STableau_PIN, OUTPUT);
  digitalWrite(STableau_PIN, HIGH);
  
  pinMode(SLedV_PIN, OUTPUT); 
  digitalWrite(SLedV_PIN , LOW);

  pinMode(SLedR_PIN, OUTPUT);
  digitalWrite(SLedR_PIN, HIGH);
}

void Riz::execute(){
  scale.set_scale(calibration_factor); //Adjust to this calibration factor

  if (mechanism_status == false) {
    float C_Poids = (scale.get_units() / 2.0);
    delay(1000);
    float C_Poids_verif = (scale.get_units() / 2.0);


    if ( (C_Poids_verif >= (C_Poids - 0.03)) && (C_Poids_verif <= (C_Poids + 0.03)) ) {
      if ((C_Poids >= 0.48) && (C_Poids <= 0.52 )) {
        digitalWrite(SLedV_PIN, 200 );  // LED VERT
        digitalWrite(SLedR_PIN, 0);     // LED ROUGE
        digitalWrite(STableau_PIN, LOW);   // relais tableau métro
        delay(200);
        digitalWrite(STableau_PIN, HIGH);  // relais tableau métro
        delay(500);
        digitalWrite(STableau_PIN, LOW);   // relais tableau métro
        delay(200);
        digitalWrite(STableau_PIN, HIGH);  // relais tableau métro
        delay(500);
        digitalWrite(STableau_PIN, LOW);   // relais tableau métro
        delay(200);
        digitalWrite(STableau_PIN, HIGH);  // relais tableau métro
        mechanism_status = true;
      } else {
        digitalWrite(SLedV_PIN, 0 );    // LED VERT
        digitalWrite(SLedR_PIN, 200);   // LED ROUGE
        digitalWrite(STableau_PIN, HIGH);  // relais tableau métro
      }
    }
  }
}

void Riz::receive_order() {
  String data_received;
  while(Wire.available() > 0) {
    char c = Wire.read();
    data_received += String(c);
  }
  if(data_received != "2") {
    String order = data_received;
    Serial.print("Order received : ");
    Serial.println(order);//4MSTASFFFT.

    for(int i=1; i<sizeof(order)+1; i++) {
      if(order[i] == 'T'){
        actuator[i-1] = true;
      }else if(order[i] == 'F'){
        actuator[i-1] = false;
      }
    }
  }
}

void Riz::send_status() {
  String as_I2Cmessage = "as";
  String sd_I2Cmessage = "sd";
  String I2Cmessage;

  for(int i=0; i<sizeof(actuator); i++){
    if (actuator[i] == true){
      as_I2Cmessage += "T";
    }else{
      as_I2Cmessage += "F";
    }
  }
  if (as_I2Cmessage.length() < 6){
    for(int i=as_I2Cmessage.length()-1; i<5; i++){
      as_I2Cmessage += "X";
    }
  }
  
  for(int i=0; i<sizeof(sensor)/2; i++){
    sd_I2Cmessage += sensor[i];
    sd_I2Cmessage += "X";
  }

  I2Cmessage = as_I2Cmessage + sd_I2Cmessage;//asFFXXsdF
  
  Wire.write(I2Cmessage.c_str());
  Serial.print("Message send to Raspberry : ");
  Serial.println(I2Cmessage);
}

//FICHIER I2C H


#define SLAVE_ADDRESS 0x19  //initialisation de l’Arduino avec l’adresse 0x15

class i2c{

  private :
    Riz mechanism;
  public :
    i2c(Riz mechanism);
    void setupI2C();
};

//FICHIER I2C CPP

i2c::i2c(Riz mechanism){
  mechanism = mechanism;
}

void i2c::setupI2C() {
  Serial.begin(9600);
  Wire.begin(SLAVE_ADDRESS);
  /*Wire.onReceive(mechanism.receive_order);
  Wire.onRequest(mechanism.send_status);*/
}


//MAIN
Riz mechanism = Riz();
i2c message = i2c(mechanism);


void setup() {
  message.setupI2C();
  mechanism.setupMechanism();
}

void loop() {
  delay(100);
  mechanism.execute();
}
