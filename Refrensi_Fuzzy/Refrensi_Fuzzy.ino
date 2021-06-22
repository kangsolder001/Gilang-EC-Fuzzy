float error_1, error, dError, pwm, Sp = 40;
float anggotaErrorN, anggotadErrorN, anggotapwmN;
float anggotaErrorZ, anggotadErrorZ, anggotapwmZ;
float anggotaErrorP, anggotadErrorP, anggotapwmP;
float rule1, rule2, rule3, rule4a, rule4b, rule5, rule6, rule7;
int def;
float suhu;
int val;
void setup()
{
  Serial.begin(115200);
  // Serial.println(rule1);
  // Serial.println(rule2);
  // Serial.println(rule3);
  // Serial.println(rule4a);
  // Serial.println(rule4b);
  // Serial.println(rule5);
  // Serial.println(rule6);
  // Serial.println(rule7);
  // Serial.print(“\n”);
  //
  // Serial.println(anggotaErrorN);
  // Serial.println(anggotaErrorZ);
  // Serial.println(anggotaErrorP);
  // Serial.println(anggotadErrorN);
  // Serial.println(anggotadErrorZ);
  // Serial.println(anggotadErrorP);
  // Serial.println(anggotadErrorP);
  // Serial.println(anggotadErrorP);
  // Serial.println(anggotadErrorP);
  // Serial.print(“\n”);
  //
  //
}
void loop()
{
  // if (Serial.available()){
  // Sp = Serial.parseInt();
  // }
  if (Serial.available() > 0)
  {
    String in = Serial.readStringUntil('\r');
    float temp = in.toFloat();
    runFuzzy(temp);
    Serial.print("def = ");
    Serial.println(def);
    //    Serial.print(” “); Serial.print(Sp); Serial.print(” “); Serial.println(suhu);
  }
  //  runFuzzy();
  // Serial.print(” “); Serial.print(error); Serial.print(” “);
  // Serial.print(error_1); Serial.print(” “);
  //  Serial.print(def);
  //  Serial.print(” “); Serial.print(Sp); Serial.print(” “); Serial.println(suhu);
}
void bacaSuhu()
{
  val = analogRead(A0);
  suhu = val / 2.0479;
  delay(100);
}

void error_suhu_N()
{
  if (error <= -1) {
    anggotaErrorN = 1;
  } else if (error > -1 && error < 0) {
    anggotaErrorN = (0 - error) / 1;
  } else if (error >= 0) {
    anggotaErrorN = 0;
  }
}
void error_suhu_Z()
{
  if (error <= -1) {
    anggotaErrorZ = 0;
  } else if (error <= 0 && error >= -1) {
    anggotaErrorZ = (error + 1) / 1;
  }
  else if (error >= 0 && error < 1) {
    anggotaErrorZ = (1 - error) / 1;
  } else if (error >= 1) {
    anggotaErrorZ = 0;
  }
}
void error_suhu_P()
{
  if (error >= 1) {
    anggotaErrorP = 1;
  }
  else if (error < 1 && error > 0) {
    anggotaErrorP = (error - 0) / 1;
  }
  else if (error < 0 ) {
    anggotaErrorP = 0;
  }
}
void dError_suhu_N()
{
  if (dError <= -1) {
    anggotadErrorN = 1;
  } if (dError > -1 && dError <= 0) {
    anggotadErrorN = (0 - dError) / 1;
  } if (dError >= 0) {
    anggotadErrorN = 0;
  }
}
void dError_suhu_Z()
{
  if (error <= -1) {
    anggotadErrorZ = 0;
  } else if (dError <= 0 && dError > -1) {
    anggotadErrorZ = (dError + 1) / 1;
  }
  else if (dError >= 0 && dError < 1) {
    anggotadErrorZ = (1 - dError) / 1;
  } else if (dError >= 1) {
    anggotadErrorZ = 0;
  }
}
void dError_suhu_P()
{
  if (dError >= 1) {
    anggotadErrorP = 1;
  }
  else if (dError < 1 && dError > 0) {
    anggotadErrorP = (dError - 0) / 1;
  }
  else if (dError <= 0 ) {
    anggotadErrorP = 0;
  }
}
/*
  void outPWM_N(){
  if (pwm == 0){ anggotapwmN = 1;}
  if (pwm > 0 && pwm < 127.5 ){ anggotapwmN = (0-pwm)/80;}
  if (pwm == 127.5) {anggotapwmN = 0;}
  }
*/
void fuzifikasi()
{
  error_suhu_N();
  error_suhu_Z();
  error_suhu_P();
  dError_suhu_N();
  dError_suhu_Z();
  dError_suhu_P();
}
float Min (float a, float b)
{
  if (a < b) {
    return a;
  }
  else if (b < a) {
    return b;
  }
  else return a;
}
void rule()
{
  fuzifikasi();
  // rule1 If Error = N And dError = N Then Out N
  float x1 = Min (anggotaErrorN, anggotadErrorN);
  rule1 = 127.5 - (127.5 * x1);
  // rule2 If Error = N And dError = Z Then Out N
  float x2 = Min (anggotaErrorN, anggotadErrorZ);
  rule2 = 127.5 - (127.5 * x2) ;
  //If Error = Z And dError = N Then Out P
  float x3 = Min (anggotaErrorZ, anggotadErrorN);
  rule3 = 127.5 - (127.5 * x3) ;
  //If Error = Z And dError = Z Then Out Z
  float x4 = Min (anggotaErrorZ, anggotadErrorZ);
  rule4a = 85 + (42.5 * x4);
  rule4b = 170 - (42.5 * x4);
  //If Error = Z And dError = P Then Out P
  float x5 = Min (anggotaErrorZ, anggotadErrorP);
  rule5 = 127.5 + (127.5 * x5);
  //If Error = P And dError = Z Then Out P
  float x6 = Min(anggotaErrorP, anggotadErrorZ);
  rule6 = 127.5 + (127.5 * x6);
  //If Error = P And dError = P Then Out P
  float x7 = Min(anggotaErrorP, anggotadErrorP);
  rule7 = 127.5 + (127.5 * x7);
  def = ((x1 * rule1) + (x2 * rule2) + (x3 * rule3) + (x4 * rule4a) + (x4 * rule4b) + (x5 * rule5) + (x6 * rule6) + (x7 * rule7)) / (x1 + x2 + x3 + x4 + x4 + x5 + x6 + x7);
}
void runFuzzy(float arre)
{
  //
  //  bacaSuhu();

  error_1 = error;
  error = Sp - arre;
  
  dError = error - error_1;
  rule();
  Serial.print("error = ");
  Serial.println(error);
  Serial.print("deError = ");
  Serial.println(dError);
  //  analogWrite(5, def);
}
