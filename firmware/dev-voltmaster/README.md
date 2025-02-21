# INA228 Voltage Monitor with LCD and Buzzer

This project reads bus voltage from an INA228 sensor, applies exponential smoothing and drift compensation, and displays the filtered and drift-corrected values on a 20x4 I2C LCD. A buzzer is triggered when the voltage exceeds a predefined threshold.

## Features

- **Voltage Measurement:** Uses the INA228 sensor.
- **Exponential Smoothing:** Reduces noise in voltage readings.
- **Drift Compensation:** Adjusts for slow baseline changes.
- **Threshold Beep:** Activates a buzzer when voltage exceeds 5.0V.
- **LCD Display:** Shows filtered voltage, drift-compensated voltage, and baseline voltage.

## Hardware Requirements

- **Microcontroller:** ESP32 (or Arduino Uno as an alternative)
- **Sensor:** INA228
- **Shunt Resistor:** 0.002 Ω (for a maximum expected current of 204 A)
- **Display:** 20x4 I2C LCD (Address 0x27)
- **Buzzer:** Connected to pin 15 (ESP32)

## Software Requirements

- [PlatformIO](https://platformio.org/)
- **Arduino Framework**
- Libraries:
  - [robtillaart/INA228](https://github.com/RobTillaart/INA228) (v0.1.5)
  - [marcoschwartz/LiquidCrystal_I2C](https://github.com/marcoschwartz/LiquidCrystal_I2C) (v1.1.4)

## Project Structure

```
.
├── src
│   └── main.cpp         # Main application code.
├── platformio.ini       # PlatformIO project configuration.
└── README.md            # This file.
```

## Code Overview

The main application performs the following:

1. **Initialization:**  
   - Sets up the I2C communication for both the INA228 sensor and the LCD.
   - Initializes the buzzer pin.
   - Performs calibration for the INA228.

2. **Main Loop:**  
   - Reads the bus voltage.
   - Applies exponential smoothing to filter noise.
   - Updates a slow-changing baseline for drift compensation.
   - Computes a drift-corrected voltage value.
   - Activates a buzzer if the voltage exceeds the trigger threshold (5.0V).
   - Displays the filtered, corrected, and baseline voltage on the LCD.
   - Outputs the readings to the Serial Monitor.

## Example Code

Below is the full source code from `src/main.cpp`:

```cpp
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "INA228.h"

#define INA228_ADDRESS  0x40     
#define LCD_ADDRESS     0x27   

// Calibration values
#define SHUNT_R 0.002    // Shunt resistor (Ohms)
#define SHUNT_A 204.0    // Maximum expected current (Amps)

// Error messages
#define INA228_INIT_ERROR "INA228 not found. Check wiring!"
#define CAL_ERROR  "Calibration error!"

// Define the trigger voltage (in volts) for the beep event.
#define TRIGGER_VOLTAGE 5.00000  

// Define the buzzer pin (adjust according to your wiring)
#define BUZZER_PIN 15

// Create a 20x4 LCD object.
LiquidCrystal_I2C lcd(LCD_ADDRESS, 20, 4);

INA228 ina228(INA228_ADDRESS);

// Exponential smoothing for the voltage reading.
const float alpha = 0.1;   
float filteredVoltage = 0.0;
bool firstReading = true;

// Drift compensation variables.
const float gamma = 0.001;  // Small coefficient for slow baseline update.
float baselineVoltage = 0.0;  // Long-term average (baseline).

// Flag to ensure beep only once per threshold crossing.
bool beeped = false;

void setup() {
  Serial.begin(115200);
  delay(1000);   
  Wire.begin();
  
  // Initialize buzzer pin.
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);
  
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Initiating...");

  if (!ina228.begin()) {
    lcd.clear();
    Serial.println(INA228_INIT_ERROR);  
    lcd.print(INA228_INIT_ERROR);
    while (1);
  }

  int calibrationResult = ina228.setMaxCurrentShunt(SHUNT_A, SHUNT_R);
  if (calibrationResult != 0) {
    Serial.println(CAL_ERROR);
    lcd.clear();
    lcd.print(CAL_ERROR);
  }
}

void loop() {
  // Read the bus voltage (in volts) from the INA228.
  float voltage = ina228.getBusVoltage();

  // Exponential smoothing to get a weighted average.
  if (firstReading) {
    filteredVoltage = voltage;
    baselineVoltage = voltage;  // Initialize baseline with first reading.
    firstReading = false;
  } else {
    filteredVoltage = alpha * voltage + (1.0 - alpha) * filteredVoltage;
    // Update baseline slowly to track drift.
    baselineVoltage = gamma * filteredVoltage + (1.0 - gamma) * baselineVoltage;
  }

  // Compute drift-compensated voltage.
  float correctedVoltage = filteredVoltage - baselineVoltage;

  // Format the filtered and corrected voltage values to five decimal places.
  char voltageStr[16];
  char correctedStr[16];
  sprintf(voltageStr, "%.5f V", filteredVoltage);
  sprintf(correctedStr, "%.5f V", correctedVoltage);

  // Check if the filtered voltage meets or exceeds the trigger threshold.
  if (filteredVoltage >= TRIGGER_VOLTAGE) {
    if (!beeped) {
      // Beep once: using tone() for 200 ms at 1000 Hz.
      tone(BUZZER_PIN, 1000, 200);
      beeped = true;
    }
  } else {
    // Reset the flag when voltage drops below the trigger threshold.
    beeped = false;
  }

  // Print the values to the Serial Monitor.
  Serial.print("Filtered: ");
  Serial.print(voltageStr);
  Serial.print("  Drift-Corrected: ");
  Serial.println(correctedStr);

  // Display the values on the LCD.
  lcd.setCursor(0, 0);
  lcd.print("Filt: ");
  lcd.print(voltageStr);

  lcd.setCursor(0, 1);
  lcd.print("Drift: ");
  lcd.print(correctedStr);

  lcd.setCursor(0, 2);
  lcd.print("Base: ");
  lcd.print(baselineVoltage, 5);

  delay(1000);  // Update once every second.
}
```

## PlatformIO Configuration

Below is the `platformio.ini` file configuration supporting both ESP32 and Arduino Uno environments:

```ini
; PlatformIO Project Configuration File

[env:esp32dev]
platform = espressif32
board = esp32dev
framework = arduino
monitor_speed = 115200
monitor_filters = default, log2file
lib_deps =  
  robtillaart/INA228 @ 0.1.5
  marcoschwartz/LiquidCrystal_I2C @ 1.1.4

[env:uno]
platform = atmelavr
framework = arduino
board = uno
```

## Usage

1. **Clone the Repository:**

   ```bash
   git clone https://your-repository-url.git
   cd your-repository-directory
   ```

2. **Open the Project in PlatformIO:**  
   Launch PlatformIO (e.g., through VSCode) and open the cloned project.

3. **Select Your Environment:**  
   - For ESP32, select `[env:esp32dev]`.
   - For Arduino Uno, select `[env:uno]`.

4. **Build and Upload:**  
   Use PlatformIO's build and upload commands to compile the code and flash it to your device.

5. **Monitor the Output:**  
   Open the Serial Monitor (set at 115200 baud) to see the real-time voltage readings.

## License

This project is provided under the [MIT License](LICENSE).

---


