float readTDS()
{
  float tdsValue;
  float temperature = 25;
  gravityTds.setTemperature(temperature);  // set the temperature and execute temperature compensation
  gravityTds.update();  //sample and calculate
  tdsValue = gravityTds.getTdsValue();  // then get the value
  Serial.print(tdsValue, 0);
  Serial.println("ppm");
  return tdsValue;
}
//float getTimestamp 
