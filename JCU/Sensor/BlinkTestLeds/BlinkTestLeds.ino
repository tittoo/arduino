/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led1 = 13;
int led2 = 3;
int led3 = 5;
int led4 = 7;
int led5 = 8;
int led6 = 10;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);  
  pinMode(led3, OUTPUT);  
  pinMode(led4, OUTPUT);  
  pinMode(led5, OUTPUT);  
  pinMode(led6, OUTPUT);  
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(led1, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(500);
  digitalWrite(led2, HIGH);
    delay(500);
  digitalWrite(led3, HIGH);
    delay(500);
  digitalWrite(led4, HIGH);
    delay(500);
  digitalWrite(led5, HIGH);
    delay(500);
  digitalWrite(led6, HIGH);
  delay(1000);               // wait for a second
  digitalWrite(led1, LOW);    // turn the LED off by making the voltage LOW
    delay(500);
  digitalWrite(led2, LOW);
    delay(500);
  digitalWrite(led3, LOW);
    delay(500);
  digitalWrite(led4, LOW);
    delay(500);
  digitalWrite(led5, LOW);
    delay(500);
  digitalWrite(led6, LOW);
  delay(1000);               // wait for a second
}
