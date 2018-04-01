#include <stdlib.h>

#define MAX_MSG_SIZE 128

enum {none, drive, steer, other};

typedef struct message_t{
  int type;
  char* data;
};

const int steeringA = 2;
const int steeringB = 3;
const int motorA = 4;
const int motorB = 5;

int mot_speed = 0;
int steer_ang = 0;

char* data_buf; //string that stores the incoming message
message_t message;

void setupPins(void)
{
  pinMode(steeringA, OUTPUT);
  pinMode(steeringB, OUTPUT);
  pinMode(motorA, OUTPUT);
  pinMode(motorB, OUTPUT);
}

void motorDrive(int forward)
{
  if (forward > 0) {
    analogWrite(motorA, forward);
  }
  if (forward < 0) {
    analogWrite(motorB, -forward);
  }
}

void steerRC(int left)
{
  if (left > 0) {
    analogWrite(steeringA, left);
  }
  if (left < 0) {
    analogWrite(steeringB, -left);
  }
}

void resetAll(void)
{
  digitalWrite(steeringA, 0);
  digitalWrite(steeringB, 0);
  digitalWrite(motorA, 0);
  digitalWrite(motorB, 0);
}



int decipherMessage(size_t msg_length)
{
  /*
   * If a message has a w in it and a subsequent number below
   * 256 that is the desired command
   */
  int sign = 0;
  if (data_buf[0] == 'w') {
    message.type = drive;
    sign = -1;
  }
  else if (data_buf[0] == 's') {
    message.type = drive;
    sign = 1;
  }
  else if (data_buf[0] == 'd') {
    message.type = steer;
    sign = -1;
  }
  else if (data_buf[0] == 'a') {
    message.type = steer;
    sign = 1;
  }
  else {
    //Serial.println("error deciphering message");
    return 0; // If a dud message comes through (not w or s) break out of function
  }
  for ( int i=1; i<msg_length; i++) {
    int num = data_buf[i] - '0';

    if (num <= 9 && num >= 0) {
      if (sign) {
        mot_speed += num*pow(10,msg_length-1-i);
      }
    }
  }
  mot_speed = mot_speed > 255? 255 : mot_speed;
  mot_speed *= (int)sign;
  return mot_speed;
}

void setup()
{
  Serial.begin(9600); //set baud rate
  Serial3.begin(9600); //set baud rate

  data_buf = (char*) malloc(MAX_MSG_SIZE); // Init buffer
  message.data = (char*) malloc(MAX_MSG_SIZE); // Init message_t buffer

  setupPins();
}

int tick = 0;

void loop()
{
  // READ STRING ALTERNATIVE:
  // - Dynamically allocate memory depending on message size.
  // - Store a buffer of messages, which can be sorted for scheduling
  // - Do scheduling (use Free RTOS? and new IDE?)
  // - Interrupts?
  mot_speed = 0;
  size_t num_chars = 0;

  if (Serial3.available()) {

    // Read message until return carriage or after 5 chars
    num_chars = Serial3.readBytesUntil('\r', data_buf, 5);
    for (int i=0;i<num_chars;i++) {
        Serial.print(data_buf[i]);
    }
    Serial.println();
    realloc(data_buf,num_chars);
    realloc(message.data,num_chars);
    //Serial.println(num_chars);
  }

  if ((int)num_chars > 0) {
    message.data = data_buf;
    mot_speed = decipherMessage((int)num_chars);
  }

  if (mot_speed) {
    //Serial.println(mot_speed);
    tick = 0;
  }

  if (!num_chars) {
    if (tick > 10000) {
      resetAll();
      tick = 0;
    }
    tick++;
  }

  if (message.type == drive) {
    motorDrive(mot_speed);
  }
  else if (message.type == steer){
    steerRC(mot_speed);
  }
}
