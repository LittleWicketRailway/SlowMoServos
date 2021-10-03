// INCLUDE LIBRARIES
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

//SET PCA9685 BOARD ADDRESS
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(); //setup the board address - defaults to 0x40 if not specified

int Status[1]; //Create a table to hold the status of each turnout, signal, etc.

void setup()
{
  pinMode(5, INPUT_PULLUP);
  pwm.begin();
  pwm.setPWMFreq(50);
}

void loop()
{
  if (digitalRead(5) != Status[0])
  {
    if (digitalRead(5) == 1)
    {
        for (int i = 1000; i < 1900; i=i+1)
        {
            pwm.writeMicroseconds(0, i);
            //delay(10);
        }
        Status[0] = 1;
    }
    else
    {
        for (int i = 1900; i > 1000; i=i-1)
        {
            pwm.writeMicroseconds(0, i);
            //delay(10);
        }
        Status[0] = 0;
    }
  }
}
