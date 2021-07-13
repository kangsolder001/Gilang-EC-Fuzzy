void kondisi(float def)
{
  waktuONWater = 0;
  waktuONABMIX = 0;
  bWater = false;
  bABMIX = false;
  bWaterOut = false;
  //  unsigned long waktu;

  Serial.println(def);
  int porsi;
  if ( def == 100)
  {
    porsi = 0;
    //donothing , karena nilainya sudah pas
  }
  else if ( def < 100)
  {
    porsi = 100 - def;
    Serial.print(porsi);
    //    waktu = porsi * 360; //500 ml = 25 ppm , 100 ppm = 2000 , 9000 ms / 500 ml, 36000 ms / 2000ml
    waktuONWater =  porsi * 1500.0; //  + tarikan awal;
    Serial.println("Pemberian AIR");

    Serial.print("Porsi = ");
    Serial.println(porsi);
    Serial.print("waktu = "); Serial.println(waktuONWater);
    pumpWaterOut();

  }
  else if ( def > 100)
  {
    porsi = def - 100;
    //    waktu = porsi * 106.8; // 5ml = 3000 ms, 10ml = 56ppm , 100 ppm = 17.8ml , 17.8 ml =10680 ms
    waktuONABMIX =  porsi * 55.0;
    Serial.print("mulai = ");
    Serial.println(millis());
    Serial.println("Pemberian ABMIX");
    Serial.print("Porsi = ");
    Serial.println(porsi);
    Serial.print("waktu = "); Serial.println(waktuONABMIX);
    pumpAB();
  }
}


void pumpWaterOut()
{
  digitalWrite(pumpWO, 0);
  Serial.println("=======================================================================================");
  Serial.println("Pompa Water OUT ON");
  Serial.print("mulai = ");
  Serial.println(millis());
  waterBegin = millis();
  bWaterOut = true;
}

void pumpWater()
{
  digitalWrite(pumpW, 0);
  Serial.println("=======================================================================================");
  Serial.print("mulai = ");
  Serial.println(millis());
  Serial.println("Pompa Water IN ON");
  waterBegin = millis();

  bWater = true;
}
void pumpAB()
{
  digitalWrite(pumpA, 0);
  digitalWrite(pumpB, 0);
  Serial.println("=======================================================================================");
  Serial.println("Pompa ABMIX ON");
  ABMIXBegin = millis();
  bABMIX = true;
}

void offPump()
{
  if (millis() - waterBegin >= waktuONWater && bWaterOut )
  {
    digitalWrite(pumpWO, 1);
    Serial.println("Pompa Water Out Off");
    Serial.println("=======================================================================================");
    Serial.print("Selesai = ");
    Serial.println(millis());
    bWaterOut = false;
    pumpWater();
    endFuzzy = millis();
    bTimeFuzzy = false;
  }
  else if (millis() - waterBegin >= waktuONWater && bWater )
  {
    digitalWrite(pumpW, 1);
    Serial.println("Pompa Water IN Off");
    Serial.println("=======================================================================================");
    Serial.print("Selesai = ");
    Serial.println(millis());
    bWater = false;
    endFuzzy = millis();
    bTimeFuzzy = false;
  }
  if ( millis() - ABMIXBegin >= waktuONABMIX && bABMIX)
  {
    digitalWrite(pumpA, 1);
    digitalWrite(pumpB, 1);
    Serial.println("pompa ABMIX Off");
    Serial.println("=======================================================================================");
    Serial.print("Selesai = ");
    Serial.println(millis());
    bABMIX = false;
    endFuzzy = millis();
    bTimeFuzzy = false;
  }
}
