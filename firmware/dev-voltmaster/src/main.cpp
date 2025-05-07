#include <stdio.h>
#include <stdlib.h>
#include <cstdio>
#include <cstdlib> 
#include <limits.h>
#include <Arduino.h>
#include <ADS1256.h>
#include <LiquidCrystal_I2C.h> 
#include <RotaryEncoder.h>
#include <OneButton.h>

#define PIN_IN1 12
#define PIN_IN2 13
#define PIN_INPUT 14

LiquidCrystal_I2C lcd(0x27, 20, 4);
RotaryEncoder *encoder = nullptr;
OneButton button(PIN_INPUT, true); 
ADS1256 adc(16, 17, 0, 5, 2.500);  

long rawConversion = 0; //24-bit raw value
float voltageValue = 0; //human-readable floating point value
unsigned long pressStartTime;
int singleEndedChannels[8] = {SING_0, SING_1, SING_2, SING_3, SING_4, SING_5, SING_6, SING_7}; //Array to store the single-ended channels
int differentialChannels[4] = {DIFF_0_1, DIFF_2_3, DIFF_4_5, DIFF_6_7}; //Array to store the differential channels
int inputChannel = 0; //Number used to pick the channel from the above two arrays
char inputMode = ' '; //can be 's' and 'd': single-ended and differential

int pgaValues[7] = {PGA_1, PGA_2, PGA_4, PGA_8, PGA_16, PGA_32, PGA_64}; //Array to store the PGA settings
int pgaSelection = 0; //Number used to pick the PGA value from the above array

float  intercept = 0;
const unsigned long UPDATE_INTERVAL = 1000;  // milliseconds
unsigned long lastUpdate = 0;

float sumSamples = 0.0;
uint16_t sampleCount = 0;

int resilution =8;
 
float max_val =-1e308;     

float attenuation = (231)/10.1;


int drateValues[16] =
{
  DRATE_30000SPS,
  DRATE_15000SPS,
  DRATE_7500SPS,
  DRATE_3750SPS,
  DRATE_2000SPS,
  DRATE_1000SPS,
  DRATE_500SPS,
  DRATE_100SPS,
  DRATE_60SPS,
  DRATE_50SPS,
  DRATE_30SPS,
  DRATE_25SPS,
  DRATE_15SPS,
  DRATE_10SPS,
  DRATE_5SPS,
  DRATE_2SPS
}; //Array to store the sampling rates

int drateSelection = 0; //Number used to pick the sampling rate from the above array

String registers[11] =
{
  "STATUS",
  "MUX",
  "ADCON",
  "DRATE",
  "IO",
  "OFC0",
  "OFC1",
  "OFC2",
  "FSC0",
  "FSC1",
  "FSC2"
};//Array to store the registers

int registerToRead = 0; //Register number to be read
int registerToWrite = 0; //Register number to be written
int registerValueToWrite = 0; //Value to be written in the selected register


IRAM_ATTR void checkPosition()
{
  encoder->tick(); 
}

IRAM_ATTR void checkTicks() { 
  button.tick();  
}
 
void singleClick() {
  Serial.println("singleClick() detected.");
}  


// this function will be called when the button was pressed 2 times in a short timeframe.
void doubleClick() {
  Serial.println("doubleClick() detected."); 
} // doubleClick


// this function will be called when the button was pressed multiple times in a short timeframe.
void multiClick() {
  int n = button.getNumberClicks();
  if (n == 3) {
    Serial.println("tripleClick detected.");
  } else if (n == 4) {
    Serial.println("quadrupleClick detected.");
  } else {
    Serial.print("multiClick(");
    Serial.print(n);
    Serial.println(") detected.");
  }
 
} // multiClick


// this function will be called when the button was held down for 1 second or more.
void pressStart() {
  Serial.println("pressStart()");
  pressStartTime = millis() - 1000; // as set in setPressMs()
} // pressStart()


// this function will be called when the button was released after a long hold.
void pressStop() {
  Serial.print("pressStop(");
  Serial.print(millis() - pressStartTime);
  Serial.println(") detected.");
} // pressStop()

void setup()
{
  Serial.begin(115200); //The value does not matter if you use an MCU with native USB

  while (!Serial)
  {
    ; //Wait until the serial becomes available
  }

  Serial.println("ADS1256 - Custom Library Demo File by Curious Scientist - 2025-03-28");

  adc.InitializeADC(); //See the documentation for every details
  //Setting up CS, RESET, SYNC and SPI
  //Assigning default values to: STATUS, MUX, ADCON, DRATE
  //Performing a SYSCAL

  //Below is a demonstration to change the values through the built-on functions of the library
  //Set a PGA value
  adc.setPGA(PGA_1);  //0b00000000 - DEC: 0
  //--------------------------------------------

  //Set input channels
  adc.setMUX(DIFF_0_1); //0b01100111 - DEC: 103
  //--------------------------------------------

  //Set DRATE
  adc.setDRATE(DRATE_10SPS); //0b00010011 - DEC: 19
  //--------------------------------------------

  adc.setBuffer(1);
  

  //Freeze the display for 3 sec
  delay(3000);
  //------------------------------------------------------
  lcd.init();                    // initialize the lcd   
  lcd.backlight();
  lcd.clear();
  //------------------------------------------------------
  lcd.setCursor(0,1); //Defining positon to write from first row, first column .
  lcd.print("Initiating ..");  
  delay(1000);  
  lcd.clear();

  lcd.setCursor(0,1); //Defining positon to write from first row, first column .
  lcd.print("Testing ..");  
  delay(1000);
  lcd.setCursor(11,1); 
  lcd.print("."); 
  //Read back the above 3 values to check if the writing was succesful
  Serial.print("PGA: ");
  Serial.println(adc.getPGA());
  lcd.setCursor(0,2); 
  lcd.print("PGA: ");
  lcd.print(adc.getPGA());
  delay(100);
  //--
  Serial.print("MUX: ");
  Serial.println(adc.readRegister(MUX_REG));
  
  lcd.setCursor(12,1); 
  lcd.print("."); 
  lcd.setCursor(0,2); 
  lcd.print("MUX: ");
  lcd.print(adc.readRegister(MUX_REG));
  delay(100);
  //--
  Serial.print("DRATE: ");
  Serial.println(adc.readRegister(DRATE_REG));
  lcd.setCursor(13,1); 
  lcd.print("."); 
  lcd.setCursor(0,2); 
  lcd.print("DRATE: ");
  lcd.print(adc.readRegister(DRATE_REG));
  delay(100);   
  double measured[] = { 0.000174382, 0.440400, 0.972722, 1.505981, 2.037400 };
  double expected[] = { 0.000000000, 0.470500, 0.957700, 1.465700, 1.963100 };
  int n = sizeof(measured) / sizeof(measured[0]);

    // accumulate sums for the “through‐origin” fit
    double sum_meas_sq = 0.0, sum_meas_exp = 0.0;
    for (int i = 0; i < n; i++) {
        sum_meas_sq  += measured[i] * measured[i];
        sum_meas_exp += measured[i] * expected[i];
    }

    // optimal single scale factor
      intercept = sum_meas_exp / sum_meas_sq;
    printf("Optimal scale factor k = %.6f\n\n", intercept);
    lcd.setCursor(0,2); 
    lcd.print("Optimal scale : ");
    lcd.print(intercept,6);
    delay(1000); 
    lcd.clear();
    lcd.setCursor(0,2); 
    lcd.print("Self Test Done !");
    delay(5000); 
    encoder = new RotaryEncoder(PIN_IN1, PIN_IN2, RotaryEncoder::LatchMode::TWO03);

    // register interrupt routine
    attachInterrupt(digitalPinToInterrupt(PIN_IN1), checkPosition, CHANGE);
    attachInterrupt(digitalPinToInterrupt(PIN_IN2), checkPosition, CHANGE);

    attachInterrupt(digitalPinToInterrupt(PIN_INPUT), checkTicks, CHANGE);

  // link the xxxclick functions to be called on xxxclick event.
  button.attachClick(singleClick);
  button.attachDoubleClick(doubleClick);
  button.attachMultiClick(multiClick);

  button.setPressMs(1000); // that is the time when LongPressStart is called
  button.attachLongPressStart(pressStart);
  button.attachLongPressStop(pressStop);
  
}

void loop()
{
  float channels[4]; //Buffer that holds 4 conversions (4 differential channels)
  static int pos = 0;

  encoder->tick();
  button.tick() ;// just call tick() to check the state.

  int newPos = encoder->getPosition();
  if (pos != newPos) {
    int direction = (int)(encoder->getDirection());
    Serial.print("pos:");
    Serial.print(newPos);
    Serial.print(" dir:");
    Serial.println(direction);
    pos = newPos;
    resilution += direction; 
    if(resilution <0){
      resilution = 8;
    }else if(resilution >8){
      resilution = 0;
    }
  } // if 
  //float intercept =0.97186; 
          for (int j = 0; j < 4; j++)
          {
            channels[j] = adc.convertToVoltage(adc.cycleDifferential()); //store the converted differential results in the buffer
          }

          //After the 4 conversions are in the buffer, the contents are printed on the serial terminal
          for (int i = 0; i < 1; i++)
          {
           // Serial.print(channels[i], 6);//print the converted differential results from the buffer
            sumSamples +=   channels[i];
            sampleCount++; 
            if (channels[i] > max_val) max_val = channels[i];
           
          }
          unsigned long now = millis();
          if (now - lastUpdate >= UPDATE_INTERVAL) {
            lastUpdate = now;
            Serial.println(sampleCount);
             
         
          lcd.setCursor(0,1);
          lcd.print("Ch 1"); 
          lcd.print(" : ");
          lcd.print( channels[0], 7);
          lcd.print(" Vdc"); 
          lcd.setCursor(0,2);
          lcd.print("Ch 2"); 
          lcd.print(" : ");
          lcd.print(channels[0]*attenuation, resilution);
          lcd.print(" Vdc");
          sumSamples  = 0.0;
          sampleCount = 0;
          max_val =-1e308;    
          }
         // Serial.println();//Printing a linebreak - this will put the next 4 conversions in a new line
        
  
  
}
