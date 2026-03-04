#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// Called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Depending on your servo make, the pulse width min and max may vary. 
// You may need to tweak these to get a true 0 to 180 degree range.
#define SERVOMIN  150 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // This is the 'maximum' pulse length count (out of 4096)

// Your specific PCA9685 Channels
int baseChannel = 15;
int elbowChannel = 14;
int shoulderChannel = 13;
int wristChannel = 12;

void setup() {
  Serial.begin(115200);
  
  pwm.begin();
  pwm.setOscillatorFrequency(27000000); // Standard for Adafruit PCA9685
  pwm.setPWMFreq(50);  // Analog servos run at ~50 Hz updates

  // Move to a safe 'Home' position (90 degrees)
  moveServo(baseChannel, 90);
  moveServo(shoulderChannel, 90);
  moveServo(elbowChannel, 90);
  moveServo(wristChannel, 90);
}

void loop() {
  // Listen for the 4 coordinates sent from Python
  if (Serial.available() > 0) {
    int b = Serial.parseInt(); // Base
    int s = Serial.parseInt(); // Shoulder
    int e = Serial.parseInt(); // Elbow
    int w = Serial.parseInt(); // Wrist
    
    // Check for the newline character that marks the end of the command
    if (Serial.read() == '\n') {
      moveServo(baseChannel, b);
      moveServo(shoulderChannel, s);
      moveServo(elbowChannel, e);
      moveServo(wristChannel, w);
    }
  }
}

// Custom function to convert 0-180 degrees into PCA9685 pulse lengths
void moveServo(int channel, int angle) {
  // Constrain the angle between 0 and 180 to prevent breaking the physical robot
  angle = constrain(angle, 0, 180);
  
  // Map the degree value to the pulse length
  int pulse = map(angle, 0, 180, SERVOMIN, SERVOMAX);
  
  // Send the signal to the specific channel
  pwm.setPWM(channel, 0, pulse);
}