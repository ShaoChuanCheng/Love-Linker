
#include <TimerOne.h>
float temprature;
int emotion =0;
int hbStr=0;

void startAnalyse(){
  Timer1.initialize(2000);
  Timer1.attachInterrupt( Analyse ); 
}

void Analyse(){
HeartBeatAlg();
temprature = measureObjectTemp();
//Temperature
//analyse

//send
int herb1=hbStr*1000+BPM;
sendDataToRemoate("heartb1", herb1);
sendDataToRemoate("emot1", emotion) ;
}


