#include <SoftwareSerial.h>
// NODE MCU 
//=======================SoftwareSerial================
SoftwareSerial MCU (D3, D4); // rx , tx

void setup() {

  MCU.begin(9600);
  
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
    MCU.print(in ) ;
  }
  if ( MCU.available() > 0)
  {
    String in = MCU.readStringUntil('\r');
    Serial.print("input dari Ard= ");
    Serial.println(in);
  }
  // put your main code here, to run repeatedly:

}
