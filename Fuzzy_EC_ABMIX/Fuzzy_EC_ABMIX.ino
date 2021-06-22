#include <EEPROM.h>
#include "GravityTDS.h"
#include <NTPClient.h>
#include <WiFiUdp.h>
#include<SoftwareSerial.h>
//=======================SoftwareSerial================
SoftwareSerial MCU (2, 3); // rx , tx
//-----------------------NTP-----------------------------
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");
unsigned long epochTime;
//====================POMPA=========================
#define pumpA 4
#define pumpB 5
#define pumpW 6
//-------------------nilai set point tds --------------------
#define sP1 560
#define sP2 750
#define sP3 900
//--------------------batas batas Error dan deError----------
#define Er1 -130
#define Er2  0
#define Er3  130
#define De1  -130
#define De2  0
#define De3  130
//-------------------------Sesor TDS-------------------------
#define sensPin A0
GravityTDS gravityTds;
//----------------------------------------------------------
float Error, deError;
boolean bWater, bABMIX;
unsigned long waktuONWater, waktuONABMIX, waterBegin, ABMIXBegin,prevR;
void setup()
{
  Serial.begin(115200);
  MCU.begin(9600);
  pinMode(pumpA, OUTPUT);
  pinMode(pumpB, OUTPUT);
  pinMode(pumpW, OUTPUT);
  Serial.println("Inisialisasi....!!!");
  gravityTds.setPin(sensPin);
  gravityTds.setAref(5.0);  //reference voltage on ADC, default 5.0V on Arduino UNO
  gravityTds.setAdcRange(1024);  //1024 for 10bit ADC;4096 for 12bit ADC
  gravityTds.begin();
  timeClient.begin();
}

void loop()
{
//  if (millis() - prevR > 500)
//  {
//    float tds = readTDS();
//    Serial.print("TDS = ");
//    Serial.println(tds);
//    prevR = millis();
//  }
  if ( Serial.available() > 0)
  {
    String in = Serial.readStringUntil('\r');
    float tds = in.toFloat();
    //    float tds = readTDS();
    float Er[3];
    float dEr[3];
    float rules[3][3];
    deError = Error;
    Error = sP1 - tds;
    EFuzzy(Error, Er);
    DeFuzzy(deError, dEr);
    Serial.print("tds     = "); Serial.println(tds);
    Serial.print("Error   = "); Serial.println(Error);
    Serial.print("deError = "); Serial.println(deError);
    outData(Er);
    outData(dEr);
    Rules(Er, dEr, rules);
    float defuz = Deffuzyfication(rules);
    kondisi(defuz);

  }
  offPump();
}

void outData(float* out)
{
  for (int i = 0; i <= 2; i++)
  {
    String dataout = "Data ";
    dataout += i;
    dataout += " = ";
    dataout += out[i];
    Serial.println(dataout);
  }
  Serial.println("=======================");
}
