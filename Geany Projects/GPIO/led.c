#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "wiringPi.h"
#include "wiringSerial.h"
#include "pigpio.h"
#include "time.h"

void setup(void)
{
	if (gpioInitialise() < 0)
	{
	// pigpio initialisation failed.
	}
	else
	{
	// pigpio initialised okay.
	}
	gpioSetMode(0,PI_OUTPUT);
	gpioSetMode(1,PI_OUTPUT);
}

int main(void)
{
	while (1)
	{
		gpioWrite(1, 1);
		delay(100);
		gpioWrite(1, 0);
	}
	return 0;
}

