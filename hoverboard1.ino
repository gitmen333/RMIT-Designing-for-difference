/*  Arduino DC Motor Control - PWM | H-Bridge | L298N
         Example 02 - Arduino Robot Car Control
    by Dejan Nedelkovski, www.HowToMechatronics.com
*/

#define dir1 8
#define pwm1 10
#define pwm2 11
#define dir2 9


int motorSpeedA = 0;
int motorSpeedB = 0;

void setup() {
  pinMode(dir1, OUTPUT);
  pinMode(pwm1, OUTPUT);
  pinMode(pwm2, OUTPUT);
  pinMode(dir2, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int xAxis = analogRead(A1); // Read Joysticks X-axis
  int yAxis = analogRead(A0); // Read Joysticks Y-axis

  


  // Y-axis used for forward and backward control
  if (yAxis < 470) {
    // Set Motor A backward
    digitalWrite(dir1, HIGH);
    // Set Motor B backward
    digitalWrite(dir2, LOW);

    // Convert the declining Y-axis readings for going backward from 470 to 0 into 0 to 255 value for the PWM signal for increasing the motor speed
    motorSpeedA = map(yAxis, 470, 0, 0, 75);
    motorSpeedB = map(yAxis, 470, 0, 0, 75);
  }
  else if (yAxis > 550) {
    // Set Motor A forward
    digitalWrite(dir1, LOW);
 
    // Set Motor B forward
    digitalWrite(dir2, HIGH);

    // Convert the increasing Y-axis readings for going forward from 550 to 1023 into 0 to 255 value for the PWM signal for increasing the motor speed
    motorSpeedA = map(yAxis, 550, 1023, 0, 75);
    motorSpeedB = map(yAxis, 550, 1023, 0, 75);
  }
  // If joystick stays in middle the motors are not moving
  else {
    motorSpeedA = 0;
    motorSpeedB = 0;
  }

  //X-axis used for left and right control
  if (xAxis < 470) {
    
    // Convert the declining X-axis readings from 470 to 0 into increasing 0 to 255 value
    int xMapped = map(xAxis, 470, 0, 0, 75);
    // Move to left - decrease left motor speed, increase right motor speed
    motorSpeedA = motorSpeedA - xMapped;
    motorSpeedB = motorSpeedB + xMapped;
    // Confine the range from 0 to 255
    if (motorSpeedA < 0) {
      motorSpeedA = 0;
    }
    if (motorSpeedB > 75) {
      motorSpeedB = 75;
    }
    
  }
  if (xAxis > 550) {
    
    // Convert the increasing X-axis readings from 550 to 1023 into 0 to 255 value
    int xMapped = map(xAxis, 550, 1023, 0, 75);
    // Move right - decrease right motor speed, increase left motor speed
    motorSpeedA = motorSpeedA + xMapped;
    motorSpeedB = motorSpeedB - xMapped;
    // Confine the range from 0 to 255
    if (motorSpeedA > 125) {
      motorSpeedA = 125;
    }
    if (motorSpeedB < 0) {
      motorSpeedB = 0;
    }
  }
  // Prevent buzzing at low speeds (Adjust according to your motors. My motors couldn't start moving if PWM value was below value of 70)
  // if (motorSpeedA < 70) {
  //   motorSpeedA = 0;
  // }
  // if (motorSpeedB < 70) {
  //   motorSpeedB = 0;
  // }
  analogWrite(pwm1, motorSpeedA); // Send PWM signal to motor A
  analogWrite(pwm2, motorSpeedB); // Send PWM signal to motor B

  // Serial.print ("motor1 = ");
  // Serial.println (motorSpeedA);
  // Serial.print ("motor2 = ");
  // Serial.println (motorSpeedB);
  Serial.print ("Yaxis = ");
  Serial.println (yAxis);
  //   Serial.print ("X");
  // Serial.println (xAxis);
  // Serial.print ("Y");
  // Serial.println (yAxis);
}