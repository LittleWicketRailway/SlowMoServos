// INCLUDE LIBRARIES
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

//SET PCA9685 BOARD ADDRESS
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(); //setup the board address - defaults to 0x40 if not specified

  int Status[4]; //Create a table to hold the status of each turnout, signal, etc. 
  int MinValue[4] = {1000,1000,1000,0};
  int MaxValue[4] = {1900,2000,2000,4096};
  int CurrentPosition[4];
  int StepSize[4] = {5,5,5,32};
  int DelayTime[4] = {10,30,30,0};
  unsigned long previousMillis[4];

void moveServos(int inputPin, int connection)
{
  unsigned long currentMillis = millis();
  if ((digitalRead(inputPin) != Status[connection]) && (currentMillis - previousMillis[connection] >= DelayTime[connection]))
  {
    previousMillis[connection] = currentMillis;
    if (digitalRead(inputPin) == 1)
    {
      if (CurrentPosition[connection] < MaxValue[connection])
      {
        CurrentPosition[connection] = CurrentPosition[connection] + StepSize[connection];
        pwm.writeMicroseconds(connection, CurrentPosition[connection]);
      }
      else
      {
          Status[connection]=1;
      }
    }
    else
    {
      if (CurrentPosition[connection] > MinValue[connection])
      {
        CurrentPosition[connection] = CurrentPosition[connection] - StepSize[connection];
        pwm.writeMicroseconds(connection, CurrentPosition[connection]);
      }
      else
      {
          Status[connection]=0;
      }
    }
  }
}

void setup()
{
  pinMode(5, INPUT_PULLUP); //Points level switch
  pinMode(6, INPUT_PULLUP); //IR Sensor
  for (int i = 0; i < 4; i=i+1)
  {
     CurrentPosition[i]=MinValue[i];
  }
  pwm.begin();
  pwm.setPWMFreq(50);
}

void loop()
{
  moveServos(5,0);
  moveServos(5,1);  
  moveServos(5,2);
  moveServos(6,3);   
}
