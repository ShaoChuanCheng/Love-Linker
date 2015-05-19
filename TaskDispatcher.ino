
int recieveEmotion = 0;
int preEmotion = 0;
int str = 0;
int hbFreq = 0;
int preHbFreq = 0;
const int TASK_DELAY = 100; //Update the state after 2 secs
int taskTime=0;

void TaskDispatcher() {
  taskTime++;
  if(taskTime < TASK_DELAY)
          return;
  taskTime =0;
   
  preEmotion = recieveEmotion;
  preHbFreq = hbFreq;
  recieveEmotion = retriveRemoteData("emot1");
  int hb =  retriveRemoteData("heartb1");
  if (hb == -1 || recieveEmotion == -1 ) { //data inavailable
    return;
  } else if (recieveEmotion == NOUN) {
    if (preEmotion != NOUN)
      controlDown();
    return;
  }

  str = hb / 1000;
  hbFreq = hb % 1000;

  if (recieveEmotion != preEmotion)
    setLED(recieveEmotion);
    
  if (hbFreq != preHbFreq) {

    int activeTime = str * 60; //ms
    int inactiveTime = 60000 / hbFreq - (activeTime); //ms
    setBlink(activeTime, inactiveTime , true);
    //control Vibrate
    setVibration(activeTime, inactiveTime, true);
  }
}

void controlDown() {
  setBlink(0, 0, false);
  setLED(DARK);
  setVibration(0, 0, false);
}
