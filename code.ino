//Source 
// http://www.learnerswings.com/2014/04/control-seven-segment-display-using.html
//Pin connected to ST_CP of 74HC595
int latchPin = 12;
//Pin connected to SH_CP of 74HC595
int clockPin = 13;
////Pin connected to DS of 74HC595
int dataPin = 11;

void setup() {
  //set pins to output so you can control the shift register
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop() 
{
    // Decimal 63      Binary output  01111111     Displays 0
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, 63);  
    digitalWrite(latchPin, HIGH);
    delay(1000);

    // Decimal 6      Binary output  00000110     Displays 1
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, 6);  
    digitalWrite(latchPin, HIGH);
    delay(1000);
  
    // Decimal 91      Binary output  01011011     Displays 2
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, 91);  
    digitalWrite(latchPin, HIGH);
    delay(1000);

    // Decimal 79      Binary output  01001111     Displays 3  
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, 79);  
    digitalWrite(latchPin, HIGH);
    delay(1000);
  
    // Decimal 102      Binary output  01101010     Displays 4  
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, 102);  
    digitalWrite(latchPin, HIGH);
    delay(1000);
  
    // Decimal 109      Binary output  01101101     Displays 5  
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, 109);  
    digitalWrite(latchPin, HIGH);
    delay(1000);

    // Decimal  125      Binary output  01111101     Displays 6  
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, 125);  
    digitalWrite(latchPin, HIGH);
    delay(1000);

    // Decimal  7      Binary output  00000111     Displays 7     
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, 7);  
    digitalWrite(latchPin, HIGH);
    delay(1000);
    
    // Decimal 127      Binary  output  01111111     Displays 8    
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, 127);  
    digitalWrite(latchPin, HIGH);
    delay(1000);

    // Decimal 102      Binary output  01101111     Displays 9      
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, 111);  
    digitalWrite(latchPin, HIGH);
    delay(1000);
    
}