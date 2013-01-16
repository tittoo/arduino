#include <PS2X_lib.h>

PS2X ps2x;

const int numReadings = 20;   // 20   50
int Yreadings[numReadings];    // het aantal waarden van de sensor
int index = 0;                // de index van de huidige meting
int Ytotal = 0;                // het progressieve totaal
int Yaverage = 0;              // het gemiddelde

int Xreadings[numReadings];    // het aantal waarden van de sensor
int Xtotal = 0;                // het progressieve totaal
int Xaverage = 0;   // het gemiddelde

int STBY = 10; //standby

//Motor A
int PWMA = 3; //Speed control 
int AIN1 = 9; //Direction
int AIN2 = 8; //Direction

//Motor B
int PWMB = 5; //Speed control
int BIN1 = 11; //Direction
int BIN2 = 12; //Direction

void setup() {
 Serial.begin(57600);
 ps2x.config_gamepad(6,2,7,4, false, false); 
 for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    Yreadings[thisReading] = 0;
    Xreadings[thisReading] = 0;    
  }
}

void loop() {
  ps2x.read_gamepad();
  byte preYvar = ps2x.Analog(PSS_RY);
  byte preXvar = ps2x.Analog(PSS_LX);
  int Yvar = int(preYvar);
  int Xvar = int(preXvar);
  
  Xtotal= Xtotal - Xreadings[index];
  Ytotal= Ytotal - Yreadings[index];             // laatste waarde eraf
  Xreadings[index] = Xvar;
  Yreadings[index] = Yvar;                       // lees de sensor
  Xtotal= Xtotal + Xreadings[index];
  Ytotal= Ytotal + Yreadings[index];             // voeg de meting toe aan het totaal
  
  index = index + 1;                           // selecteer de volgende positie in de array  

  // als we aan het einde van de array zijn, begin dan opnieuw vooraan in de array
  if (index >= numReadings) {
    index = 0;               
  }

  Xaverage = Xtotal / numReadings;
  Yaverage = Ytotal / numReadings;  // calculate the average:

  Serial.println(Yaverage);
  Serial.println(Xaverage);
  int directions = 0;
  int dir=0;
  if (Xaverage < 120){
    dir = map(Xaverage, 0, 128, 255, 0);
    directions = 2;
  }
  else if (Xaverage > 136) {
    dir = map(Xaverage, 128, 255, 0, 255);
    directions = 1;
  }
  
  if (Yaverage < 120){ 
    int velo = map(Yaverage, 0, 128, 255, 0);
    switch (directions) {
      case 1:
        move(1, (velo - dir), 0); //motor 1, full speed, left
        move(2, velo, 0); //motor 2, full speed, left
        break;
      case 2:
        move(1, velo, 0); //motor 1, full speed, left
        move(2, (velo - dir), 0); //motor 2, full speed, left
        break;
      default:
        move(1, velo, 0); //motor 1, full speed, left
        move(2, (velo), 0); //motor 2, full speed, left
    }
  }
  else if (Yaverage > 136) {
    int velo = map(Yaverage, 128, 255, 0, 255);
    switch (directions) {
      case 1:
        move(1, (velo - dir), 1); //motor 1, full speed, left
        move(2, velo, 1); //motor 2, full speed, left
        break;
      case 2:
        move(1, velo, 1); //motor 1, full speed, left
        move(2, (velo - dir), 1); //motor 2, full speed, left
        break;
      default:
        move(1, velo, 1); //motor 1, full speed, left
        move(2, (velo), 1); //motor 2, full speed, left
    }
  }
  else {
    stop();
  }
}

void move(int motor, int speed, int direction){
//Move specific motor at speed and direction
//motor: 0 for B 1 for A
//speed: 0 is off, and 255 is full speed
//direction: 0 clockwise, 1 counter-clockwise

  digitalWrite(STBY, HIGH); //disable standby

  boolean inPin1 = LOW;
  boolean inPin2 = HIGH;

  if(direction == 1){
    inPin1 = HIGH;
    inPin2 = LOW;
  }

  if(motor == 1){
    digitalWrite(AIN1, inPin1);
    digitalWrite(AIN2, inPin2);
    analogWrite(PWMA, speed);
  }else{
    digitalWrite(BIN1, inPin1);
    digitalWrite(BIN2, inPin2);
    analogWrite(PWMB, speed);
  }
}

void stop(){
//enable standby  
  digitalWrite(STBY, LOW);
}
