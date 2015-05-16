int redPin = 6; 	// R petal on RGB LED module connected to digital pin 11
int greenPin = 9; 	// G petal on RGB LED module connected to digital pin 9
int bluePin = 10; 	// B petal on RGB LED module connected to digital pin 10
boolean isBlink = false;
int blinkUpTime = 0; //ms
int blinkDownTime = 0; //ms
int curColor = 0;
int blinkTimer = 0;
void setupLED()
{
  //  pinMode(ledPin, OUTPUT); 	// sets the ledPin to be an output
  pinMode(redPin, OUTPUT); 	// sets the redPin to be an output
  pinMode(greenPin, OUTPUT); 	// sets the greenPin to be an output
  pinMode(bluePin, OUTPUT); 	// sets the bluePin to be an output

  setLED(DARK);
}

void setBlink(int upTime, int downTime, boolean state) {
  blinkUpTime = upTime ;
  blinkDownTime = downTime ;
  isBlink = state;
}

void updateLED() {
  if (!isBlink)
    return;
  if (blinkTimer >= blinkUpTime + blinkDownTime) {
    blinkTimer = 0;
  } else if (blinkTimer == blinkUpTime) {
    setColor(255, 255, 255);
  }
 
  if (blinkTimer ==0){
    setLED(curColor);
  }
  blinkTimer += DELAY_TIME;

}

void setLED(int color) {
  curColor = color;
  switch (color) {
    case DARK:
      setColor(255, 255, 255);
      break;
    case GREEN:
      setColor(255, 0, 255);
      break;
    case YELLOW:
      setColor(0, 0, 255);
      break;
    case RED:
      setColor(0, 255, 255);
      break;
  }

}

void setColor (unsigned char red, unsigned char green, unsigned char blue)     // the color generating function
{
  analogWrite(redPin, red);
  analogWrite(bluePin, blue);
  analogWrite(greenPin, green);
}
