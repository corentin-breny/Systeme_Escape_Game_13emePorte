//Fichier Terre.h

#define C_EffetHall_1_PIN 2 //Capteur à effet Hall 1
#define S_LedR_PIN A2 //Led de sortie
#define S_LedV_PIN A0 //Led de sortie

int pindoigt;
int DOIGTstate = HIGH; // Etat actuel de la broche de sortie (la LED)
int readingDOIGT;      // Contient la valeur lue sur la broche d'entrée
int previousDOIGT = LOW;
long timeDOIGT = 0;      // La dernière fois que la broche de sortie à changé d'état
long time = 0;      // La dernière fois que la broche de sortie à changé d'état
long debounce = 2000; // Temps de déparasitage (debounce time), a augmenter si la sortie clignote.
// Les variables suivantes sont de type "long" parce que nous allons mesure le temps (en milisecondes).
// Ce temps deviendra vite de grands nombres qui ne pourrons pas être stockés dans un simple entier (type "int").
int state = HIGH; // Etat actuel de la broche de sortie (la LED)
int reading;      // Contient la valeur lue sur la broche d'entrée
int previous = LOW;

class Terre {

  private :
    const int C_EffetHall_1;
    bool S_LedR;
    bool S_LedV;
    bool mecanism_status;

  private :
    bool actuator[2] = {S_LedR, S_LedV};
    bool sensor[1] = {C_EffetHall_1};
    const int C_EffetHall_1 = 2;
    bool getMechanism_status();
    void setMechanism_status(bool ms);


  public :
    Terre();
    void setupMecanism();
    void execute();
};

//Fichier Terre.cpp

Terre::Terre(){  
  C_EffetHall_1 = false;
  S_LedR = false;
  S_LedV = false;
  mecanism_status = false;
}

void LionB::setupMechanism() {
  
  pinMode(4, OUTPUT); // Vers led controle doigt
  pinMode (3 , OUTPUT); // Vers relais doigt
  pinMode (C_EffetHall_1, INPUT); // pin2
  digitalWrite(C_EffetHall_1, HIGH);
  
  pinMode (A0 , OUTPUT);
  digitalWrite (A0, LOW);  // LED exit vert

  pinMode (A2 , OUTPUT);
  digitalWrite (A2, LOW);  // LED exit rouge
 
}

void LionB::execute(){
  
  pindoigt = digitalRead(C_EffetHall_1);  // lecture du capteur a Effet Hall

  readingDOIGT = pindoigt;

  if (readingDOIGT != previousDOIGT) 
  { 
    timeDOIGT = millis();  // Remettre la minuterie/timer de déparasitage à 0
  }
  
  if ((millis() - timeDOIGT) > (debounce / 3)) // attendre que l'on ai dépassé le temps de déparasitage
  {
    if ((pindoigt == LOW)) 
    {
      digitalWrite(4, HIGH); //LED CONTROLE doigt
      DOIGTstate = LOW;
    }
  }
  if (pindoigt == HIGH)
  {
    DOIGTstate = HIGH;
  }

  digitalWrite(3, DOIGTstate );

  previousDOIGT = readingDOIGT;  
}


Terre mechanism = Terre();

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
