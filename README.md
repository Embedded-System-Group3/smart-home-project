#### **Project Overview**  
The **Smart Home Monitoring System** is designed to enhance home automation and safety by monitoring environmental conditions like temperature, humidity, and light intensity. It leverages a modular system of interconnected Arduino boards to collect data, activate actuators like fans and lights, and display real-time data on an LCD screen. This system ensures a comfortable and efficient living environment through intelligent sensing and actuation.

---

### **Table of Contents**
1. [Features](#features)  
2. [System Architecture](#system-architecture)  
3. [Hardware Requirements](#hardware-requirements)  
4. [Software Requirements](#software-requirements)  
5. [How to Set Up](#how-to-set-up)  
6. [How It Works](#how-it-works)  
7. [Code Structure](#code-structure)  


### **Features**
- **Environmental Monitoring**: Tracks temperature, humidity, and light intensity in real-time.  
- **Automatic Actuation**: Activates a cooling fan during overheating and adjusts lighting based on room brightness.  
- **Intelligent Relevance Sampling (IRS)**: Reduces redundant data transmission by filtering insignificant changes.  
- **Real-Time Data Display**: Shows monitored data on an I2C LCD for easy readability.  
- **Data Persistence**: Stores the last known values in EEPROM to retain state after power cycles.  


### **System Architecture**
The system consists of four Arduino boards, each assigned specific roles:
1. **Board 1**: Collects data from the DHT22 (temperature and humidity) and BH1750 (light intensity) sensors.  
2. **Board 2**: Processes data, applies thresholds using IRS, and forwards commands to Boards 3 and 4. this is the master board. 
3. **Board 3**: Controls the cooling fan and lighting based on data received.  
4. **Board 4**: Displays temperature, humidity, and light intensity on an LCD screen.  


### **Hardware Requirements**
- **Sensors**:  
  - DHT22 (Temperature and Humidity Sensor)  
  - BH1750 (Light Intensity Sensor)  
- **Microcontrollers**:  
  - Four Arduino-compatible boards (e.g., Arduino Uno/Nano)  
- **Actuators**:  
  - Cooling fan (controlled by Board 3)  
- **Display**:  
  - 16x2 I2C LCD  
- **Miscellaneous**:  
  - Jumper wires, breadboards, and resistors as required.  


### **Software Requirements**
- Arduino IDE (Version 1.8 or higher)  
- Libraries:  
  - `DHT.h` (For DHT22 sensor)  
  - `Wire.h` (For I2C communication)  
  - `LiquidCrystal_I2C.h` (For LCD display)  
  - `EEPROM.h` (For EEPROM storage)  


### **How to Set Up**
1. **Hardware Setup**:  
   - Connect the DHT22 and BH1750 sensors to **Board 1**.  
   - Wire the cooling fan to **Board 3** using a relay or transistor circuit.  
   - Connect the I2C LCD to **Board 4**.  
   - Use jumper wires for Serial communication between boards.  

2. **Software Upload**:  
   - Upload the respective code to each board using the Arduino IDE:
     - `board1.ino` for Board 1  
     - `board2.ino` for Board 2(Master board)  
     - `board3.ino` for Board 3  
     - `board4.ino` for Board 4  

3. **Power On**:  
   - Power all boards using USB or an external 5V source.  
   - Verify connections for proper communication.  


### **How It Works**
1. **Data Collection**:  
   - Board 1 gathers temperature, humidity, and light intensity data and sends it to Board 2.  

2. **Data Processing**:  
   - Board 2 filters data using IRS and determines if it needs to activate actuators based on predefined thresholds.  

3. **Actuation**:  
   - Board 3 manages the cooling fan for temperature control and light feedback based on brightness levels.  

4. **Data Display**:  
   - Board 4 displays real-time environmental data on the LCD for easy monitoring.  


### **Code Structure**
- **Board 1**: Sensor data collection and transmission.  
- **Board 2**: Threshold-based filtering, decision-making, and forwarding commands to Boards 3 and 4.  
- **Board 3**: Actuator control for temperature and lighting.  
- **Board 4**: Data visualization on an LCD screen.  

