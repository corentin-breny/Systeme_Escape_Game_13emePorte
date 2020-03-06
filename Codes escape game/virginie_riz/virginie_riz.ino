// ARDUINO 
// PESEE DU RIZ ET DRAGON
//
//  PIN 2 = SCK (HX711 CLK)
//  PIN 3 = DT
//  5V -> VCC
//  GND -> GND
//
//  PIN 4 = LED VERT (Riz)
//  PIN 5 = LED Rouge (Riz)
//  PIN 6 = RELAIS riz (Tableau métro)


// PIN A0 , A1 , A2 ,A3 ,A4 , A5 ,13 => 4 DIGIT   7,8.9.10.11.12.13

// PIN 8 Lecture interupteur clef   
// PIN 9 LED CONTROLE     
// PIN 10 RELAIS ventouse dragon    
// PIN 11 RELAIS Fumée    
// PIN 12 Selecteur afficheur LED     suppressible    




//
//
//



// INITIALISATION BALANCE ET RIZ

#include "HX711.h"  //You must have this library in your arduino library folder

#define DOUT  3
#define CLK  2

HX711 scale(DOUT, CLK);

//Change this calibration factor as per your load cell once it is found you many need to vary it in thousands
float calibration_factor = 20180; //-106600 worked for my 40Kg max scale setup

int firstriz = 0;


int state = HIGH; // Etat actuel de la broche de sortie (la LED)
int reading;      // Contient la valeur lue sur la broche d'entrée
int previous = LOW;
long time = 0;      // La dernière fois que la broche de sortie à changé d'état
long debounce = 500;



// INITIALISATON DRAGON


//4 Digit début:
int CA_1 = 13;
int CA_2 = digitalRead(A5);
int CA_3 = digitalRead(A4);
int CA_4 = digitalRead(A3);
int clk = digitalRead(A2);
int latch = digitalRead(A1);
int data = digitalRead(A0);
int count = 0;
int digits[4] ;
int CAS[4] = {13, A5, A4, A3};
byte numbers[10] {B11111100, B01100000, B11011010, B11110010, B01100110, B10110110, B10111110, B11100000, B11111110, B11110110};
//4 Digit Fin



const int clef = 8;
const int LED = 9;

int etatclef;
int first;

   


int etatselecteur = HIGH;
int previousetatselecteur = LOW;





void setup() {

  // SET UP DE LA BALANCE
  Serial.begin(9600);
  Serial.println("HX711 Calibration");
  Serial.println("Remove all weight from scale");
  Serial.println("After readings begin, place known weight on scale");
  Serial.println("Press a,s,d,f to increase calibration factor by 10,100,1000,10000 respectively");
  Serial.println("Press z,x,c,v to decrease calibration factor by 10,100,1000,10000 respectively");
  Serial.println("Press t for tare");
  scale.set_scale();
  scale.tare(); //Reset the scale to 0

  long zero_factor = scale.read_average(); //Get a baseline reading
  Serial.print("Zero factor: "); //This can be used to remove the need to tare the scale. Useful in permanent scale projects.
  Serial.println(zero_factor);
  

  pinMode( 4, OUTPUT ); // LED VERT RIZ
  pinMode (5, OUTPUT) ; // LED ROUGE RIZ
  pinMode (6, OUTPUT) ; // RELAIS RIZ

  digitalWrite(6 , HIGH);// RELAIS RIZ



// INITIALISATION DRAGON


pinMode(CA_1, OUTPUT);
  pinMode(CA_2, OUTPUT);
  pinMode(CA_3, OUTPUT);
  pinMode(CA_4, OUTPUT);
  pinMode(clk, OUTPUT);
  pinMode(latch, OUTPUT);
  pinMode(data, OUTPUT);
  digitalWrite(CA_1, HIGH);
  digitalWrite(CA_2, HIGH);
  digitalWrite(CA_3, HIGH);
  digitalWrite(CA_4, HIGH);
// 4 digit Fin


 pinMode(clef , INPUT_PULLUP); //inter Clef
 //etatclef = HIGH; 
 first=0;
 pinMode(LED, OUTPUT); //LED controle dragon
 digitalWrite(LED , LOW);  // a voir si regle PB led controle
 pinMode(10, OUTPUT); // Vers relais Ventouse DRagon
 digitalWrite(10, HIGH);
 pinMode(11, OUTPUT); //Vers relais fumée
 digitalWrite(11, HIGH);

 pinMode(12, INPUT_PULLUP);


  


}

void loop() {

  // @@@@@@@@@@ PESEE RIZ @@@@@@@@@@@@
  
  scale.set_scale(calibration_factor); //Adjust to this calibration factor

  float azerty;

  if (firstriz == 0) {
    float azerty = (scale.get_units() / 2.0);
    delay(1000);
    float azerty2 = (scale.get_units() / 2.0);


    if ( (azerty2 >= (azerty - 0.03)) && (azerty2 <= (azerty + 0.03)) ) {


      if ((azerty >= 0.48) && (azerty <= 0.52 )) {


        digitalWrite(4, 200 );  // LED VERT
        digitalWrite(5, 0); // LED ROUGE
        digitalWrite(6, LOW); // relais tableau métro
        delay(200);
        digitalWrite(6, HIGH); // relais tableau métro
        delay(500);
        digitalWrite(6, LOW); // relais tableau métro
        delay(200);
        digitalWrite(6, HIGH); // relais tableau métro
        delay(500);
        digitalWrite(6, LOW); // relais tableau métro
        delay(200);
        digitalWrite(6, HIGH); // relais tableau métro
        firstriz = 1;
      }

      else
      {
        digitalWrite(4, 0 );  // LED VERT
        digitalWrite(5, 200); // LED ROUGE
        digitalWrite(6, HIGH); // relais tableau métro

      }

    }


//     Serial.print("Reading: ");
// Serial.print(scale.get_units(), 2);
//  Serial.print (azerty);
//   Serial.print(" kg"); //Change this to kg and re-adjust the calibration factor if you follow SI units like a sane person
//  Serial.print(" calibration_factor: ");
// Serial.print(calibration_factor);
  }


//@@@@@@@@@@@@@@@@@@@@@@@@@DRAGON


etatselecteur = digitalRead(12);   // INTERUPTEUR selction difficulté
 
       // Si le contact à changé, est-ce causé par un changement de 
       // position OU un parasite (bille qui trésaute)... 
       if ( etatselecteur != previousetatselecteur) {
         // Remettre la minuterie/timer de déparasitage à 0
        time = millis();
       }
       // attendre que l'on ai dépassé le temps de déparasitage 
      if ((millis() - time) > (debounce)) {



 

            if ( etatselecteur == HIGH) {

digits[0] = 5;  //1er
digits[1] = 0;  //2eme
digits[2] = 8;  //3eme
digits[3] = 8;  //dernier
       }


            if ( etatselecteur == LOW) {

digits[0] = 3;  //1er
digits[1] = 0;  //2eme
digits[2] = 8;  //3eme
digits[3] = 8;  //dernier
       }

}

previousetatselecteur=etatselecteur;





       
// 4 Digit Appel de fonction et réglage délais
    //  break_number();
      display_number();
      delay(5);







// Clef dragon


etatclef = digitalRead( clef );   // INTERUPTEUR CLEF
  reading = etatclef;
       // Si le contact à changé, est-ce causé par un changement de 
       // position OU un parasite (bille qui trésaute)... 
       if (reading != previous) {
         // Remettre la minuterie/timer de déparasitage à 0
         time = millis();
       }
       // attendre que l'on ai dépassé le temps de déparasitage 
       if ((millis() - time) > ((debounce)/2)) {

    
Serial.print(digitalRead(8));

if (first==0){


if (etatclef==LOW){

  

  cathode_high();  //eteind led 7 digit
  digitalWrite(10 , LOW); // Ventouse dragon
  delay(1000);
  digitalWrite(10, HIGH);
 // delay(4000); // attend 5 sec
 
  digitalWrite(11, LOW); //fumée on
  delay(1000);
  digitalWrite(11,HIGH);//fumée off
  //delay(5000);
  first++; 
  state = LOW;
  }
//  else
//  {
//  digitalWrite(LED, LOW);  // LED CONTROLE
//  digitalWrite(7, HIGH);
//  }

} 
}

 digitalWrite(LED, not(state) ); // LED CONTROLE + LED Dragon
 previous= reading;
}




void break_number() { //4 digit: seperate the input number into 4 single digits

int etatselecteur ;
etatselecteur = digitalRead(12);   // INTERUPTEUR CLEF
 
       // Si le contact à changé, est-ce causé par un changement de 
       // position OU un parasite (bille qui trésaute)... 
       if ( etatselecteur != LOW) {
         // Remettre la minuterie/timer de déparasitage à 0
         time = millis();
       }
       // attendre que l'on ai dépassé le temps de déparasitage 
       if ((millis() - time) > (debounce)) {
 
digits[0] = 3;  //3eme
digits[1] = 1;  //1er
digits[2] = 2;  //2eme
digits[3] = 8;  //dernier
       }

              if ( etatselecteur != HIGH) {
         // Remettre la minuterie/timer de déparasitage à 0
         time = millis();
       }
       // attendre que l'on ai dépassé le temps de déparasitage 
       if ((millis() - time) > (debounce)) {
 
digits[0] = 3;  //3eme
digits[1] = 1;  //1er
digits[2] = 2;  //2eme
digits[3] = 4;  //dernier
       }
}


void display_number() { //4 DIGIT

  cathode_high(); //black screen
  digitalWrite(latch, LOW); //put the shift register to read
  shiftOut(data, clk, LSBFIRST, numbers[digits[count]]); //send the data
  digitalWrite(CAS[count], LOW); //turn on the relevent digit
  digitalWrite(latch, HIGH); //put the shift register to write mode
  //delay(5);
  count++; //count up the digit
  if (count == 2) { // keep the count between 0-3   @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  NOMBRE DE CHIFFRE AFFIC
    count = 0;
  }
}

void cathode_high() { //turn off all 4 digits
  digitalWrite(CA_1, HIGH);
  digitalWrite(CA_2, HIGH);
  digitalWrite(CA_3, HIGH);
  digitalWrite(CA_4, HIGH);

  
}
