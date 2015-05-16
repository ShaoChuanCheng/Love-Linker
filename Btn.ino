// constants won't change. They're used here to
// set pin numbers:
const int buttonPin = 2;     // the number of the pushbutton pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status
int buttonPreState = 0;
boolean startCount = false;
int clickTimes = 0;
int pressTime = 0;
int count = 0;
int timer = 0;

int checkTime = 0;

void setupBtn(int time) {

  checkTime = time;
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
}

int BtnEvent() {
  int event = 0;
  // read the state of the pushbutton value:
  buttonPreState = buttonState;
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH && buttonPreState == LOW) {
    if (startCount) {
      clickTimes++;
      pressTime = 0;
    }
  } else if (buttonState ==LOW && buttonPreState == HIGH) {
    if (startCount == false) {
      Serial.print("Start");
      startCount = true;
      timer = 0;
      clickTimes = 0;
      pressTime = 0;
    }
  } else if (buttonState == LOW && buttonPreState == LOW && startCount) {
    pressTime++;
    if (pressTime > (checkTime * 2 /3) )
      clickTimes += 100;
  } else {
  }


  if (timer == checkTime) {

    switch (clickTimes) {
      case 0:
        //nothing
        break;
      case 2:
        //digitalWrite(ledPin,HIGH);
        event = 2;
        break;
      case 3:
        //digitalWrite(ledPin,LOW);
        event = 3;
        break;
      default:
        if (clickTimes > 100)
          event = 100; //long press
        break;
    }
    startCount = false;
    timer = 0;
  }

  if (startCount)
    timer++;
  return event;
  //delay(1);
}
