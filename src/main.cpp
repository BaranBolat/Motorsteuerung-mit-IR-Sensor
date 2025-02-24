#include <Arduino.h>
#include <IRremote.h>

// Pin, an den der IR-Sensor angeschlossen ist
const int RECV_PIN = 6;

void setup() {
  Serial.begin(9600);

  // IR-Empfänger starten
  IrReceiver.begin(RECV_PIN, ENABLE_LED_FEEDBACK);
  Serial.println("IR-Empfänger gestartet. Warten auf Signale...");
}

void loop() {
  if (IrReceiver.decode()) {
    // Hex-Code des Signals ausgeben
    Serial.print("Empfangenes Signal: 0x");
    Serial.println(IrReceiver.decodedIRData.command, HEX);

    if (IrReceiver.decodedIRData.command == 0xA2) { // Beispiel-Hex-Code
      Serial.println("Taste POWER erkannt!");
    }

    // IR-Daten verwerfen, um auf neue Signale zu warten
    IrReceiver.resume();
  }
}