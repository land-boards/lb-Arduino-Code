#ifndef __BINARYUTILS_H_
#define __BINARYUTILS_H_

void printBinaryNIBBLE(byte pWord){
  Serial.print("[ ");
  int count=0;
  for(byte mask = 0x8; mask; mask >>= 1)
  {  
    if(mask  & pWord)
    {
      Serial.print('1');
    }
    else
    {
      Serial.print('0');
    } 
    count++;
    if(count == 4) 
    {
       Serial.print(" ");
       count=0;
    }
  }
  Serial.print("]");
}

void printBinaryWORD(unsigned int pWord){
  Serial.print("[ ");
  int count=0;
  for(int mask = 0x80; mask; mask >>= 1)
  {  
    if(mask  & pWord)
    {
      Serial.print('1');
    }
    else
    {
      Serial.print('0');
    } 
    count++;
    if(count == 4) 
    {
       Serial.print(" ");
       count=0;
    }
  }
  Serial.print("]");
}

void printBinaryDWORD(unsigned long pWord){
  Serial.print("[ ");
  int count=0;
  for(long mask = 0x8000; mask; mask >>= 1)
  {  
    if(mask  & pWord)
    {
      Serial.print('1');
    }
    else
    {
      Serial.print('0');
    } 
    count++;
    if(count == 4) 
    {
       Serial.print(" ");
       count=0;
    }
  }
  Serial.print("]");
}

void printBinaryQWORD(unsigned long long pWord){
  Serial.print("[ ");
  int count=0;
  for(long long mask = 0x80000000; mask; mask >>= 1)
  {  
    if(mask  & pWord)
    {
      Serial.print('1');
    }
    else
    {
      Serial.print('0');
    } 
    count++;
    if(count == 4) 
    {
       Serial.print(" ");
       count=0;
    }
  }
  Serial.print("]");
}


#endif
