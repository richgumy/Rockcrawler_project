#include <SoftwareSerial.h>

const int steeringA = 2;
const int steeringB = 3;
const int motorA = 4;
const int motorB = 5;

int motorSpeed = 200;
int steerDir = 255;

int time_delay = 400;

char msg;

void setupPins(void)
{
  pinMode(steeringA, OUTPUT);
  pinMode(steeringB, OUTPUT);
  pinMode(motorA, OUTPUT);
  pinMode(motorB, OUTPUT);
}

// 1 is reverse -1 is forward
void motorDrive(int dir)
{
  int speedB = dir > 0 ? dir : 0;
  int speedA = dir < 0 ? -dir : 0;

  analogWrite(motorA, speedA);
  analogWrite(motorB, speedB);
}

// 1 is left -1 is right
void steer(int dir)
{
  int speedA = dir > 0 ? dir : 0;
  int speedB = dir < 0 ? -dir : 0;

  analogWrite(steeringA, speedA);
  analogWrite(steeringB, speedB);
}

void resetAll(void)
{
  digitalWrite(steeringA, 0);
  digitalWrite(steeringB, 0);
  digitalWrite(motorA, 0);
  digitalWrite(motorB, 0);
}

void setup(void)
{
  pinMode(23, OUTPUT);
  digitalWrite(23, HIGH);
  setupPins();
  resetAll();
  Serial3.begin(9600);
  Serial3.println("Initialised.");
}

void loop(void)
{
  if (Serial3.available())
    // if text arrived in from Serial3 serial...
  {
    msg = Serial3.read();
    switch (msg)
    {
      case 'w':
        motorDrive(motorSpeed);
        delay(time_delay);
        resetAll();
        break;
      case 's':
        motorDrive(-motorSpeed);
        delay(time_delay);
        resetAll();
        break;
      case 'a':
        steer(steerDir);
        delay(time_delay);
        resetAll();
        break;
      case 'd':
        steer(-steerDir);
        delay(time_delay);
        resetAll();
        break;
    }
  }
}

