#include <Wire.h> // librairie permettant de communiquer via I2C

#define SLAVE_ADDRESS 0x15 // initialisation de l’Arduino avec l’adresse 0x12
int dataReceived = 0;
bool etatMecanisme = true;


/*void receiveData(int byteCount){
    while(Wire.available()) {
        dataReceived = Wire.read();
        Serial.print("Donnee recue : ");
        Serial.println(dataReceived);
    }
}*/

void receiveData(int byteCount){
  Serial.print("data received: ");
        String strMsg;
  while(Wire.available() > 0) {
          char c = Wire.read();
    strMsg += String(c);
  }
  Serial.println();
  Serial.print(strMsg);
  Serial.println();
}

void sendEtatMecanisme(){
  String envoi;
  
  if(etatMecanisme == true){
    envoi = "MSTASFFFT";
  }else{
    envoi = "MSFASFFFF"; 
  }
  Wire.write(envoi.c_str());
  //Serial.print("Donnee envoye à Raspberry : ");
  //Serial.println(envoi);
  
}


void setup() {
    Serial.begin(9600);
    Wire.begin(SLAVE_ADDRESS);
    Wire.onReceive(receiveData);
    Wire.onRequest(sendEtatMecanisme);
}

void loop() {
    delay(100);
}
