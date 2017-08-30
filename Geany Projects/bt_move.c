/* 
 * Date - 30/08/2017
 * Author - Richie Ellingham
 * Program - Setup bt server then drive based on commands received
 * 
 */
#include <stdio.h>
#include <unistd.h>
#include <wiringPi.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

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

int main(int argc, char **argv)
{
	wiringPiSetup();
	wiringPiSetupGpio();
	
	setupPins();
	
	printf("GPIO initialized\n");
	
    struct sockaddr_rc loc_addr = { 0 }, rem_addr = { 0 };
    char buf[1024] = { 0 };
    int s, client, bytes_read;
    socklen_t opt = sizeof(rem_addr);

    // allocate socket
    s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

    // bind socket to port 1 of the first available 
    // local bluetooth adapter
    loc_addr.rc_family = AF_BLUETOOTH;
    loc_addr.rc_bdaddr = *BDADDR_ANY;
    loc_addr.rc_channel = (uint8_t) 1;
    bind(s, (struct sockaddr *)&loc_addr, sizeof(loc_addr));

    // put socket into listening mode
    listen(s, 1);
	printf("Listening\n");
	
    // accept one connection
    client = accept(s, (struct sockaddr *)&rem_addr, &opt);
	
    ba2str( &rem_addr.rc_bdaddr, buf );
    fprintf(stderr, "accepted connection from %s\n", buf);
    
	while (buf[0] != 'q')
	{
		memset(buf, 0, sizeof(buf));
		// read data from the client
		bytes_read = read(client, buf, sizeof(buf));
		if( bytes_read > 0 && isalpha(buf[0])) {
			printf("received [%c]\n", buf[0]);
			switch (buf[0])
			{
				case 'w':
					motorDrive(-1);
					delay(200);
					resetAll();
					break;
				case 's':
					motorDrive(1);
					delay(200);
					resetAll();
					break;
				case 'a':
					steer(1);
					delay(200);
					resetAll();
					break;
				case 'd':
					steer(-1);
					delay(200);
					resetAll();
					break;
			}			
		}
	}

    // close connection
    close(client);
    close(s);
    return 0;
}


