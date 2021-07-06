#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <TimeLib.h>
#include <WiFiUdp.h>
#include <EEPROM.h>

#include<SoftwareSerial.h>
SoftwareSerial ard(D3, D4);

//=================WIFI================================
char auth[] = "c3xcE-dT6CFSx-nK0deEfQKDEfDFi6ht";
char ssid[] = "NOMOREDOTAFORTOMMOROW";   //sesuaikan ssid 
char pass[] = "N0m0r3d0t4"; // sesuaikan passwrod 

//======================NTP===============================
static const char ntpServerName[] = "id.pool.ntp.org";
const int timeZone = 7;
WiFiUDP Udp;
unsigned int localPort = 8888;
time_t getNtpTime();
void sendNTPpacket(IPAddress &address);

//=======================Blynk=========================
String dateBlynk;
int yB, mB, dB;
int yN, mN, dN;
int mon[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
BLYNK_WRITE(V0) // data tanggal input
{
  dateBlynk = param.asStr();
  Serial.print("Data Blynk:");
  Serial.println(dateBlynk);
  parsingDate(yB, mB, dB, dateBlynk);
}
unsigned long prevR;
float EC;


void setup() {
  ard.begin(9600);
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  ntpBegin();
}

void loop() {
  if ( year() == 1970 ) // mencocokan jam yang teraktual
  {
    ntpBegin();
  }
  readArd();



  if ( Serial.available() > 0)
  {
    String in = Serial.readStringUntil('\r');
    //    lcd.clear();
    EC = parsing(in);
    Blynk.virtualWrite(V1, EC);
  }

  if ( millis() - prevR > 500)
  {
    prevR = millis();
    int x = random(1, 100);
    Blynk.virtualWrite(V2, x);

    String jam = getTime();
    Serial.print("jam = ");
    Serial.println(jam);
    String ttl = getDate();
    Serial.print("ttl = ");
    Serial.println(ttl);
    parsingDate(yN, mN, dN, ttl);
    unsigned int selisih;
    int ytdB, ytdN, mtdB, mtdN;
    long  totalDayB = (yB * 365) + (mB * mon[mB - 1]) + dB;
    long totalDayN = (yN  * 365) + (mN * mon[mN - 1]) + dN;
    selisih = totalDayN - totalDayB; // umur tanaman 
    Serial.print("selisih hari = ");
    Serial.println(selisih);

    Blynk.virtualWrite(V3, selisih);
  }
  Blynk.run();
}
