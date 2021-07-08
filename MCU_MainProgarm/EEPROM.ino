void savetoEeprom(int val, int address, int longAdd)
{
  
  byte n[5];
  byte s1, s2, s3, s4;
  if ( longAdd == 4)
  {
    n[1] = val / 1000;
    s1 = val % 1000;
    n[2] = s1 / 100;
    s2 = s1 % 100;
    n[3] = s2 / 10;
    s4 = s2 % 10;
    n[4] = s4 / 1;
  }
  else if ( longAdd == 2)
  {
    s2 = val % 100;
    n[1] = s2 / 10;
    s4 = s2 % 10;
    n[2] = s4 / 1;
  }
  int x = 1;
  for (int i = address; i < address + longAdd; i++)
  {
    EEPROM.write(i, n[x]);
    Serial.print("n" + String(i));
    Serial.println(n[x]);
    x++;
    EEPROM.commit();
  }
}
int readEEPROM(int address, int longAdd)
{
  String text;
  int nilai;
  for (int i = address; i < address + longAdd; i++)
  {
    int te = EEPROM.read(i);
    Serial.println(te);
    text += te;
  }
  nilai = text.toInt();
  return nilai;
}
