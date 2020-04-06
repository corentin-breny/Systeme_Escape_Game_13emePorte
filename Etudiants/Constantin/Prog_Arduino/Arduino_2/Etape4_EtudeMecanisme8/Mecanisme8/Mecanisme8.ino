#include <Wire.h> // librairie permettant de communiquer via I2C

#define SLAVE_ADDRESS 0x19 // initialisation de l’Arduino avec l’adresse 0x19

bool mechanism_status = false;

bool S_Tableau = false;
bool S_Led = false;
bool actuator[] = {S_Tableau, S_Led};

void execute_order(String order){
  if(order[3] == 'T'){
    mechanism_status = true;
  }else if(order[3] == 'F'){
    mechanism_status = false;
  }

  for(int i=6; i<sizeof(order)+6; i++) {
    if(order[i] == 'T'){
      actuator[i-6] = true;
    }else if(order[i] == 'F'){
      actuator[i-6] = false;
    }
  }
}

void receive_order(int byteCount) {
  String data_received;
  while(Wire.available() > 0) {
    char c = Wire.read();
    data_received += String(c);
  }
  if(data_received != "2") {
    String order = data_received;
    Serial.print("Order received : ");
    Serial.println(order);//4MSTASFFFT.

    execute_order(order);
  }
}

void send_status() {
  String ms_I2Cmessage = "MS";
  String as_I2Cmessage = "AS";
  String I2Cmessage;
  
  if(mechanism_status == true){
    ms_I2Cmessage += "T";
  }
  else{
    ms_I2Cmessage += "F";
  }

  for(int i=0; i<sizeof(actuator); i++){
    if (actuator[i] == true){
      as_I2Cmessage += "T";
    }else{
      as_I2Cmessage += "F";
    }
  }
  
  I2Cmessage = ms_I2Cmessage + as_I2Cmessage;//MSTASFFFT
  
  Wire.write(I2Cmessage.c_str());
  Serial.print("Message send to Raspberry : ");
  Serial.println(I2Cmessage);
}


void setup() {
    Serial.begin(9600);
    Wire.begin(SLAVE_ADDRESS);
    Wire.onReceive(receive_order);
    Wire.onRequest(send_status);
}

void loop() {
    delay(100);
}
