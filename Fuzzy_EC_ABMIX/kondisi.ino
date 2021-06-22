void kondisi(float def)
{
  long porsi = abs(def / 100 * 130);
  Serial.print("Porsi = ");
  Serial.print(porsi);
  Serial.println("%");
  waktuONWater = 0;
  waktuONABMIX = 0;
  bWater = false;
  bABMIX = false;
  if ( def == 0)
  {
    //donothing , karena nilainya sudah pas
  }
  else if ( def < 0)
  {
    waktuONWater = porsi * 594; //  + tarikan awal;
    Serial.println("Pemberian AIR");
    Serial.print("waktu = "); Serial.println(waktuONWater);
    pumpWater();
    //    char buff[1000];
    //    sprintf(buff,"memberikan Air dengan porsi %f, dan waktu %f", porsi, waktuON);
    //    Serial.println(buff);
    //    Serial.print("Memberikan Air dengan Porsi = ");
    //    Serial.println(porsi);

    // mengurangi ppm sejumlah = def * 130
    // 33 ml / 1 ppm
    // 594 ms / 33 ml
    // 594 ms / 1 ppm

    // menambahkan air ( program penambahan air )
  }
  else if ( def > 0)
  {
    waktuONABMIX = porsi * 143;
    Serial.println("Pemberian ABMIX");
    Serial.print("waktu = "); Serial.println(waktuONABMIX);
    pumpAB();

    // 0.178 ml / 1 ppm
    // 248 ms / 0.178 ml
    // karena ada 2 carian jadi di bagi 2
    // 143 ms / 1 ppm
    // delay = porsi * 143
    // menambahkan ppm sejumlah = def * 130
    // menambahkan abmix ( program penambahan abmix )
    //    pompaON = millis();
    //    porsi = def * 130;
    //    waktuON =

  }
}

void pumpWater()
{
  digitalWrite(pumpW, 1);
  Serial.println("=======================================================================================");
  Serial.println("Pompa AIR ON");
  waterBegin = millis();
  bWater = true;
}
void pumpAB()
{
  digitalWrite(pumpA, 1);
  digitalWrite(pumpB, 1);
  Serial.println("=======================================================================================");
  Serial.println("Pompa ABMIX ON");
  ABMIXBegin = millis();
  bABMIX = true;
}

void offPump()
{
  if (millis() - waterBegin >= waktuONWater && bWater )
  {
    digitalWrite(pumpW, 0);
    Serial.println("Pompa AIR Off");
    Serial.println("=======================================================================================");
    bWater = false;
  }
  if ( millis() - ABMIXBegin >= waktuONABMIX && bABMIX)
  {
    digitalWrite(pumpA, 0);
    digitalWrite(pumpB, 0);
    Serial.println("pompa ABMIX Off");
    Serial.println("=======================================================================================");
    bABMIX= false;
  }
}
