#include <Arduino.h>
#include <IRremote.h>
#include <Stepper.h>

// IR Sensor Pin
const int RECV_PIN = 8;

// Schrittmotor-Parameter
const int STEPS_PER_REV = 2048; // Schritte pro Umdrehung
const int MOTOR_SPEED = 10;      // Geschwindigkeit in U/min

// Pins für den ULN2003 Treiber
const int IN1 = 2;
const int IN2 = 3;
const int IN3 = 4;
const int IN4 = 5;

// Stepper-Objekt erstellen
Stepper stepper(STEPS_PER_REV, IN1, IN3, IN2, IN4);

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(RECV_PIN, ENABLE_LED_FEEDBACK);
  Serial.println("IR-Empfänger gestartet. Warten auf Signale...");
  stepper.setSpeed(MOTOR_SPEED);
}

void loop() {
  if (IrReceiver.decode()) {
    Serial.print("Empfangenes Signal: 0x");
    Serial.println(IrReceiver.decodedIRData.command, HEX);

    if (IrReceiver.decodedIRData.command == 0x9) { // POWER-Taste erkannt
      Serial.println("Schrittmotor dreht sich vorwärts!");
      stepper.step(STEPS_PER_REV / 4); // 1/4 Umdrehung vorwärts
    }
    else if (IrReceiver.decodedIRData.command == 0x7) { // Andere Taste
      Serial.println("Schrittmotor dreht sich rückwärts!");
      stepper.step(-STEPS_PER_REV / 4); // 1/4 Umdrehung rückwärts
    }

    IrReceiver.resume(); // Nächstes Signal empfangen
  }
}
