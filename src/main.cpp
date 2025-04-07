#include <Arduino.h>
#include <IRremote.h>
#include <Stepper.h>

// IR sensor pin
const int RECV_PIN = 8;

// Stepper motor parameters
const int STEPS_PER_REV = 2048;  // Steps per revolution
const int MOTOR_SPEED = 10;      // Speed in RPM

// Pins for the ULN2003 driver
const int IN1 = 2;
const int IN2 = 3;
const int IN3 = 4;
const int IN4 = 5;

// Create Stepper object
Stepper stepper(STEPS_PER_REV, IN1, IN3, IN2, IN4);

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(RECV_PIN, ENABLE_LED_FEEDBACK);
  Serial.println("IR receiver started. Waiting for signals...");
  stepper.setSpeed(MOTOR_SPEED);
}

void loop() {
  if (IrReceiver.decode()) {
    Serial.print("Received signal: 0x");
    Serial.println(IrReceiver.decodedIRData.command, HEX);

    if (IrReceiver.decodedIRData.command == 0x9) { // POWER button detected
      Serial.println("Stepper motor rotates forward!");
      stepper.step(STEPS_PER_REV / 4); // 1/4 revolution forward
    }
    else if (IrReceiver.decodedIRData.command == 0x7) { // Other button
      Serial.println("Stepper motor rotates backward!");
      stepper.step(-STEPS_PER_REV / 4); // 1/4 revolution backward
    }

    IrReceiver.resume(); // Receive the next signal
  }
}
