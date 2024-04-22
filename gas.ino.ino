#include <Stepper.h>

const int STEPS_PER_REVOLUTION = 200; // Change according to your stepper motor
const int stepperPin1 = 4;            // Digital pin for stepper motor control
const int stepperPin2 = 5;            // Digital pin for stepper motor control
const int stepperPin3 = 6;            // Digital pin for stepper motor control
const int stepperPin4 = 7;            // Digital pin for stepper motor control
const int gasSensorPin = A0;          // Analog pin for gas sensor
const int gasThreshold = 70;          // Gas threshold value
const int fanSpeed = 200;             // Adjust the speed of the "fan"
const int sensorDelay = 1000;         // Delay between sensor readings (in milliseconds)

Stepper stepper(STEPS_PER_REVOLUTION, stepperPin1, stepperPin2, stepperPin3, stepperPin4);

void setup() {
  Serial.begin(9600);  // Start serial communication
  stepper.setSpeed(fanSpeed); // Set stepper motor speed
}

void loop() {
  int gasValue = analogRead(gasSensorPin); // Read gas sensor value

  Serial.print("Gas Value: ");
  Serial.println(gasValue);

  if (gasValue > gasThreshold) {
    rotateStepper(); // Rotate stepper motor if gas threshold is exceeded
  }

  delay(sensorDelay); // Delay before taking the next sensor reading
}

void rotateStepper() {
  stepper.step(1); // Rotate stepper motor by one step
  delay(10);       // Adjust delay for desired "fan" speed
}
