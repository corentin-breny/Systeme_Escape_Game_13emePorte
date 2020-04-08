#include <Wire.h> // librairie permettant de communiquer via I2C

#define SLAVE_ADDRESS 0x15 // initialisation de l’Arduino avec l’adresse 0x15

#define CInterupteur_PIN 8  //interupteur a clef
#define SLed_PIN 9          //led controle
#define SDragon_PIN 10      //relais dragon
#define SFumee_PIN 11       //relais fumee
#define DEBOUNCE 500

bool S_Dragon = false;
bool S_Fumee = false;
bool S_Led = false;
bool S_Feu = true;
bool actuator[] = {S_Dragon, S_Fumee, S_Led, S_Feu};

bool C_Interupteur = false;
bool sensor[] = {C_Interupteur};

bool mechanism_status = false;

int sensor_data = LOW;        
bool sd_previous = false;     //Last sensor data
long ms_time = 0;             //Last time mechanism_status has changed


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

  I2Cmessage = as_I2Cmessage + sd_I2Cmessage;//asFFXXsdF
  
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

void execute(){
  sensor_data = digitalRead(CInterupteur_PIN);   // INTERUPTEUR CLEF
  
  if (sensor_data == HIGH){
    C_Interupteur = true;
  }
  
  // Si le contact à changé, est-ce causé par un changement de position OU un parasite (bille qui trésaute)... 
  if (C_Interupteur != sd_previous) {
  // Remettre la minuterie/timer de déparasitage à 0
    ms_time = millis();
  }
  
  // attendre que l'on ai dépassé le temps de déparasitage 
  if ((millis() - ms_time) > ((DEBOUNCE)/2)) {  
    Serial.print(digitalRead(CInterupteur_PIN));

    if (mechanism_status==false && C_Interupteur == true){
      //cathode_high();  //eteind led 7 digit //Envoyer un ordre à une autre arduino
        
      digitalWrite(SDragon_PIN, LOW); // Ventouse dragon
      delay(1000);
      digitalWrite(SDragon_PIN, HIGH);
      S_Dragon = true;
        
      delay(4000); // attend 5 sec
      digitalWrite(SFumee_PIN, LOW); //fumée on
      delay(1000);
      digitalWrite(SFumee_PIN,HIGH);//fumée off
      S_Fumee = true;
        
      delay(5000);
      mechanism_status = true; 
      digitalWrite(SLed_PIN, HIGH);
      S_Led = true;
      S_Dragon = true;
    } 
  }
  sd_previous = C_Interupteur;
}

void setupMechanism() {
  pinMode(CInterupteur_PIN , INPUT_PULLUP); 
  
  pinMode(SLed_PIN, OUTPUT); 
  digitalWrite(SLed_PIN , LOW);
    
  pinMode(SDragon_PIN, OUTPUT);
  digitalWrite(SDragon_PIN, HIGH);
  
  pinMode(SFumee_PIN, OUTPUT);
  digitalWrite(SFumee_PIN, HIGH);
}

void setup() {
    setupI2C();
    setupMechanism();
}

void loop() {
    delay(100);
    execute();
}
