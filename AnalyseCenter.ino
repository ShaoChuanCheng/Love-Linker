
#include <TimerOne.h>

float temperature;
int emotion =0;
int hbStr=0;
const int TEMP_MIN = 20; //32;
const int TEMP_MID = 27; //35;
const int TEMP_MAX = 32; //38;

const int AMP_MIN = 0;
const int AMP_MID = 500;
const int AMP_MAX = 1000;

const int BPM_MIN = 200;
const int BPM_MID = 230;
const int BPM_MAX = 250;

int result = 0;

int transf_remote_time_count = 0;
const int REMOTE_TX_PERIOD = 500; //Update the state after 1 secs



//fake data array (levels: 0 , 1 ,2 ,3 )
int fakeStr[5] = {0, 1, 2, 3, 0};
int fakeBPM[5] = {5, 20, 70, 100, 150};


void startAnalyse(){
  Timer1.initialize(2000); //2ms
  Timer1.attachInterrupt( Analyse ); 
}

void Analyse(){
    HeartBeatAlg();
    temperature = measureObjectTemp();
    temperature += 15;
//Temperature
//analyse

// Normal
    if ((temperature >= TEMP_MIN) && (temperature < TEMP_MID) && (BPM >= BPM_MIN) && (BPM < BPM_MID) && (amp >= AMP_MIN) && (amp < AMP_MID))
    {
        emotion = NORMAL;
    }
    else if ((temperature >= TEMP_MIN) && (temperature < TEMP_MID) && (BPM >= BPM_MIN) && (BPM < BPM_MID) && (amp >= AMP_MID) && (amp < AMP_MAX))
    {
        emotion = LOWEMO;
    }
    else if ((temperature >= TEMP_MIN) && (temperature < TEMP_MID) && (BPM >= BPM_MIN) && (BPM < BPM_MID) && (amp >= AMP_MAX))
    {
        emotion = HIGHEMO;
    }
    else
        emotion = NORMAL;


    //send
    transf_remote_time_count++;
    if(transf_remote_time_count < REMOTE_TX_PERIOD)
        return;
    transf_remote_time_count = 0;

    // Strength
    if ((amp >= AMP_MIN) && (amp < AMP_MID)) { 
        hbStr = LEVEL1;
    }
    else if ((amp >= AMP_MID) && (amp < AMP_MAX)) {
        hbStr = LEVEL2;
    }
    else if (amp >= AMP_MAX) {
        hbStr = LEVEL3;
    }
    else {
        hbStr = NOUNLEVEL;
    }

    // For the range of demo
    int calcuBPM = (BPM/3);
    int herb1 = hbStr*1000 + calcuBPM;
    

 
    sendDataToRemoate("heartb1", herb1);
    sendDataToRemoate("emot1", emotion);
}



