
// variabelen instellen

int led1 = 13;
int led2 = 3;
int led3 = 5;
int led4 = 7;
int led5 = 8;
int led6 = 10;
float Res = 10.0;
int smooth[20];

void setup() {                
  // ledpinnen instellen als uitvoer
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);  
  pinMode(led3, OUTPUT);  
  pinMode(led4, OUTPUT);  
  pinMode(led5, OUTPUT);  
  pinMode(led6, OUTPUT);
  //aanzetten serial console
  Serial.begin(9600);  
}

void loop() {
  //lees 20 waarden, bereken het gemiddelde en stuur deze via de serial console
  int i;
  for (i=0; i<19; i++) {
    smooth[i] = analogRead(A0);
  }
  int avg;
  for (i=0; i<19; i++) {
    avg = avg + smooth[i];
  }
  avg = avg/20;
  Serial.println(avg);
  // bereken lux en print via serial
  //   float  Vo = avg*0.004882813;
  //   int  lux=500/(Res*((5-Vo)/Vo));
  //  Serial.println(lux);

  // losse uitvoer als PC niet voor handen is.

  if (avg > 30) {
    digitalWrite(led1, HIGH);
  }
  else {
    digitalWrite(led1, LOW);
  }

  if (avg > 200) {
    digitalWrite(led2, HIGH);
  }
  else {
    digitalWrite(led2, LOW);
  }

  if (avg > 400) {
    digitalWrite(led3, HIGH);
  }
  else {
    digitalWrite(led3, LOW);
  }

  if (avg > 600) {
    digitalWrite(led4, HIGH);
  }
  else {
    digitalWrite(led4, LOW);
  }

  if (avg > 700) {
    digitalWrite(led5, HIGH);
  }
  else {
    digitalWrite(led5, LOW);
  }

  if (avg > 800) {
    digitalWrite(led6, HIGH);
  }
  else {
    digitalWrite(led6, LOW);
  }
}

