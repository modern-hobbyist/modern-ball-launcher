/*
     Dog Ball Launcher ESC & Brushless Motor Controller
     by Charlie Steenhagen - Modern Hobbyist
     -----
     This code is rather simple, and could actually be simplified further by 
     removing one of the Motors. Both motors will actually be spinning at the 
     same speed, so there is no point having them on different pins. I did it
     just for clarity, but could be removed.
*/

#include <Servo.h>
#define MAX_VALUE 180
#define MIN_VALUE 90 
#define MIN_PULSE_LENGTH 90 // Minimum pulse length in µs
#define MAX_PULSE_LENGTH 180 // Maximum pulse length in µs
#define POT_PIN A2
#define MOTOR_1_PIN 9
#define MOTOR_2_PIN 10

Servo ESC;     // create servo object to control the ESC
Servo ESC_2;

int potValue;  // value from the analog pin

void setup() {
  pinMode(POT_PIN, INPUT);
  
  delay(2000);
  
  // Attach the ESC on pin 9 & 10
  ESC.attach(MOTOR_1_PIN,1000,2000); // (pin, min pulse width, max pulse width in microseconds) 
  ESC_2.attach(MOTOR_2_PIN, 1000, 2000);

  //Calibrate The ESC's by sending Max value then Min value
  ESC.write(MAX_PULSE_LENGTH);
  ESC_2.write(MAX_PULSE_LENGTH);
  delay(1000);
  ESC.write(MIN_PULSE_LENGTH);
  ESC_2.write(MIN_PULSE_LENGTH);
}

void loop() {
  potValue = analogRead(POT_PIN);

  // Maps the potValue from between 0 and 1023 to between 0 and 180
  potValue = map(potValue, 0, 1023, MIN_VALUE, MAX_VALUE);

  // Adds a buffer so the motors aren't trying to run at low values.
  if(potValue < 95) potValue = MIN_VALUE;
  
  ESC.write(potValue);
  ESC_2.write(potValue);
  
  delay(100);
}
