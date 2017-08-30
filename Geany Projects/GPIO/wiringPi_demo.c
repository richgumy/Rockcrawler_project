#include <wiringPi.h>
#include "stdio.h"

const int steeringA = 17;
const int steeringB = 27;
const int motorA = 23;
const int motorB = 24;

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
	int speedB = dir > 0? dir : 0;
	int speedA = dir < 0? -dir : 0;
	
	digitalWrite(motorA, speedA);
	digitalWrite(motorB, speedB);
}

// 1 is left -1 is right
void steer(int dir)
{
	int speedA = dir > 0? dir : 0;
	int speedB = dir < 0? -dir : 0;
	
	digitalWrite(steeringA, speedA);
	digitalWrite(steeringB, speedB);
}

void resetAll(void)
{
	digitalWrite(steeringA, 0);
	digitalWrite(steeringB, 0);
	digitalWrite(motorA, 1);
	digitalWrite(motorB, 1);
}

int main(void)
{
	wiringPiSetup();
	wiringPiSetupGpio();
	
	setupPins();
	
	printf("GPIO initialized\n");
	
	int steeringDir = 1;
	int tick = 0;
	
	motorDrive(1);
	
	while(tick < 50)
	{
		steer(steeringDir);
		motorDrive(1);
		delay(200);
		resetAll();
		delay(200);
		steeringDir = -steeringDir;
		tick++;
		delay(3000);
	}
	resetAll();
}
