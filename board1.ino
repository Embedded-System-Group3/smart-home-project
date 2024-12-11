#include <DHT.h>
#include <Wire.h> 

#define DHTPIN 2       // DHT22 data pin 
#define DHTTYPE DHT22  // DHT 22 (AM2302)
#define LDR_ADDR 0x23  // Default I2C address of the BH1750 sensor

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
  Wire.begin();  // Start I2C communication

  // Initialize the BH1750 sensor
  Wire.beginTransmission(LDR_ADDR);
  Wire.write(0x01);  
  Wire.endTransmission();
  delay(200);  
}

void loop() {
  float temp = dht.readTemperature();
  float humidity = dht.readHumidity();
  
  if (isnan(temp) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Read the LDR sensor value via I2C
  uint16_t ldrValue = readLDR(); 

  // Send temperature, humidity, and LDR value to Board 2
  Serial.print(temp);
  Serial.print(",");
  Serial.print(humidity);
  Serial.print(",");
  Serial.println(ldrValue);  

  delay(2000); 
}

// Function to read LDR sensor (BH1750) value via I2C
uint16_t readLDR() {
  Wire.beginTransmission(LDR_ADDR);  // Start communication with BH1750 sensor
  Wire.write(0x11);  
  Wire.endTransmission();

  Wire.requestFrom(LDR_ADDR, 2);  // Request 2 bytes of data from the BH1750 sensor
  
  if (Wire.available() == 2) {
    uint16_t value = Wire.read() << 8 | Wire.read();  
    return value; 
  } else {
    return 0;  // if no data was read
  }
}
