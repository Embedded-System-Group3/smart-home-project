#include <SoftwareSerial.h>
#include <EEPROM.h>  

// SoftwareSerial pins for communication with Board 4
SoftwareSerial board4Serial(10, 11); // RX, TX

// Variables to store last received values
float lastTemp = -1.0;
float lastHumidity = -1.0;
uint16_t lastLdrValue = -1;

// Thresholds for IRS
const float tempThreshold = 0.5;     // Temperature change threshold (in °C)
const uint16_t ldrThreshold = 10;    // LDR value change threshold (in lux)

// EEPROM memory locations for storing values
const int EEPROM_TEMP_ADDR = 0;        // EEPROM address for temperature
const int EEPROM_HUMIDITY_ADDR = 4;    // EEPROM address for humidity
const int EEPROM_LDR_ADDR = 8;         // EEPROM address for LDR value

void setup() {
  Serial.begin(9600);          // Communication with Board 1
  board4Serial.begin(9600);    // Communication with Board 4
  
  // Step 1: Read the last values from EEPROM
  lastTemp = EEPROM.read(EEPROM_TEMP_ADDR);
  lastHumidity = EEPROM.read(EEPROM_HUMIDITY_ADDR);
  lastLdrValue = EEPROM.read(EEPROM_LDR_ADDR);
}

void loop() {
  // Step 2: Receive data from Board 1
  if (Serial.available()) {
    String data = Serial.readStringUntil('\n'); // Read incoming data

    // Parse temperature, humidity, and LDR value
    int firstComma = data.indexOf(',');
    int secondComma = data.indexOf(',', firstComma + 1);

    float temp = data.substring(0, firstComma).toFloat();
    float humidity = data.substring(firstComma + 1, secondComma).toFloat();
    uint16_t ldrValue = data.substring(secondComma + 1).toInt();

    // Step 3: Apply IRS - Check if new data differs enough from old values
    bool dataChanged = false;

    if (abs(temp - lastTemp) >= tempThreshold || abs(ldrValue - lastLdrValue) >= ldrThreshold) {
      dataChanged = true;
    }

    // If data has changed significantly, process and forward it
    if (dataChanged) {
      // Determine heating and light conditions separately
      String heatingStatus;
      String lightStatus;


      if (temp > 28.0) {
        heatingStatus = "Overheating";  // High temperature 
      } else {
        heatingStatus = "Temperature Normal";
      }

      // Check light intensity conditions
      if (ldrValue < 50) {
        lightStatus = "Dark";  // Low light 
      } else {
        lightStatus = "Bright";
      }

      // Step 4: Send processed data to Board 3
      Serial.println("Heating: " + heatingStatus);       
      Serial.println("Light: " + lightStatus);           

      // Step 5: Forward data to Board 4 for display
      String displayData = "Temp: " + String(temp) + " °C, Humidity: " + String(humidity) + 
                           " %, Light: " + String(ldrValue) + " lux";
      board4Serial.println(displayData);                

      Serial.println("Sent to Board 4: " + displayData);

      // Step 6: Update the last received values and store them in EEPROM
      lastTemp = temp;
      lastHumidity = humidity;
      lastLdrValue = ldrValue;

      // Save to EEPROM
      EEPROM.write(EEPROM_TEMP_ADDR, (int)temp); 
      EEPROM.write(EEPROM_HUMIDITY_ADDR, (int)humidity); 
      EEPROM.write(EEPROM_LDR_ADDR, (int)ldrValue); 
    } else {
      
      Serial.println("No significant change in data.");
    }
  }
}
