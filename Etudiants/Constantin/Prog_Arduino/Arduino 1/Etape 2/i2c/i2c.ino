#include <Wire.h> // librairie permettant de communiquer via I2C

#define SLAVE_ADDRESS 0x12 // initialisation de l’Arduino avec l’adresse 0x12
int dataReceived = 0;


void receiveData(int byteCount){
    while(Wire.available()) {
        dataReceived = Wire.read();
        Serial.print("Donnee recue : ");
        Serial.println(dataReceived);
    }
}

void sendData(){
    int envoi = dataReceived + 2;
    Wire.write(envoi);
}


void setup() {
    Serial.begin(9600);
    Wire.begin(SLAVE_ADDRESS);
    Wire.onReceive(receiveData);
    Wire.onRequest(sendData);
}

void loop() {
    delay(100);
}
