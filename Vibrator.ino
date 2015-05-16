int MoPin = 7;    // vibrator Grove connected to digital pin 7

int VibrationTime = 0;
int VibrationUpTime = 0;
int VibrationDownTime = 0;
boolean isVibration = false;

void setupVibrator() {
  pinMode( MoPin, OUTPUT );
}

void setVibration(int upTime, int downTime, boolean state) {
  VibrationUpTime = upTime ;
  VibrationDownTime = downTime ;
  isVibration = state;
}

void updateVibration() {
  if (!isVibration) {
    digitalWrite(MoPin, LOW);
    return;
  }
  if (VibrationTime >= VibrationUpTime + VibrationDownTime) {
    VibrationTime = 0;
  } else if (VibrationTime == VibrationUpTime) {
    digitalWrite(MoPin, LOW);
  }

  if (VibrationTime == 0){
    digitalWrite(MoPin, HIGH);
  }
  VibrationTime += DELAY_TIME;

}

