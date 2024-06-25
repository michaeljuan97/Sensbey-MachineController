#include <ShiftRegister74HC595.h>
#include "MAX31855.h"
#include <SPI.h>

// What works?
// Setting timer bisa. Naik turun bisa.
// Save ke variable timer bisa.

// Running mode masih belum work. Tweek this
// Belum show timer di seven segment

// - Show timer di seven segment. INPROGRESS
// - Masuk ke setup mode. Done.
// - Control timer updown. Done
// - Exit setup. Done.
// - Masuk running mode. HOLD
// - Exit running mode. HOLD.
// - Read temp. DONE>>UNTESTED.

// Pin definitions
const int dataPin = 2;   // DS pin of 74HC595
const int clockPin = 3;  // SHCP pin of 74HC595
const int latchPin = 4;  // STCP pin of 74HC595

const int setButtonPin = 5;   // Set button
const int upButtonPin = 6;    // Up button
const int downButtonPin = 7;  // Down button
const int runButtonPin = 8; // running button

//Temp Sensor
// SPI Bus 1 Init (Max 3 sensor di 1 bus)
int CLK = 18;
int SO = 19;
int CS1 = 5;
MAX31855 temp_sensor1(CS1, SO, CLK);
char temp1[50]

// Create shift register object
ShiftRegister74HC595<3> sr(dataPin, clockPin, latchPin);

// Seven segment display digits
const byte digits[10] = {
  B00111111, // 0
  B00000110, // 1
  B01011011, // 2
  B01001111, // 3
  B01100110, // 4
  B01101101, // 5
  B01111101, // 6
  B00000111, // 7
  B01111111, // 8
  B01101111  // 9
};

int timer = 0;

int currentDisplay[3] = {0, 0, 0}; // Stores current values of the 7-segment displays
int currentSegment = 0;            // Currently selected segment in setting mode
bool settingMode = false;          // Indicates if setting mode is active
bool runningMode = false;          // Indicates if running mode is active
unsigned long lastButtonPressTime = 0;  // Time of the last button press

void setup() {
  temp_sensor1.begin();
  pinMode(setButtonPin, INPUT_PULLUP);
  pinMode(upButtonPin, INPUT_PULLUP);
  pinMode(downButtonPin, INPUT_PULLUP);
  
  Serial.begin(9600);
  displayNumber();
}

void loop() {
  //Temp. UNTESTED!
  long now = millis();
  if (now - lastMsg > 5000) {
    lastMsg = now;
    int status1 = temp_sensor1.read();
    float temperature1 = temp_sensor1.getTemperature();
    Serial.println("Temperature 1 ONLY = ... ");
    Serial.print(temperature1);
  }
  //read set button
  if (digitalRead(setButtonPin) == LOW) {
    delay(50); // Debounce delay
    if (digitalRead(setButtonPin) == LOW && millis() - lastButtonPressTime > 2000) {
      // Serial.print(currentDisplay[0]);
      lastButtonPressTime = millis();
      Serial.print(lastButtonPressTime);
      if (!settingMode) {
        settingMode = true;
        Serial.println("Entered setting mode");
        Serial.print("Now setting segment..");
        Serial.println(currentSegment);
      } else {
        currentSegment++;
                Serial.print("Now setting segment..");
        Serial.println(currentSegment);
        if (currentSegment >= 3) {
          currentSegment = 0; //Reset segment counter
          settingMode = false;
          Serial.print("Exiting setting mode. Current display: ");
          Serial.print(currentDisplay[0]);
          Serial.print(currentDisplay[1]);
          Serial.println(currentDisplay[2]);
          displayNumber();
          // timer = currentDisplay[0]+currentDisplay[1]+currentDisplay[2];
          String timer_str = String(currentDisplay[0]) + String(currentDisplay[1]) + String(currentDisplay[2]);
          timer = timer_str.toInt();
          Serial.print("Timer Counter : ");
          Serial.println(timer);
        }
      }
    }
  } else if (digitalRead(runButtonPin) == LOW) { //read run button
    delay(50); // Debounce delay
    if (digitalRead(runButtonPin) == LOW && millis() - lastButtonPressTime > 2000) {
      if (!runningMode) {
        runningMode = true;
        Serial.println("Entered running mode");
        heating();
      }

    }
  }
  // if(digitalRead(runButtonPin) == HIGH){
  //   if (!runningMode) {
  //       runningMode = true;
  //       Serial.println("Entered running mode");
  //       heating();
  //     }
  // }

  if (settingMode) {
    handleSettingMode();
  } else {
    displayNumber();
  }

}

void handleSettingMode() {
  static bool blinkState = true;
  static unsigned long lastBlinkTime = 0;

  if (millis() - lastBlinkTime > 500) {
    blinkState = !blinkState;
    lastBlinkTime = millis();
  }

  if (blinkState) {
    displaySegment(currentSegment, digits[currentDisplay[currentSegment]]);
  } else {
    displaySegment(currentSegment, 0);
  }

  if (digitalRead(upButtonPin) == LOW) {
    delay(50); // Debounce delay
    if (digitalRead(upButtonPin) == LOW) {
      currentDisplay[currentSegment]++;
      if (currentDisplay[currentSegment] > 9) {
        currentDisplay[currentSegment] = 0;
      }
      displaySegment(currentSegment, digits[currentDisplay[currentSegment]]);
      Serial.println(currentDisplay[currentSegment]);
      delay(200); // Button press delay
    }
  }

  if (digitalRead(downButtonPin) == LOW) {
    delay(50); // Debounce delay
    if (digitalRead(downButtonPin) == LOW) {
      currentDisplay[currentSegment]--;
      if (currentDisplay[currentSegment] < 0) {
        currentDisplay[currentSegment] = 9;
      }
      displaySegment(currentSegment, digits[currentDisplay[currentSegment]]);
      delay(200); // Button press delay
      Serial.println(currentDisplay[currentSegment]);
    }
  }
}

void displayNumber() {
  for (int i = 0; i < 3; i++) {
    displaySegment(i, digits[currentDisplay[i]]);
  }
}

void displaySegment(int segment, byte value) {
  sr.set(segment, value);
}

void heating(){
  //reading temp
  //timer countdown
  if(timer != 0){
  Serial.print("Timer remaining..");
  Serial.println(timer);
  timer--;
  } else{
    runningMode = false;
    Serial.print("Exiting running mode......");
  }
}

  // If max_temp-10% < heater < max_temp+10%
  //heater on

  // If heater reach max_temp+10%, turnof heater

  // If timer = 0
  // heater off
  // !heating
// }