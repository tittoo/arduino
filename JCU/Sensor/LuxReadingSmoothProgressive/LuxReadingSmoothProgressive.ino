
// Debug

const boolean leddebug = false;
const boolean calibratiedebug = false;

// variabelen instellen

const int numReadings = 20;   // 20   50
int readings[numReadings];    // het aantal waarden van de sensor
int index = 0;                // de index van de huidige meting
int total = 0;                // het progressieve totaal
int average = 0;              // het gemiddelde
int inputPin = A0;            //de pin met de sensor

//instellen lednummers en vergelijkingswaarden
const int Asize = 8;
int led[Asize] = {13, 8, 7, 6, 5, 4, 3};
int relatives[Asize] = {30, 200, 400, 600, 700, 800, 900};
const int Yksize = 43;
int from[Yksize] = {0, 690, 759, 761 ,780, 793, 806, 814, 821, 828, 836, 842, 847, 852, 856, 860, 864, 867, 874, 883, 886, 889, 891, 894, 898, 900, 903, 913, 919, 924, 929, 932, 936, 939, 941, 944, 946, 950, 953, 956, 958, 1023};
int to[Yksize] = {0, 240, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500, 1600, 1700, 1800, 1900, 2000, 2100, 2200, 2300, 2400, 2500, 2600, 2800, 3000, 3500, 4000, 4500, 5000, 5500, 6000, 6500, 7000, 7500, 9000, 10000, 11000, 12000, 13000, 20000};
int tussen;

//instellen resistor Ohm
float Res = 10.0;

void setup() {                
  // ledpinnen instellen als uitvoer
  for (int i = 0; i < (Asize - 1); i++) {
    pinMode(led[i], OUTPUT);
  }

  //aanzetten serial console
  Serial.begin(115200);       // 9600  115200
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;          
  }

  // debug options om ledjes te testen en de en de pin en vergelijk waarden
  while (leddebug) {
    for (int i = 0; i < (Asize - 1); i++) {
      digitalWrite(led[i], HIGH);
    }
    delay(1000);
    for (int i = 0; i < (Asize - 1); i++) {
      digitalWrite(led[i], LOW);
    }
    delay(1000);

    for (int i = 0; i < (Asize - 1); i++) {
      Serial.print(led[i]);
      Serial.print(" ");
      Serial.println(relatives[i]);
    }
  }
  Serial.println("");
  if (calibratiedebug) {
    Serial.println("{voltpoints,T,0}");
    Serial.println("{voltpoints,T,1023}");
  }
  Serial.println("{Lux,T,0}");
  Serial.println("{Lux,T,5000}");
}

void loop() {
  //lees 20 waarden, bereken het gemiddelde en stuur deze via de serial console
  total= total - readings[index];             // laatste waarde eraf
  readings[index] = analogRead(inputPin);     // lees de sensor
  total= total + readings[index];             // voeg de meting toe aan het totaal
  index = index + 1;                          // selecteer de volgende positie in de array  

  // als we aan het einde van de array zijn, begin dan opnieuw vooraan in de array
  if (index >= numReadings) {
    index = 0;               
  }

  average = total / numReadings;  // calculate the average:

  // stuur het resultaat naar de computer
  if (calibratiedebug) {
    Serial.print("{");
    Serial.print("voltpoints");
    Serial.print(",T,");
    Serial.print(average);                    
    Serial.println("}");
  }
  // bereken lux en print via serial
  for (int j = 0; j < (Yksize - 2); j++) {
    if (average >= from[j] && average <= from[j+1]) {
      tussen = j;
      break;
    }
  }

  int lux = map(average, from[tussen], from[(tussen + 1)], to[tussen], to[(tussen + 1)]);

  Serial.print("{");
  Serial.print("Lux");
  Serial.print(",T,");
  Serial.print(lux);                    
  Serial.println("}");

  // losse uitvoer als PC niet voor handen is.

  for (int i = 0; i < (Asize - 1); i++) {
    if (average > relatives[i]) {
      digitalWrite(led[i], HIGH);
    }
    else {
      digitalWrite(led[i], LOW);
    }
  }

  delay(1);
}



