int redPin = 11; 
int bluePin = 10; 
int greenPin = 9; 
int redIn = A0; 
int greenIn = A1; 
int blueIn = A2; 
int redVal; 
int greenVal; 
int blueVal;
 
void setup() { 
  pinMode(redIn, INPUT);
  pinMode(greenIn, INPUT);
  pinMode(blueIn, INPUT);
  
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(redPin, OUTPUT);
} 

void loop() { 
  redVal = analogRead(redIn); 
  greenVal = analogRead(greenIn); 
  blueVal = analogRead(blueIn); 

  redVal = map(redVal, 0, 1023, 0, 255); 
  greenVal = map(greenVal, 0, 1023, 0, 255); 
  blueVal = map(blueVal, 0, 1023, 0, 255); 
  
  setColor(redVal, greenVal, blueVal);
}

void setColor(int red, int green, int blue){
  analogWrite(redPin, red); 
  analogWrite(greenPin, green); 
  analogWrite(bluePin, blue); 
}
