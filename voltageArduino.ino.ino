double sensorValue ;
int avg = 0;
int led = 13;
int flag = 0;
float findVolt();
float volt;
int previousMillis = 0;
const long interval = 2000;


void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {

  volt = findVolt();
  unsigned long currentMillis = millis();
  if (volt >= 0.17) {
    Serial.println("Over volt ");
    digitalWrite(led, 0);
    flag = 1;

  }
  else if (volt <= 0.05) {
    Serial.println("Under Voltage ");
    digitalWrite(led, 0);
    flag = 1;
    //previousMillis = 0;
  }

  else {
    //previousMillis = currentMillis;

    Serial.println("  SAfe Level");
    //    Serial.println(currentMillis);

    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      Serial.println("Timer RESET");
    
    //digitalWrite(led, HIGH);
    
  }
}
}
float findVolt() {

  for (int i = 1; i <= 500; i++) {
    sensorValue = analogRead(A0);
    avg =  avg + sensorValue;
  }

  avg = avg / 500;
  double volt = avg * (5.0 / 1023.0);
  Serial.println(volt);
  return volt;
}

