void readArd()
{
  if ( ard.available() > 0)
  {
    String in = Serial.readStringUntil('\r');

    EC = parsing(in);
  }
}
void sendToArd(int nDay)
{
  String dataSend = "|";
  dataSend += String(nDay);
  dataSend += "|/r";
  ard.print(dataSend);
  Serial.println(dataSend);
}
float parsing( String in)
{
  float ec;
  int ind1, ind2;
  ind1 = in.indexOf('|');
  ind2 = in.indexOf('|', ind1 + 1);
  String output = in.substring(ind1 + 1 , ind2);

  ec = output.toFloat();
  return ec;
}

void parsingDate(int &yy, int &mm, int &dd, String dateBlynk)
{
  int ind1, ind2;
  ind1 = dateBlynk.indexOf('/');
  ind2 = dateBlynk.indexOf('/', ind1 + 1);
  String YY = dateBlynk.substring(0, ind1);
  String MM = dateBlynk.substring(ind1 + 1, ind2);
  String DD = dateBlynk.substring(ind2 + 1, dateBlynk.length());
  yy = YY.toInt();
  mm = MM.toInt();
  dd = DD.toInt();
  //  Serial.print("year = ");
  //  Serial.println(yy);
  //  Serial.print("month = ");
  //  Serial.println(mm);
  //  Serial.print("date = ");
  //  Serial.println(dd);
}
