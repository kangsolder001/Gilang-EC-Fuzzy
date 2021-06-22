float Deffuzyfication(const float rule[3][3]) // waktu , caHardaya,SoftuHardu
{
  float sigmamiuxBobot;

  float K = -100;    // pemberian AIR
  float P = 0;  // donothing
  float L = 100;    // pemberian ABMIX 
  sigmamiuxBobot = (rule[0][0] * K + rule[0][1] * K + rule[0][2] * K +
                    rule[1][0] * K + rule[1][1] * P + rule[1][2] * L +
                    rule[2][0] * L + rule[2][1] * L + rule[2][2] * L );
                    
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
  Serial.print("sigmamiu = ");
  Serial.println(sigmamiu);
  float Defuzification;
  Defuzification = sigmamiuxBobot / sigmamiu;
  Serial.print("Defuz = ");
  Serial.println(Defuzification);
  return Defuzification;
}
