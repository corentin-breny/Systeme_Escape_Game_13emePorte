//Fichier LionB.h

#include "WIRE.H"
#define SLAVE_ADDRESS 0x13
#define C_EffetHall1_PIN A0 //Capteur à effet Hall 1
#define S_Lion_PIN 3 //Led de sortie

int LIONBstate = HIGH; // Etat actuel de la broche de sortie (la LED)
int readingLIONB;         // Contient la valeur lue sur la broche d'entrée
int previousLIONB = LOW;
long timeLIONB = 0;      // La dernière fois que la broche de sortie à changé d'état
int LedLIONB = LOW;
long debounce = 2000;

class LionB {

  private :
    const int C_EffetHall1;
    bool S_Lion;
    bool mecanism_status;

  private :
    bool actuator[1] = {S_Lion};
    bool sensor[1] = {C_EffetHall1};
    bool getMechanism_status();
    void setMechanism_status(bool ms);

  public :
    LionB();
    void setupMecanism();
    void execute();
};

//Fichier LionB.cpp

LionB::LionB(){  
  C_EffetHall_1 = false;
  S_LedR = false;
  mecanism_status = false;
}

bool Echec::getMechanism_status(){
  return mechanism_status;
}

void Echec::setMechanism_status(bool ms){
  mechanism_status = ms;
}

void LionB::setupMechanism() {
  
  pinMode(10, OUTPUT); // vers led controle lionb
  digitalWrite(10, HIGH);
  
  pinMode( 3, OUTPUT); // Vers relais lionb
  digitalWrite(3, HIGH);
  
  pinMode(C_EffetHall, INPUT); // pin 6
  digitalWrite(C_EffetHall, HIGH);
  
  pinMode(11, INPUT_PULLUP);
  
  digitalWrite(hallPin, HIGH);  // Activation résistance pullUP
  digitalWrite(hallPin2, HIGH);
 
}

void LionB::execute(){
  
  pinlionb = digitalRead(C_EffetHall);

  readingLIONB = pinlionb;

  if (LIONBstate == HIGH)
  {
    if (readingLIONB != previousLIONB) 
    {  
      timeLIONB = millis();   // Remettre la minuterie/timer de déparasitage à 0
    }
    
    if ((millis() - timeLIONB) > (debounce)) // attendre que l'on ai dépassé le temps de déparasitage
    {    
      if (readingLIONB == HIGH) 
      {
        LIONBstate = LOW;   //Ce qui valide la réussite de l'énigme
        digitalWrite(3, LIONBstate);    //reset pour defaire le solenoide
        timeLIONB = millis();
        LedLIONB = HIGH;    //La led correspondante sur le panneau du superviseur est allumée
      }
    }

    previousLIONB = readingLIONB;   // Mémoriser la dernière lecture
  }
  else if ((millis() - timeLIONB) > debounce)
  {
    digitalWrite(3, HIGH);
    if (readingLIONB == LOW)
    LIONBstate = HIGH;
  }
  digitalWrite(10, LedLIONB);  
}

LionB mechanism = LionB();

void receive_order(int numBytes) {
  String data_received;
  
  while(Wire.available() > 0) {           //Tant que le message n'est pas fini
    char c = Wire.read();             //On lit le message
    data_received += String(c);
  }
  
  if(data_received != "2") {
    
    String order = data_received;
    Serial.print("Order received : ");
    Serial.println(order);//412221

    if(order[1] == '1'){              //Si le 2eme caractère est 1
      mechanism.setMechanism_status(true);    //On valide le mécanisme
    }else if(order[1] == '0'){            //Si le 2eme caractère est 0
      mechanism.setMechanism_status(false);   //On invalide le mécanisme
    }
    
    for(int i=2; i<sizeof(order); i++) {      //Pour chaque actionneur
      if(order[i] == '1'){            //Si le caractère est 1
        mechanism.actuator[i-1] = true;     //On valide l'actionneur
      }else if(order[i] == '0'){          //Si le caractère est 0
        mechanism.actuator[i-1] = false;    //On invalide l'actionneur
      }
    }
  }
}

void send_status() {
  String ms_I2Cmessage = "ms";
  String as_I2Cmessage = "as";
  String sd_I2Cmessage = "sd";
  String I2Cmessage;

  if(mechanism.getMechanism_status() == true){    //Si le mécanisme est validé
    ms_I2Cmessage += "T";             //On ajoute T au message i2c
  }else{                        //Si le mécanisme est invalide
    ms_I2Cmessage += "F";             //On ajoute F au message i2c
  }
  
  for(int i=0; i<sizeof(mechanism.actuator); i++){  //Pour chaque actionneur du mécanisme
    if (mechanism.actuator[i] == true){       //Si l'actionneur est validé
      as_I2Cmessage += "T";           //On ajoute T au message i2c
    }else{                      //Si l'actionneur est invalidé
      as_I2Cmessage += "F";           //On ajoute F au message i2c
    }
  }
  if(as_I2Cmessage.length() < 6){
    for(int i=as_I2Cmessage.length()-1; i<5; i++){  //Tant que le message est inférieur à 6 caractere
      as_I2Cmessage += "X";           //On ajoute X au message i2c
    }
  }

  /*//A COMMENTER SI LES CAPTEURS SONT DES VALEURS BOOLEAN
  for(int i=0; i<sizeof(mechanism.sensor); i++){    //Pour chaque capteur du mécanisme
    if (mechanism.sensor[i] == true){       //Si le capteur est validé
      sd_I2Cmessage += "T";           //On ajoute T au message i2c
    }else{                      //Si le capteur est invalidé
      sd_I2Cmessage += "F";           //On ajoute F au message i2c
    }
  }*/

  //A COMMENTER SI LES CAPTEURS SONT DES VALEURS NUMERIQUE
  for(int i=0; i<sizeof(sensor)/2; i++){        //Pour chaque capteur du mécanisme
    sd_I2Cmessage += sensor[i];           //On ajoute la valeur du capteur au message i2c
    sd_I2Cmessage += "X";             //Et on ajoute aussi X
  }
  
  I2Cmessage = ms_I2Cmessage + as_I2Cmessage + sd_I2Cmessage;//msFasFFFFsdF
  
  Wire.write(I2Cmessage.c_str());           //On envoie le message i2c
  Serial.print("Message send to Raspberry : ");
  Serial.println(I2Cmessage);
}

void setup() {
  Serial.begin(9600);
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receive_order);
  Wire.onRequest(send_status);
  mechanism.setupMechanism();
}

void loop() {
  delay(100);                     //On attends 0.1 seconde
  mechanism.execute();                //On exécute le mécanisme
}
