#include <Wire.h> // librairie permettant de communiquer via I2C
/*
Definir l'adresse corresondant à son mécanisme

#define SLAVE_ADDRESS 0x12  //pour le Mecanisme 1
#define SLAVE_ADDRESS 0x13	//pour le Mecanisme 2
#define SLAVE_ADDRESS 0x14	//pour le Mecanisme 3
#define SLAVE_ADDRESS 0x15	//pour le Mecanisme 4
#define SLAVE_ADDRESS 0x16	//pour le Mecanisme 5
#define SLAVE_ADDRESS 0x17	//pour le Mecanisme 6
#define SLAVE_ADDRESS 0x18	//pour le Mecanisme 7
#define SLAVE_ADDRESS 0x19	//pour le Mecanisme 8
#define SLAVE_ADDRESS 0x20	//pour le Mecanisme 9


EXEMPLE
pour le mecanisme 4:

#define SLAVE_ADDRESS 0x15

*/
bool mechanism_status = false;
/*
Definir ses sorties et les mettre dans un tableau

EXEMPLE:

bool S_Dragon = false;
bool S_Fumee = false;
bool S_Led = false;
bool S_Feu = true;

bool actuator[] = {S_Dragon, S_Fumee, S_Led, S_Feu};
*/

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
  
  I2Cmessage = ms_I2Cmessage + as_I2Cmessage;
  
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
