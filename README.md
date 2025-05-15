
### ⚡ **VoltMaster 228 16/6.5 DVM**  


🔬 **VoltMaster 228 16/6.5 DVM** is a high-precision, **DIY digital voltmeter** inspired by professional-grade **DMMs**. Designed for makers, engineers, and electronics enthusiasts, this project leverages **off-the-shelf sensor modules** like **ADS1256** to provide **24-bit resolution** and up to **6.5-digit precision** for **DC voltage measurements up to 50V**.  

💡 **Key Features:**  
✅ **24-bit High-Resolution ADC** – Powered by **ADS1256** for enhanced accuracy  
✅ **6.5-Digit Display Precision** – Ensures fine voltage readings  
✅ **Auto-Ranging** – Intelligent range selection for optimal accuracy  
✅ **Built-in Voltage Reference** – No external precision resistors required  
✅ **Standalone LCD Display** – Real-time monitoring without a PC  
✅ **Data Logging Support** – Save measurements via **SD card, Serial, or Wi-Fi (ESP32)**  
✅ **Software Calibration & EEPROM Storage** – Fine-tune accuracy and save settings  
✅ **Trigger Mode for Event-Based Measurements** – Capture readings at precise moments  

🔧 **Designed for simplicity but built with precision**, **VoltMaster 228** is the ultimate **DIY alternative** to commercial benchtop **DVMs**—perfect for lab work, testing, and automation.  

📡 **Get started today and build your own professional-grade voltmeter!**  

⚡ **GitHub Link:** _([VoltMaster](https://github.com/lahirunirmalx/VoltMaster))_


# **DIY Digital Voltmeter (DVM) Using Off-the-Shelf Components**  

## **Abstract**  

### **Introduction**  
A **Digital Voltmeter (DVM)** is an essential tool for any electronics hobbyist, engineer, or technician. While professional-grade benchtop DVMs offer superior precision, they are often costly and complex. This project aims to create a **beginner-friendly, easy-to-build Digital Voltmeter** using **off-the-shelf components** that integrate multiple functions into a single module.  

Instead of using separate components for **ADC, voltage reference, and auto-ranging circuits**, we will utilize **integrated solutions like the Adafruit INA228 or INA226 modules**, which include:  
- **A high-resolution (16-bit) ADC**  
- **Built-in precision voltage reference**  
- **Automatic range handling**  

By leveraging these off-the-shelf sensor modules, we can **reduce design complexity, improve accuracy, and make the project more accessible to beginners**.  

---

## **Project Objectives**  
The goal is to create a **cost-effective, beginner-friendly DVM** that offers useful features without requiring extensive calibration or circuit design expertise.  

### **Key Features:**  
1. **Utilizes Ready-to-Use ADC Modules**:  
   - Uses off-the-shelf solutions like **INA228 or INA226**, which provide **16-bit ADC resolution** with a built-in voltage reference.  
   - Eliminates the need for external precision voltage references and complex calibration.  

2. **Auto-Ranging for Versatile Measurements**:  
   - The **INA228 and INA226 handle auto-ranging internally**, simplifying circuit design.  
   - Capable of measuring **voltages from near-zero to 30V** with reasonable accuracy.  

3. **Data Logging & Connectivity**:  
   - Supports **data logging to an SD card** or **transmitting data via USB, UART, or Wi-Fi (ESP32 option)**.  
   - Can interface with computers or cloud services for remote monitoring.  

4. **Calibration & Long-Term Stability**:  
   - The **built-in voltage reference in the INA228/INA226** provides better long-term stability than external resistor networks.  
   - A software-based **user calibration function** can be included to fine-tune accuracy.  

5. **Trigger Function for Precision Measurements**:  
   - Supports external **trigger inputs** to capture voltage readings at specific events.  
   - Useful for capturing **fast-changing signals or voltage changes in circuits**.  

6. **Standalone Operation with LCD Display**:  
   - The system includes an **LCD (16x2, 20x4, or TFT screen)** for standalone use.  
   - Displays real-time voltage readings, unit status, and additional data.  

---

## **Hardware Components**  

### **1. Integrated Voltage & Current Sensor Module**  
- **Adafruit INA228 or INA226**  
  - **16-bit ADC with high precision**  
  - **Built-in voltage reference** for stable measurements  
  - **Auto-ranging capability**  
  - **I2C communication for easy interfacing with Arduino/ESP32**  

### **2. Microcontroller (MCU)**  
- **Arduino (ATmega328P, ATmega2560) or ESP32**  
  - Handles data acquisition, user interface, and logging.  
  - ESP32 allows for **wireless data transmission** (optional).  

### **3. Display Module**  
- **LCD Screen (16x2, 20x4, or TFT Display)**  
  - Displays real-time voltage, range, calibration status, and data logging indicators.  

### **4. Power Supply Module**  
- **5V & 3.3V Regulators (e.g., AMS1117, LM7805)**  
  - Ensures a stable power supply for consistent readings.  

### **5. Data Logging (Optional)**  
- **SD Card Module or Serial Logging to PC**  
  - Stores voltage data for later analysis.  

### **6. Trigger System (Optional)**  
- **External Button or Digital Input**  
  - Captures readings at specific moments for more accurate measurements.  

---

## **Software Implementation**  

### **1. Auto-Ranging Algorithm**  
- **INA228/INA226 handle auto-ranging internally**, reducing the need for complex switching circuits.  
- The microcontroller reads the **current range setting** and adjusts display scaling automatically.  

### **2. Calibration & Accuracy Enhancement**  
- The **built-in voltage reference in INA modules** provides a stable baseline.  
- Users can perform **software-based multi-point calibration** for fine adjustments.  
- Calibration values are stored in **EEPROM or an SD card** for future use.  

### **3. Data Logging**  
- Readings can be stored in:  
  - **SD Card (CSV Format)**  
  - **Sent to a PC via USB/UART**  
  - **Sent wirelessly (ESP32 via MQTT, HTTP, or Bluetooth)**  

### **4. Triggered Measurement Mode**  
- Supports capturing a measurement **on an external trigger event** (e.g., button press or digital signal).  

---

## **Expected Accuracy & Limitations**  
- **Better than DIY resistor-divider ADC designs** due to **integrated voltage reference and 16-bit ADC**.  
- **Not suitable for precision microvolt-level measurements** but **good enough for 30V range with reasonable accuracy**.  
- **Potential noise or drift issues at high frequencies** – primarily designed for **DC voltage measurements**.  

---

## **Summary**  
This project provides an **easy-to-build, beginner-friendly DVM** that takes advantage of modern **off-the-shelf sensor modules like Adafruit INA228/INA226**. By using **integrated ADC, voltage reference, and auto-ranging capabilities**, the design is:  
✅ **Simpler to build** (fewer external components needed)  
✅ **More accurate than basic Arduino ADC circuits**  
✅ **Easier to calibrate and maintain**  

This approach **reduces circuit complexity** while maintaining **good performance for DC voltage measurements up to 30V**. The added features like **data logging, software calibration, and trigger functions** make it a versatile tool for hobbyists and engineers alike.  

By using **widely available sensor modules**, this project ensures **easy replication** and **scalability for future improvements**. Whether used as a simple voltmeter or integrated into larger measurement systems, this DIY DVM provides a **low-cost yet functional alternative to commercial benchtop meters**.

### ⚡ **BUILD LOG**  

# **Part List**

## **Update - 1**

Due to unexpected performance issues with the 16-bit High-Resolution ADC powered by the INA228, the project will now utilize the ADS1256 24-bit DAM for analog-to-digital conversion. This change aims to deliver enhanced measurement resolution and reliability. In addition, a new divider network configuration has been implemented using both 1:10 and 1:1 resistor networks, paired with OPA2333 low-noise op-amps for superior signal conditioning. These updates are expected to improve the overall accuracy and stability of the voltmeter measurements.

## **Update - 2**
Basic voltage measurement has been successfully implemented, and a new attenuation front-end has been added.

The design has been updated to include two displays: a single-row, 10-digit hexadecimal display for voltage readings, and a 20-digit pixel-based display for menu interactions and mathematical functions.

A new 4x3 keypad and rotary encoder have also been added for improved menu navigation.

