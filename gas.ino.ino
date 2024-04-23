#include <Servo.h>
#include <Stepper.h>

// Define pin numbers
#define TRIGGER_PIN      9
#define ECHO_PIN         10
#define BUZZER_PIN       8
#define SERVO_PIN        7
#define STEPPER_PIN_1    A0
#define STEPPER_PIN_2    A1
#define STEPPER_PIN_3    A2
#define STEPPER_PIN_4    A3
#define GAS_SENSOR_PIN   A4 // Analog pin for gas sensor

// Define constants
#define MAX_DISTANCE     200
#define BUZZER_FREQ      2000
#define SERVO_DELAY      15
#define STEPPER_STEPS    2048 // Adjust based on your stepper motor
#define GAS_THRESHOLD    100 // Adjust threshold based on sensor sensitivity

// Initialize objects
Servo servo;
Stepper stepper(STEPPER_STEPS, STEPPER_PIN_1, STEPPER_PIN_2, STEPPER_PIN_3, STEPPER_PIN_4);
long duration, distance;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  
  // Initialize pin modes
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(SERVO_PIN, OUTPUT);
}

void loop() {
  // Measure distance
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.034 / 2;

  // Print distance to serial monitor
  Serial.print("Distance: ");
  Serial.println(distance);

  // Activate buzzer and servo if object detected within specified range
  if (distance < MAX_DISTANCE) {
    tone(BUZZER_PIN, BUZZER_FREQ);
    delay(100);
    noTone(BUZZER_PIN);
    for (int angle = 0; angle <= 180; angle += 5) {
      servo.write(angle);
      delay(SERVO_DELAY);
    }
    for (int angle = 180; angle >= 0; angle -= 5) {
      servo.write(angle);
      delay(SERVO_DELAY);
    }
  }

  // Read gas sensor value
  int gasValue = analogRead(GAS_SENSOR_PIN);
  Serial.print("Gas Value: ");
  Serial.println(gasValue);
  
  // Check if gas value exceeds threshold
  if (gasValue > GAS_THRESHOLD) {
    // Gas detected, take necessary action
    Serial.println("Gas detected! Taking necessary action...");
    // For example, activate an alarm
    tone(BUZZER_PIN, BUZZER_FREQ);
    delay(1000);
    noTone(BUZZER_PIN);
    // Move stepper motor
    stepper.setSpeed(20); // Adjust speed as needed
    stepper.step(360); // Rotate stepper motor 360 degrees
    delay(1000); // Delay before resetting stepper motor position
    stepper.step(-360); // Reset stepper motor position
  }

  // Add a delay before next iteration
  delay(1000); // Adjust delay as needed
}
