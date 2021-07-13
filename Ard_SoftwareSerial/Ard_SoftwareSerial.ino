#include <SoftwareSerial.h>

//=======================SoftwareSerial================
SoftwareSerial ard (3, 2); // rx , tx

void setup() {

  ard.begin(9600);
  Serial.begin(115200);
  // put your setup code here, to run once:

}

void loop() {
  if ( Serial.available() > 0)
  {
    String in = Serial.readStringUntil('\r');
    Serial.print("input = ");
    Serial.println(in);
    in = in + "\r";
    ard.print(in ) ;
  }
  if ( MCU.available() > 0)
  {
    String in = Serial.readStringUntil('\r');
    Serial.print("input dari MCU = ");
    Serial.println(in);
  }
  // put your main code here, to run repeatedly:

}
