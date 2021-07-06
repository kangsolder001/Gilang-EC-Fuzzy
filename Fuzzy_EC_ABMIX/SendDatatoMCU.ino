void SendData(float EC)
{
  String dataSend = "|";
  dataSend += String(EC);
  dataSend += "|";
  dataSend += "\r";
  MCU.print(dataSend);
  Serial.println(dataSend);
}
