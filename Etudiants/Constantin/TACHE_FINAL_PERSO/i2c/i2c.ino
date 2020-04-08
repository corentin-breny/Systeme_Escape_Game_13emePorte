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

/*
Definir ses sorties et les mettre dans un tableau

EXEMPLE:

bool S_Dragon = false;
bool S_Fumee = false;
bool S_Led = false;
bool S_Feu = true;

bool actuator[] = {S_Dragon, S_Fumee, S_Led, S_Feu};
*/

/* 
Definir ses capteurs et les mettre dans un tableau

EXEMPLE:

bool C_Interupteur = false;

bool sensor[] = {C_Interupteur};
*/

void execute_order(String order){
  for(int i=1; i<sizeof(order)+1; i++) {
    if(order[i] == 'T'){
      actuator[i-1] = true;
    }else if(order[i] == 'F'){
      actuator[i-1] = false;
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
  
  /*
   //DECOMMENTER SI sensor[] est un bool
   
  for(int i=0; i<sizeof(sensor); i++){
    if (sensor[i] == true){
      sd_I2Cmessage += "T";
    }else{
      sd_I2Cmessage += "F";
    }
  }
  */
  
  /*
   //DECOMMENTER SI sensor[] est un int
   
  for(int i=0; i<sizeof(sensor)/2; i++){
    sd_I2Cmessage += sensor[i];
    sd_I2Cmessage += "X";
  }*/

  I2Cmessage = as_I2Cmessage + sd_I2Cmessage;
  
  Wire.write(I2Cmessage.c_str());
  Serial.print("Message send to Raspberry : ");
  Serial.println(I2Cmessage);
}

void setupI2C() {
    Serial.begin(9600);
    Wire.begin(SLAVE_ADDRESS);
    Wire.onReceive(receive_order);
    Wire.onRequest(send_status);
}

void setup() {
    setupI2C();
}

void loop() {
    delay(100);
}
