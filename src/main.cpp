//Author: Hieu Nguyen
//Email: edwardnguyen202@gmail.com
//TinkerCAD circuit: https://www.tinkercad.com/things/dCTIbrLsIua

#include <Arduino.h>
#define NUM_DIGIT 2

//Represent a two digit BCD number.
struct BCDNumber2
{
  unsigned char digits[NUM_DIGIT];	//Initialized to 0's by default
  
  //Post increment the bcd number by one
  BCDNumber2 operator++(int)
  {
    struct BCDNumber2 temp = *this;
    //Increment digit 0 and check if it's 0.
    if ((digits[0] = ++digits[0] % 10) == 0)
    {
      //Increment digit 1
      digits[1] = ++digits[1] % 10;
    }
    return temp;
  };

  //Combine two digits chars into a 8 bit BCD number consists of:
  //  4 least sig. bits are the 4 least sig. bits of digits[0]
  //  4 most sig. bits are the 4 least sig. bits of digits[1]
  unsigned char getVal()
  {
    return ((digits[0] & B00001111) | ((digits[1]<<4) & B11110000));
  }
};

//Ref. numbers, used to check the value of a bit of a another number
unsigned char bit[8];	

void setup()
{
  
  //Create the reference bits
  for (int i = 0; i < 8; i++)
  {
    bit[i] = (((unsigned char)1) << i);
  }

  //setup digital pins: pin 0 - 7 drive the LED, pin 8 controls the latch enable
  for (int i = 0; i < 9; i++)
  {
    pinMode(i, OUTPUT);
  }

  BCDNumber2 bcd2 = BCDNumber2();
  unsigned char bcdVal = 0;
  
  for (int _ = 0; _ < 100; _++)
  {
    delay(1000);
    bcd2++;
    bcdVal = bcd2.getVal();
    
    //Set the input of the 7-segment driver according to bcdVal
    for (int i = 0; i < 8; i++)
    {
      digitalWrite(i, (bcdVal & bit[i]) == 0 ? LOW : HIGH);
    }
    
    //latch to save the values of the input in CD4511's internal memory
    digitalWrite(8, LOW);
    digitalWrite(8, HIGH);
  }
}

void loop()
{
  //Do nothing
}