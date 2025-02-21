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
