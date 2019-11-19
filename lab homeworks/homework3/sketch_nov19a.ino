// declare all the segments pins
const int pinA = 12;
const int pinB = 8;
const int pinC = 5;
const int pinD = 3;
const int pinE = 2;
const int pinF = 11;
const int pinG = 6;
const int pinDP = 4;
const int pinD1 = 7;
const int pinD2 = 9;
const int pinD3 = 10;
const int pinD4 = 13;

const int segSize = 8;

int currentNumber = 0;

const int noOfDisplays = 4;
const int noOfDigits = 10;

// declare all the joystick pins
const int pinSW = 1; // digital pin connected to switch output
const int pinX = A0; // A0 - analog pin connected to X output
const int pinY = A1; // A1 - analog pin connected to Y output

// dp on or off
int dpState = HIGH;
// states of the button press
int swState = LOW;
int lastSwState = LOW;
int switchValue;
int xValue = 0;
int yValue = 0;

bool joyMoved1 = false;
bool joyMoved2 = false;
int digit = 0;
int minThreshold= 400;
int maxThreshold= 600;

// store the pins in an array for easier access
int segments[segSize] = {
  pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDP
};

byte digitMatrix[noOfDigits][segSize - 1] = {
// a  b  c  d  e  f  g
  {1, 1, 1, 1, 1, 1, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1}, // 2
  {1, 1, 1, 1, 0, 0, 1}, // 3
  {0, 1, 1, 0, 0, 1, 1}, // 4
  {1, 0, 1, 1, 0, 1, 1}, // 5
  {1, 0, 1, 1, 1, 1, 1}, // 6
  {1, 1, 1, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 1, 0, 1, 1}  // 9
};

int digits[noOfDisplays] = {
  pinD1, pinD2, pinD3, pinD4
 };   

void displayNumber(byte digit) {
  for (int i = 0; i < segSize - 1; i++) {
  digitalWrite(segments[i], digitMatrix[digit][i]);
  }
}

// activate the display no. received as param
void showDigit(int num) {
  for (int i = 0; i < noOfDisplays; i++) {
  digitalWrite(digits[i], HIGH);
  }
  digitalWrite(digits[num], LOW);
}

void setup() {
   for (int i = 0; i < segSize - 1; i++)
  {
  pinMode(segments[i], OUTPUT);  
  }
  for (int i = 0; i < noOfDisplays; i++)
  {
  pinMode(digits[i], OUTPUT);  
  }
  Serial.begin(9600);

  displayNumber(digit); // initial value displayed. Choose any value
}

int number = 0;

void move (){
  
  yValue = analogRead(pinY);
 // On Oy axis, if the value is lower than a chosen min threshold, then
 // decrease by 1 the digit value.
  if (yValue < minThreshold && joyMoved2 == false) {
  if (number > 0) {
      number--;
  } else {
      number = 9;
  }
  dpState = !dpState;
  joyMoved2 = true;
  }

 // On Oy axis, if the value is bigger than a chosen max threshold, then
 // increase by 1 the digit value
  if (yValue > maxThreshold && joyMoved2 == false) {
  if (number < 9) {
      number++; 
  } else {
      number = 0;
  }
  
  joyMoved2 = true;
  }

  if (yValue >= minThreshold && yValue <= maxThreshold) {
  joyMoved2 = false;
  }
  displayNumber(number);
  delay(1);
}


void loop() {

  int switchValue = digitalRead(pinSW);
  if(switchValue==LOW) {
    dpState = !dpState;
  }

  if(dpState == HIGH){
    showDigit(digit);
    move();
  }
  else
  {
  xValue = analogRead(pinX);
 // On Ox axis, if the value is lower than a chosen min threshold, then
 // decrease by 1 the digit value.
  if (xValue < minThreshold && joyMoved1 == false) {
  if (digit > 0) {
      digit--;
  } else {
      digit = 3;
  }
  joyMoved1 = true;
  }

 // On Ox axis, if the value is bigger than a chosen max threshold, then
 // increase by 1 the digit value
  if (xValue > maxThreshold && joyMoved1 == false) {
  if (digit < 3) {
      digit++;
  } else {
      digit = 0;
  }
  
  joyMoved1 = true;
  }

  if (xValue >= minThreshold && xValue <= maxThreshold) {
  joyMoved1 = false;  
  showDigit(digit); 
  displayNumber(number);
  }
  delay(1);
 }
}
