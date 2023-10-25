/*
 * ArduinoNunchukDemo.ino
 *
 * Copyright 2011-2013 Gabriel Bianconi, http://www.gabrielbianconi.com/
 *
 * Project URL: http://www.gabrielbianconi.com/projects/arduinonunchuk/
 *
 */

#include <Wire.h>
#include <ArduinoNunchuk.h>

#define BAUDRATE 19200

#define enA 10 //PWM for motor A (Right) 
#define in1 12 
#define in2 13
#define enB 11 //PWM for motor B (Left)
#define in3 8
#define in4 9

#define speaker 6 //(pwm)

int xAxis = 0;
int yAxis = 0;
int zButton = 0;


int motorSpeedA = 0;
int motorSpeedB = 0;

ArduinoNunchuk nunchuk = ArduinoNunchuk();


void honk(){
  analogWrite(speaker, 120);
}

void honkoff(){
  analogWrite(speaker, 0);
}

void setup()
{
  Serial.begin(BAUDRATE);
  nunchuk.init();

  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  pinMode(speaker, OUTPUT);
  
}

void loop()
{
  nunchuk.update();

//  Serial.print(nunchuk.analogX, DEC);
//  Serial.print(' ');
//  Serial.print(nunchuk.analogY, DEC);
//  Serial.print(' ');
//  Serial.print(nunchuk.accelX, DEC);
//  Serial.print(' ');
//  Serial.print(nunchuk.accelY, DEC);
//  Serial.print(' ');
//  Serial.print(nunchuk.accelZ, DEC);
//  Serial.print(' ');
//  Serial.print(nunchuk.zButton, DEC);
//  Serial.print(' ');
//  Serial.println(nunchuk.cButton, DEC);


  xAxis = nunchuk.analogX;
  yAxis = nunchuk.analogY;
  zButton = nunchuk.zButton;

  Serial.println(xAxis);
  Serial.println(yAxis);

  
   // Y-axis used for forward and backward control
  if (yAxis < 125) {
    // Set Motor A backward
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    // Set Motor B backward
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    // Convert the declining Y-axis readings for going backward from 470 to 0 into 0 to 255 value for the PWM signal for increasing the motor speed
    motorSpeedA = map(yAxis, 125, 38, 0, 100);  //the map values of the Y axis are very strange as the potenitometers in the nunchuck min and max values are 38-224 with a middle value of 130
    motorSpeedB = map(yAxis, 125, 38, 0, 100);
  }
  else if (yAxis > 135) {
    // Set Motor A forward
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    // Set Motor B forward
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    // Convert the increasing Y-axis readings for going forward from 550 to 1023 into 0 to 255 value for the PWM signal for increasing the motor speed
    motorSpeedA = map(yAxis, 135, 224, 0, 100);
    motorSpeedB = map(yAxis, 135, 224, 0, 100);
  }
  // If joystick stays in middle the motors are not moving
  else {
    motorSpeedA = 0;
    motorSpeedB = 0;
  }

  // X-axis used for left and right control
  if (xAxis < 120) {
    // Convert the declining X-axis readings from 470 to 0 into increasing 0 to 255 value
    int xMapped = map(xAxis, 120, 29, 0, 100);
    // Move to left - decrease left motor speed, increase right motor speed
    motorSpeedA = motorSpeedA + xMapped;
    motorSpeedB = motorSpeedB - xMapped;
    // Confine the range from 0 to 255
    if (motorSpeedA < 0) {
      motorSpeedA = 0;
    }
    if (motorSpeedB > 100) {
      motorSpeedB = 100;
    }
  }
  if (xAxis > 130) {
    // Convert the increasing X-axis readings from 550 to 1023 into 0 to 255 value
    int xMapped = map(xAxis, 130, 227, 0, 100);
    // Move right - decrease right motor speed, increase left motor speed
    motorSpeedA = motorSpeedA - xMapped;
    motorSpeedB = motorSpeedB + xMapped;
    // Confine the range from 0 to 255
    if (motorSpeedA > 100) {
      motorSpeedA = 100;
    }
    if (motorSpeedB < 0) {
      motorSpeedB = 0;
    }
  }
//  // Prevent buzzing at low speeds (Adjust according to your motors. My motors couldn't start moving if PWM value was below value of 70)
//  if (motorSpeedA < 70) {
//    motorSpeedA = 0;
//  }
//  if (motorSpeedB < 70) {
//    motorSpeedB = 0;
//  }
  analogWrite(enA, motorSpeedA); // Send PWM signal to motor A
  analogWrite(enB, motorSpeedB); // Send PWM signal to motor B

if(zButton == 1){
  honk();
  }
if(zButton == 0){
  honkoff();
}

Serial.println(zButton);
  
}
