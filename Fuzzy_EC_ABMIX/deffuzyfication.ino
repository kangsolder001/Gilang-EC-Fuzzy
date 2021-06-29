float outRule(float rulein, int numRule)
{
  float valOut;
  if ( numRule == 1) //rule nilai negatif
  {
    valOut = 100 - (100 * rulein);
  }
  else if ( numRule == 2) // rule nilai zero
  {
    valOut = 67 + (33 * rulein);
  }
  else if ( numRule == 3) // rule nilai zero
  {
    valOut = 133 - (33 * rulein);
  }
  else if ( numRule == 4) // rule nilai positif
  {
    valOut = 100 + (100 * rulein);
  }
  Serial.print("valout = ");
  Serial.println(valOut);
  return valOut;

}
float Deffuzyfication(const float rule[3][3]) // waktu , caHardaya,SoftuHardu
{
  float sigmamiuxBobot;

  int N = 1;
  int Z1 = 2;
  int Z2 = 3;
  int P = 4;
  sigmamiuxBobot = (outRule(rule[0][0], N) * rule[0][0] + // rule1
                    outRule(rule[0][1], N) * rule[0][1] + // rule2
                    outRule(rule[0][2], N) * rule[0][2] + // rule3
                    outRule(rule[1][0], N) * rule[1][0] + // rule4
                    outRule(rule[1][1], Z1) * rule[1][1] + // rule5
                    outRule(rule[1][1], Z2) * rule[1][1] + // rule6
                    outRule(rule[1][2], P) * rule[1][2] + // rule7
                    outRule(rule[2][0], P) * rule[2][0] + // rule8
                    outRule(rule[2][1], P) * rule[2][1] + // rule9
                    outRule(rule[2][2], P) * rule[2][2]); // rule10

  Serial.print("sigmamiuxBobot = ");
  Serial.println(sigmamiuxBobot);
  float sigmamiu = 0;
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      sigmamiu += rule[i][j];
    }
  }
  sigmamiu = sigmamiu + rule[1][1];
  Serial.print("sigmamiu = ");
  Serial.println(sigmamiu);
  float Defuzification;
  Defuzification = sigmamiuxBobot / sigmamiu;
  Serial.print("Defuz = ");
  Serial.println(Defuzification);
  Serial.print("def = ");
  
  return Defuzification;
}
