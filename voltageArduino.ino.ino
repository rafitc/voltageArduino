//=========================================================================//

double sensorValue;
int avg = 0;
int led = 13;
int flag = 0;
float findVolt();
float volt;
unsigned long endTime = 0;
unsigned long startTime = 0;
const long interval = 5000;

//=========================================================================//

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}

//=========================================================================//
// the loop routine runs over and over again forever:
void loop() {
  volt = findVolt();
  
  if (volt >= 0.17) {
    Serial.println("Over Voltage ");
    digitalWrite(led, 0);
    flag = 1;
    startTime = 0;

  }
  
  else if (volt <= 0.05) {
    Serial.println("Under Voltage ");
    digitalWrite(led, 0);
    flag = 1;
    startTime = 0;
  }

  else {
    if(flag == 1) { //only if transitioning from an OV or UV condition
      startTime = millis(); //start the timer
    }
    flag = 0;
  }

  if ((flag == 0) && ((millis() - startTime) >= interval)) {  //if the interval is exceeded
    startTime = millis(); //reset timer
    Serial.println("  Safe Level");
    digitalWrite(led,HIGH);
    //add rest of your code here to execute once after the timeout interval
  }
  
}

//=========================================================================//

float findVolt() {
  for (int i = 1; i <= 500; i++) {
    sensorValue = analogRead(A0);
    avg = avg + sensorValue;
  }

  avg = avg / 500;
  double volt = avg * (5.0 / 1023.0);
  Serial.println(volt);
  return volt;
}

//=========================================================================//
