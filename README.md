
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

# 🛠 **BUILD LOG**  

### **Part List**

- [ADS1256  24bit ADC Data acquisition card ](https://www.aliexpress.com/item/1005007924015949.html)
- [ESP 32 WROOM](https://www.aliexpress.com/item/1005005704190069.html?) (i had micro usb one so I got [this also](https://www.aliexpress.com/item/4001084210384.html))
- [OPA2333](https://www.aliexpress.com/item/1005006533819763.html) / [adapter board](https://www.aliexpress.com/item/1005007797484067.html)
- [20x4 LCD](https://www.aliexpress.com/item/1005007132655492.html)
- [10 Digit 16 Segment LCD](https://www.aliexpress.com/item/1005003062619251.html)
- [3*4 keypad](https://www.aliexpress.com/item/4000873237364.html) / may be 4*4 is better with more keys with [I/O For I2C Port Interface](https://www.aliexpress.com/item/32353277284.html?)
- [Rotary Encoder](https://www.aliexpress.com/item/1005005714786511.html)
- [Insulated Safety 4mm Banana Female Jack](https://www.aliexpress.com/item/32979364296.html?) / not the best . need to have better ones
- [8 Channel Solid State Relay Module](https://www.aliexpress.com/item/10000247027760.html) got for auto attenuation accidently bought low ones may be need to fix in software and less safe


-[AC line filter ](https://www.aliexpress.com/item/4001315809458.html) to avoid noice in transformer 
-[Case](https://www.aliexpress.com/item/1005006528488875.html?) [ may be I need 19 2U Rack ](https://www.aliexpress.com/item/1005008870576062.htm)
-[SD card](https://www.aliexpress.com/item/1005005839004388.html) for data logging
-[Logic Level Converter](https://www.aliexpress.com/item/32310628741.html) (for external triggers)


### **Block Diagram**

![block_diagrams](block_diagrams/VoltMaster.jpeg)



## **Update - 1**

Due to unexpected performance issues with the 16-bit High-Resolution ADC powered by the INA228, the project will now utilize the ADS1256 24-bit DAM for analog-to-digital conversion. This change aims to deliver enhanced measurement resolution and reliability. In addition, a new divider network configuration has been implemented using both 1:10 and 1:1 resistor networks, paired with OPA2333 low-noise op-amps for superior signal conditioning. These updates are expected to improve the overall accuracy and stability of the voltmeter measurements.

## **Update - 2**
Basic voltage measurement has been successfully implemented, and a new attenuation front-end has been added.
also divider netwok has been change to 1:22 to have some hedspace for the ADC 2.5v internal ref 
The design has been updated to include two displays: a single-row, 10-digit hexadecimal display for voltage readings, and a 20-digit pixel-based display for menu interactions and mathematical functions.

A new 4x3 keypad and rotary encoder have also been added for improved menu navigation.

## **Update - 3**  OPA2333 Sourcing and Reliability Notes ##

I'm looking to buy the **OPA2333** from a reputable source. The ones I got from **AliExpress** seemed okay at first, but some issues started to appear.

**Three of them failed** shortly after being exposed to signal conditions that were not ideal.

Now I'm considering buying from **Mouser** or **Digi-Key**, although they are more expensive. I'm also looking for cheaper alternatives in the meantime.

I'll keep updating as I test new parts. If the problem persists, we may need to make further improvements to the front-end circuitry to handle these issues more robustly.

Since I have to use the software for gain error compensation, I might also use gain error calculations to correct for op-amp inaccuracies.

---

### ✅ Suggestions & Solutions

#### 1. Component Sourcing
- Stick to authorized distributors like:
  - [Mouser](https://www.mouser.com)
  - [Digi-Key](https://www.digikey.com)
  - [Arrow](https://www.arrow.com)
  - [RS Components](https://www.rs-online.com)
- For budget options, consider:
  - [LCSC](https://www.lcsc.com) (budget-friendly with traceability)

#### 2. Possible Replacements for OPA2333
If you're open to alternatives, consider:
- `TLV2333` — Similar specs with possible differences in noise or offset.
- `MCP6022` — Lower cost, but verify it meets your performance needs.
- `MAX4239` — Precision op-amp with low offset.

#### 3. Front-End Circuit Protection
- Add **input protection diodes**, **resistors**, or **clamping circuits**.
- Consider adding **low-pass filters** to handle noisy or transient signals.

#### 4. Firmware-Based Compensation
- Use **software calibration** to correct gain and offset errors.
- Store calibration constants in **non-volatile memory**.
- Apply corrections at startup for consistency across devices.

---
 

