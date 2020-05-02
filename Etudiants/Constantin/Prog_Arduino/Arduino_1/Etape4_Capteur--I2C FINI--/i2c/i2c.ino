#include <Wire.h> // librairie permettant de communiquer via I2C

#define SLAVE_ADDRESS 0x15 // initialisation de l’Arduino avec l’adresse 0x15

bool mechanism_status = false;

bool S_Dragon = false;
bool S_Fumee = false;
bool S_Led = false;
bool S_Feu = true;
bool actuator[] = {S_Dragon, S_Fumee, S_Led, S_Feu};

bool C_Interupteur = true;
bool sensor[] = {C_Interupteur};


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
  String ms_I2Cmessage = "ms";
  String as_I2Cmessage = "as";
  String sd_I2Cmessage = "sd";
  String I2Cmessage;

  if (mechanism_status == true){
    ms_I2Cmessage += "T";
  }else{
    ms_I2Cmessage += "F";
  }
  
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
  
  /*for(int i=0; i<sizeof(sensor)/2; i++){
    sd_I2Cmessage += sensor[i];
    sd_I2Cmessage += "X";
  }*/
  
  I2Cmessage = ms_I2Cmessage + as_I2Cmessage + sd_I2Cmessage; //msFasFFFFsdF
  
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
