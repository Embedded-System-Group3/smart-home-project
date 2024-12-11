#define TEMP_FAN_PIN 9   // Pin for the Temperature Fan (PB1)
#define LIGHT_LED_PIN 8  // Pin for the Light LED (PB0)

void setup() {
  // Set TEMP_FAN_PIN and LIGHT_LED_PIN as outputs using direct register manipulation
  DDRB |= (1 << PB1);  // Set Pin 9 (PB1) as output for fan
  DDRB |= (1 << PB0);  // Set Pin 8 (PB0) as output for light

  Serial.begin(9600);  // Serial communication for receiving from Board 2
}

void loop() {
  if (Serial.available()) {
    String status = Serial.readStringUntil('\n');  // Read incoming status
    status.trim();  // Remove extra spaces/newlines

    // Step 1: Parse and handle temperature status
    if (status.startsWith("Heating: ")) {
      String heatingStatus = status.substring(9);  // Extract heating status

      if (heatingStatus == "Overheating") {
        // Turn on the fan if overheating
        PORTB |= (1 << PB1);  // Turn on TEMP_FAN_PIN (HIGH)
      } else {
        // Turn off the fan if not overheating
        PORTB &= ~(1 << PB1); // Turn off TEMP_FAN_PIN (LOW)
      }
    }

    // Step 2: Parse and handle light status
    if (status.startsWith("Light: ")) {
      String lightStatus = status.substring(7);  // Extract light status

      if (lightStatus == "Dark") {
        // Turn on the Light LED
        PORTB |= (1 << PB0);  // Turn on LIGHT_LED_PIN (HIGH)
      } else if (lightStatus == "Bright") {
        // Turn off the Light LED
        PORTB &= ~(1 << PB0); // Turn off LIGHT_LED_PIN (LOW)
      }
    }
  }
}
