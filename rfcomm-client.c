#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>
#include "time.h"

// Raspberry Pi MAC: "B8:27:EB:17:D1:DB"

int main(int argc, char **argv)
{
    struct sockaddr_rc addr = { 0 };
    int s, status;
    char dest[18] = "B8:27:EB:17:D1:DB";

    // allocate a socket
    s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

    // set the connection parameters (who to connect to)
    addr.rc_family = AF_BLUETOOTH;
    addr.rc_channel = (uint8_t) 1;
    str2ba( dest, &addr.rc_bdaddr );

    // connect to server
    status = connect(s, (struct sockaddr *)&addr, sizeof(addr));
    
    char user_input;
    int message;

    while (user_input != 'q')
    {
		scanf("%c",&user_input);
		//~ printf("Msg-%d",message);
		if( status == 0 || user_input != '\n') {
			status = write(s, &user_input, 6);
			printf("'%c' sent\n",user_input);
			//~ free(&user_input);
			
		}
		message = 0;
		user_input = ' ';
		if( status < 0 ) perror("uh oh");
	}
    close(s);
    return 0;
}
