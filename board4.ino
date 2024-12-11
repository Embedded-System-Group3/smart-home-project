#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

// Define SoftwareSerial pins for communication with Board 3
SoftwareSerial board4Serial(10, 11); // RX, TX

// Initialize the LCD with I2C address 0x27 and dimensions 16x2
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  board4Serial.begin(9600);  // Communication with Board 3
  lcd.init();                // Initialize the LCD
  lcd.backlight();           // Turn on the backlight
  lcd.clear();               // Clear the screen
  lcd.setCursor(0, 0);
  lcd.print("Waiting for data");
}

void loop() {
  // Check if data is available from Board 3
  if (board4Serial.available()) {
    String receivedData = board4Serial.readStringUntil('\n'); // Read incoming data

    // Display received data on the LCD
    lcd.clear();

    if (receivedData.startsWith("Temp:")) {

      int tempStart = receivedData.indexOf(':') + 2;
      int tempEnd = receivedData.indexOf(" °C");
      String tempValue = receivedData.substring(tempStart, tempEnd);

      int humStart = receivedData.indexOf("Humidity:") + 10;
      int humEnd = receivedData.indexOf(" %");
      float humValue = receivedData.substring(humStart, humEnd).toFloat();  // Convert to float for formatting

      int ldrStart = receivedData.indexOf("Light:") + 7;
      String ldrValue = receivedData.substring(ldrStart);

      // Display values on the LCD
      lcd.setCursor(0, 0);
      lcd.print("Temp: ");
      lcd.print(tempValue);
      lcd.print("C");  //Display temperature

      lcd.setCursor(0, 1);
      lcd.print("H: ");
      lcd.print(humValue, 1);  // Display humidity with 1 decimal point

  
      lcd.setCursor(9, 1);  
      lcd.print("L: ");
      lcd.print(ldrValue.substring(0, ldrValue.indexOf(" ")));  //Didplay light intensity
    }
  }
}
