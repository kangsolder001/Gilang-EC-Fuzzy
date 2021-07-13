void SendData(float EC)
{
  String dataSend = "|";
  dataSend += String(EC);
  dataSend += "|";
  dataSend += "\r";
  MCU.print(dataSend);
  Serial.println(dataSend);
}
void readMCU()
{
  if (MCU.available() > 0)
  {
    String in = MCU.readStringUntil('\r');
    Day = parsing( in);
    Serial.println( in);
  }
}

int parsing( String in)
{
  int out;
  int ind1, ind2;
  ind1 = in.indexOf('|');
  ind2 = in.indexOf('|', ind1 + 1);
  String output = in.substring(ind1 + 1 , ind2);

  out = output.toInt();
  return out;
}
