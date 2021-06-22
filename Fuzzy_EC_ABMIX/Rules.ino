void Rules(const float * E, const float * De, float rule[3][3])
{
  for (int i = 0; i < 3; i++) // i<3 , 0,1,2
  {
    for (int j = 0; j < 3; j++) // j<4, 0,1,2,3,4
    {
      rule[i][j] = min(E[i], De[j]); // 00 01
      String ruleout = "Rule [";
      ruleout += String(i);
      ruleout += "][";
      ruleout += String(j);
      ruleout += "]= ";
      ruleout += String(rule[i][j]);
      Serial.println(ruleout);
    }
  }
}
