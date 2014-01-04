#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial nss(2, 3); // (RX, TX)

Servo steeringServo;
Servo escServo;

int STEER_PIN = 6;
int ESC_PIN = 5;
int OFF_SWITCH = 21;

String escValues;
String steeringValues;
String rawValues;

const int ledPin = 11;

void setup() {

  digitalWrite(OFF_SWITCH, LOW);
  nss.begin(57600);
  Serial.begin(57600);
  escServo.attach(ESC_PIN);
  steeringServo.attach(STEER_PIN);
  Serial.println("Loaded... lets rock!");
}

void loop() {
  while(nss.available()) {
//      digitalWrite(ledPin, LOW);
   delay(10);
   if (nss.available() >0) {
    char c = nss.read();
    if (c != '&') {
//        digitalWrite(ledPin, HIGH);
      rawValues += c;
    } else {
      Serial.println(rawValues);
      processRawValues(rawValues); 
      rawValues = "";
    }
  }
}
}

void processRawValues(String rawValues) {
  String escFlag = "A";
  String steeringFlag = "B";
  String offFlag = "OFF";
//  steeringServo.detach();
//  escServo.detach();
  
  if (rawValues.indexOf(escFlag) != (-1)) {
    String sub = rawValues.substring(1);
    Serial.print("substring =" + sub);
    char carray[sub.length() + 1];
    sub.toCharArray(carray, sizeof(carray));
    int n = atoi(carray);
    escController(n); 
    
  } else if (rawValues.indexOf(steeringFlag) != (-1)) {
    String sub = rawValues.substring(1);
    Serial.print("substring =" + sub);
    char carray[sub.length() + 1];
    sub.toCharArray(carray, sizeof(carray));
    int n = atoi(carray);
    steeringController(n); 
  } else if (rawValues.indexOf(offFlag) != (-1)) {
     shutDown(); 
  }
}

void escController(int valueToSend) {
//  escServo.attach(ESC_PIN);
  escServo.writeMicroseconds(valueToSend); // for microseconds
}

void steeringController(int valueToSend) {
//  steeringServo.attach(STEER_PIN);
  steeringServo.write(valueToSend);
}

void shutDown() {
   digitalWrite(OFF_SWITCH, HIGH); 
}

String printValue(String value) {
 Serial.println(value); 
}
