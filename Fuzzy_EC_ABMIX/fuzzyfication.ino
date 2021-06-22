void EFuzzy( float er, float * output)
{
  //=======================KERING==================================
  if (er <= Er1) 
  {
    output[0] = 1;
  }
  else if (er > Er1 && er < Er2)
  {
    output[0] = (Er2 - er) / (Er2 - Er1);
  }
  else
  {
    output[0] = 0;
  }
  //=========================NORMAL=================================
  if (er > Er1 && er < Er2)  
  {
    output[1] = (er - Er1) / (Er2 - Er1);
  }
  else if (er == Er2)
  {
    output[1] = 1;
  }
  else if (er > Er2 && er < Er3)
  {
    output[1] = (Er3 - er) / (Er3 - Er2);
  }
  else
  {
    output[1] = 0;
  }

  //===========================TINGGI===============================
  if (er > Er2 && er < Er3)  
  {
    output[2] = (er - Er2) / (Er3 - Er2);
  }
  else if (er >= Er3)
  {
    output[2] = 1;
  }
  else
  {
    output[2] = 0;
  }
}

void DeFuzzy( float derror, float * output)
{
  //=======================Negatif Big==================================
  if (derror <= De1) 
  {
    output[0] = 1;
  }
  else if (derror > De1 && derror < De2)
  {
    output[0] = (De2 - derror) / (De2 - De1);
  }
  else
  {
    output[0] = 0;
  }
  //=========================Negatif Small=================================
  if (derror > De1 && derror < De2)  
  {
    output[1] = (derror - De1) / (De2 - De1);
  }
  else if (derror == De2 )
  {
    output[1] = 1;
  }
  else if (derror > De2 && derror < De3)
  {
    output[1] = (De3 - derror) / (De3 - De2);
  }
  else
  {
    output[1] = 0;
  }

  //===========================Zero===============================
  if (derror > De2 && derror < De3)  
  {
    output[2] = (derror - De2) / (De3 - De2);
  }
  else if (derror >= De3)
  {
    output[2] = 1;
  }
  else
  {
    output[2] = 0;
  }
  
}
