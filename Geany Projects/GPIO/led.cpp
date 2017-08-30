#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "wiringPi.h"
#include "wiringSerial.h"
#include "pigpio.h"

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
}

int main(void)
{

	return 0;
}

