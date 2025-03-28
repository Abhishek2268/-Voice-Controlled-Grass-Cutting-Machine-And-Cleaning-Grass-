#include "AFMotor.h"

const int MOTOR_1 = 1; //motor pins 1 to 4
const int MOTOR_2 = 2; 
const int MOTOR_3 = 3; 
const int MOTOR_4 = 4; 

AF_DCMotor motor1(MOTOR_1, MOTOR12_64KHZ); // create motor object, 64KHz pwm
AF_DCMotor motor2(MOTOR_2, MOTOR12_64KHZ); // create motor object, 64KHz pwm
AF_DCMotor motor3(MOTOR_3, MOTOR12_64KHZ); // create motor object, 64KHz pwm
AF_DCMotor motor4(MOTOR_4, MOTOR12_64KHZ); // create motor object, 64KHz pwm

int state;
int Speed = 130; 

#define MOTOR1_DIR 1
#define MOTOR1_PWM 2
#define MOTOR2_DIR 3
#define MOTOR2_PWM 4

// Ultrasonic sensor pins
#define TRIG_PIN 9
#define ECHO_PIN 10

// Maximum distance to detect an object (in cm)
#define MAX_DISTANCE 20

// Create motor objects
//AF_DCMotor motor1(1);
//AF_DCMotor motor2(2);

void setup() {
motor1.setSpeed(Speed);   // set the motor speed to 0-255
motor2.setSpeed(Speed);
motor3.setSpeed(Speed);
motor4.setSpeed(Speed);  
Serial.begin(9600);
delay(500); 

Serial.begin(9600);

  // Set motor control pins as outputs
  pinMode(MOTOR1_DIR, OUTPUT);
  pinMode(MOTOR1_PWM, OUTPUT);
  pinMode(MOTOR2_DIR, OUTPUT);
  pinMode(MOTOR2_PWM, OUTPUT);

  // Set ultrasonic sensor pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);//
}

void loop(){   
if(Serial.available() > 0){  //if some date is sent, reads it and saves in state     
state = Serial.read();      
if(state > 10){Speed = state;}      
}
           
motor1.setSpeed(Speed);          // set the motor speed to 0-255
motor2.setSpeed(Speed);
motor3.setSpeed(Speed);
motor4.setSpeed(Speed);
   
//===============================================================================
//                          Key Control Command
//===============================================================================   
     if(state == 1){forword(); }  // if the state is '1' the DC motor will go forward
else if(state == 2){backword();}  // if the state is '2' the motor will Reverse
else if(state == 3){turnLeft();}  // if the state is '3' the motor will turn left
else if(state == 4){turnRight();} // if the state is '4' the motor will turn right
else if(state == 5){Stop(); }     // if the state is '5' the motor will Stop
/////////////////////////////////////END\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

//===============================================================================
//                          Voice Control Command
//===============================================================================
else if(state == 6){turnLeft();  delay(400);  state = 5;}
else if(state == 7){turnRight(); delay(400);  state = 5;}
/////////////////////////////////////END\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

delay(80);  

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Measure the time for sound to bounce back
  long duration = pulseIn(ECHO_PIN, HIGH);

  // Calculate distance in cm
  float distance = duration * 0.034 / 2;

  // Print distance for debugging
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Check if an object is detected within the maximum distance
  if (distance < MAX_DISTANCE) {
    // Stop the motors if an object is detected
    motor1.setSpeed(0);
    motor2.setSpeed(0);
    motor1.run(RELEASE);
    motor2.run(RELEASE);
  } else {
    // Move the robot car forward if no object is detected
    motor1.setSpeed(200);
    motor2.setSpeed(200);
    motor1.run(FORWARD);
    motor2.run(FORWARD);
  }

  delay(100); // Small delay for stability
}

void forword(){
motor1.run(FORWARD); // turn it on going forward
motor2.run(FORWARD); 
motor3.run(FORWARD); 
motor4.run(FORWARD);
}

void backword(){
motor1.run(BACKWARD); // the other way
motor2.run(BACKWARD);
motor3.run(BACKWARD); 
motor4.run(BACKWARD); 
}

void turnRight(){11111111111111
motor1.run(FORWARD); // the other right
motor2.run(FORWARD); 
motor3.run(BACKWARD); 
motor4.run(BACKWARD);
}

void turnLeft(){
motor1.run(BACKWARD); // turn it on going left
motor2.run(BACKWARD);
motor3.run(FORWARD); 
motor4.run(FORWARD); 
}

void Stop(){
 motor1.run(RELEASE); // stopped
 motor2.run(RELEASE);
 motor3.run(RELEASE);
 motor4.run(RELEASE);
}
