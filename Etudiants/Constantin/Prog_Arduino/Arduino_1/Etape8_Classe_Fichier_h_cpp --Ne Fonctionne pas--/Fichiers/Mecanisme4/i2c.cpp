
#include "i2c.h"

i2c::i2c(){
  
}

void i2c::setupI2C(Feu mecanisme) {
  Serial.begin(9600);
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receive_order);
  Wire.onRequest(send_status);
}

void i2c::receive_order() {
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

void i2c::send_status() {
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
  
  for(int i=0; i<sizeof(sensor); i++){
    if (sensor[i] == true){
      sd_I2Cmessage += "T";
    }else{
      sd_I2Cmessage += "F";
    }
  }

  I2Cmessage = as_I2Cmessage + sd_I2Cmessage;//asFFXXsdF
  
  Wire.write(I2Cmessage.c_str());
  Serial.print("Message send to Raspberry : ");
  Serial.println(I2Cmessage);
}
