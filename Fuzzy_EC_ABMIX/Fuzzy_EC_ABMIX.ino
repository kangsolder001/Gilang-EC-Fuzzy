#include <EEPROM.h>
#include "GravityTDS.h"
//#include <NTPClient.h>
//#include <WiFiUdp.h>
#include<SoftwareSerial.h>
//=======================SoftwareSerial================
SoftwareSerial MCU (2, 3); // rx , tx
//-----------------------NTP-----------------------------
//WiFiUDP ntpUDP;
//NTPClient timeClient(ntpUDP, "pool.ntp.org");
//unsigned long epochTime;
//====================POMPA=========================
#define pumpA 4
#define pumpB 5
#define pumpW 6
#define pumpWO 7
//-------------------nilai set point tds --------------------
#define sP1a 560
#define sP1b 600
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
#define sensPin A1
GravityTDS gravityTds;
//----------------------------------------------------------
float Error, deError;
boolean bWater, bWaterOut, bABMIX;
unsigned long waktuONWater, waktuONABMIX, waterBegin, ABMIXBegin, prevR;
void setup()
{
  Serial.begin(115200);
  MCU.begin(9600);
  pinMode(pumpA, OUTPUT);
  pinMode(pumpB, OUTPUT);
  pinMode(pumpW, OUTPUT);
  pinMode(pumpWO, OUTPUT);
  digitalWrite(pumpA,1);
  digitalWrite(pumpB,1);
  digitalWrite(pumpW,1);
  digitalWrite(pumpWO,1);
  Serial.println("Inisialisasi....!!!");
  gravityTds.setPin(sensPin);
  gravityTds.setAref(5.0);  //reference voltage on ADC, default 5.0V on Arduino UNO
  gravityTds.setAdcRange(1024);  //1024 for 10bit ADC;4096 for 12bit ADC
  gravityTds.begin();
//  timeClient.begin();
}

void loop()
{
  if (millis() - prevR > 500)
  {
    float tds = readTDS();
    Serial.print("TDS = ");
    Serial.println(tds);
    prevR = millis();
  }
  if ( Serial.available() > 0)
  {
    String in = Serial.readStringUntil('\r');
    float tds = in.toFloat();
    //    float tds = readTDS();
    float Er[3];
    float dEr[3];
    float rules[3][3];
    float Error_1 = Error;
    int sP;
    if ( tds <= sP1a )
    {
      sP = sP1a;
      Error = sP - tds; // Error = setpoint - nilai sensor (nilai sekarang )
      deError = Error - Error_1; // deError = nilai error sekarang - nilai error sebelumnya
    }
    else if ( tds >= sP1b)
    {
      sP = sP1b;
      Error = sP - tds;
      deError = Error - Error_1;
    }
    else
    {
      Error = 0;
      deError = 0;
    }

    EFuzzy(Error, Er);
    DeFuzzy(deError, dEr);
    Serial.print("tds     = "); Serial.println(tds);
    Serial.print("Error   = "); Serial.println(Error);
    Serial.print("deError = "); Serial.println(deError);
    //    outData(Er);
    //    outData(dEr);
    Rules(Er, dEr, rules);
    float defuz = Deffuzyfication(rules);
    kondisi(defuz);

    Serial.println("=======================================================================================");
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
