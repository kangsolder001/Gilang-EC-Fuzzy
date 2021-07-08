#include <EEPROM.h>
#include "GravityTDS.h"
#include<SoftwareSerial.h>
//=======================SoftwareSerial================
SoftwareSerial MCU (3, 2); // rx , tx
//====================POMPA=========================
#define pumpA 4
#define pumpB 5
#define pumpW 6
#define pumpWO 7
//-------------------nilai set point tds --------------------
#define sP1a 560  // 10 -15
#define sP1b 600  // 10 -15
#define sP2a 750  // 16-23
#define sP2b 790  // 16-23
#define sP3a 900  //24-30
#define sP3b 940  //24-30
int SP1, SP2;
int Day, days;
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
float tds;
float Error, deError;
boolean bWater, bWaterOut, bABMIX, bFuzzy;
unsigned long waktuONWater, waktuONABMIX, waterBegin, ABMIXBegin, prevR, endFuzzy;
unsigned long delayFuzzy = 180000;
void setup()
{
  Serial.begin(115200);
  MCU.begin(9600);
  pinMode(pumpA, OUTPUT);
  pinMode(pumpB, OUTPUT);
  pinMode(pumpW, OUTPUT);
  pinMode(pumpWO, OUTPUT);
  digitalWrite(pumpA, 1);
  digitalWrite(pumpB, 1);
  digitalWrite(pumpW, 1);
  digitalWrite(pumpWO, 1);
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
    tds = readTDS();
    Serial.print("TDS = ");
    Serial.println(tds);
    prevR = millis();
    SendData(tds);
  }
  readMCU();

  //float tds = readTDS();
  float Er[3];
  float dEr[3];
  float rules[3][3];
  float Error_1 = Error;
  int sP;
  if ( (millis() - endFuzzy >= delayFuzzy) && !bFuzzy)
  {
    Serial.println("Fuzzy ON ");
    bFuzzy = true;
  }
  if ( Day != days)
  {
    days = Day;
    Serial.print("Day = ");
    Serial.println(Day);
    if ( Day >= 10 && Day <= 15)
    {
      SP1 = sP1a;
      SP2 = sP1b;
      bFuzzy = true;
    }
    else if ( Day >= 16 && Day <= 23)
    {
      SP1 = sP2a;
      SP2 = sP2b;
      bFuzzy = true;
    }
    else if ( Day >= 24 && Day <= 30)
    {
      SP1 = sP3a;
      SP2 = sP3b;
      bFuzzy = true;
    }
    else
    {
      SP1 = 0;
      SP2 = 0;
      bFuzzy = false;
    }
  }
  
  if ( bFuzzy )
  {
    if ( tds <= SP1 )
    {
      sP = SP1;
      Error = sP - tds; // Error = setpoint - nilai sensor (nilai sekarang )
      deError = Error - Error_1; // deError = nilai error sekarang - nilai error sebelumnya
    }
    else if ( tds >= SP2)
    {
      sP = SP2;
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
