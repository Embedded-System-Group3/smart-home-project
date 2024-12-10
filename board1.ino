#include <DHT.h>
#include <Wire.h>  // Include the Wire library for I2C communication

#define DHTPIN 2       // Pin where the DHT22 data pin is connected
#define DHTTYPE DHT22  // DHT 22 (AM2302)
#define LDR_ADDR 0x23  // Default I2C address of the BH1750 sensor

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
  Wire.begin();  // Start I2C communication

  // Initialize the BH1750 sensor
  Wire.beginTransmission(LDR_ADDR);
  Wire.write(0x01);  // Send the "Power ON" command
  Wire.endTransmission();
  delay(200);  // Wait for the sensor to power on
}

void loop() {
  float temp = dht.readTemperature();
  float humidity = dht.readHumidity();
  
  if (isnan(temp) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Read the LDR sensor value via I2C
  uint16_t ldrValue = readLDR();  // Function to read LDR value

  // Send temperature, humidity, and LDR value to Board 2
  Serial.print(temp);
  Serial.print(",");
  Serial.print(humidity);
  Serial.print(",");
  Serial.println(ldrValue);  // Send LDR value

  delay(2000);  // Wait for 2 seconds before reading again
}

// Function to read LDR sensor (BH1750) value via I2C
uint16_t readLDR() {
  Wire.beginTransmission(LDR_ADDR);  // Start communication with BH1750 sensor
  Wire.write(0x11);  // Send the "Continuous High-Resolution Mode" command to start measurement
  Wire.endTransmission();

  Wire.requestFrom(LDR_ADDR, 2);  // Request 2 bytes of data from the BH1750 sensor
  
  if (Wire.available() == 2) {
    uint16_t value = Wire.read() << 8 | Wire.read();  // Combine two bytes into one 16-bit value
    return value;  // Return the LDR value
  } else {
    return 0;  // Return 0 if no data was read
  }
}
