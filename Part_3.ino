// INCLUDE LIBRARIES
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

//SET PCA9685 BOARD ADDRESS
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(); //setup the board address - defaults to 0x40 if not specified

int Status[4]; //Create a table to hold the status of each turnout, signal, etc.
int MinValue[4]={1000,1000,1000,0};
int MaxValue[4]={1900,2000,2000,4096};
int CurrentPosition[4];
int Delay[4]={10,30,30,0};
int Step[4]={5,5,5,32};
unsigned long previousMillis[4];

void setup()
{
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  for (int i = 0; i < 4; i = i + 1)
  {
    CurrentPosition[i]=MinValue[i];
  }
  pwm.begin();
  pwm.setPWMFreq(50);
}

void loop()
{
  unsigned long currentMillis = millis();
  
  if (digitalRead(5) != Status[0] && (currentMillis - previousMillis[0] >= Delay[0]))
  {
    previousMillis[0] = currentMillis;
    if (digitalRead(5) == 1)
    {
        if (CurrentPosition[0] < MaxValue[0])
        {
            CurrentPosition[0] = CurrentPosition[0] + Step[0];
            pwm.writeMicroseconds(0, CurrentPosition[0]);
        }
        else
        {
            Status[0] = 1;         
        }
    }
    else
    {
        if (CurrentPosition[0] > MinValue[0])
        {
            CurrentPosition[0] = CurrentPosition[0] - Step[0];
            pwm.writeMicroseconds(0, CurrentPosition[0]);
        }
        else
        {
            Status[0] = 0;          
        }
    }
  }

  if (digitalRead(5) != Status[1] && (currentMillis - previousMillis[1] >= Delay[1]))
  {
    previousMillis[1] = currentMillis;
    if (digitalRead(5) == 1)
    {
        if (CurrentPosition[1] < MaxValue[1])
        {
            CurrentPosition[1] = CurrentPosition[1] + Step[1];
            pwm.writeMicroseconds(1, CurrentPosition[1]);
        }
        else
        {
            Status[1] = 1;         
        }
    }
    else
    {
        if (CurrentPosition[1] > MinValue[1])
        {
            CurrentPosition[1] = CurrentPosition[1] - Step[1];
            pwm.writeMicroseconds(1, CurrentPosition[1]);
        }
        else
        {
            Status[1] = 0;          
        }
    }
  }

  if (digitalRead(5) != Status[2] && (currentMillis - previousMillis[2] >= Delay[2]))
  {
    previousMillis[2] = currentMillis;
    if (digitalRead(5) == 1)
    {
        if (CurrentPosition[2] < MaxValue[2])
        {
            CurrentPosition[2] = CurrentPosition[2] + Step[2];
            pwm.writeMicroseconds(2, CurrentPosition[2]);
        }
        else
        {
            Status[2] = 1;         
        }
    }
    else
    {
        if (CurrentPosition[2] > MinValue[2])
        {
            CurrentPosition[2] = CurrentPosition[2] - Step[2];
            pwm.writeMicroseconds(2, CurrentPosition[2]);
        }
        else
        {
            Status[2] = 0;          
        }
    }
  }

  if (digitalRead(6) != Status[3] && (currentMillis - previousMillis[3] >= Delay[3]))
  {
    previousMillis[3] = currentMillis;
    if (digitalRead(6) == 1)
    {
        if (CurrentPosition[3] < MaxValue[3])
        {
            CurrentPosition[3] = CurrentPosition[3] + Step[3];
            pwm.writeMicroseconds(3, CurrentPosition[3]);
        }
        else
        {
            Status[3] = 1;         
        }
    }
    else
    {
        if (CurrentPosition[3] > MinValue[3])
        {
            CurrentPosition[3] = CurrentPosition[3] - Step[3];
            pwm.writeMicroseconds(3, CurrentPosition[3]);
        }
        else
        {
            Status[3] = 0;          
        }
    }
  }

}
