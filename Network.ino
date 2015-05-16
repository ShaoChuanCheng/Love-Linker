#include <IoTkit.h>
#include <Ethernet.h>
#include <aJSON.h>
#include <stdio.h>
#include <string.h>

// The location for remote device state
#define HB_FILE "/home/root/remoteDevHBRec.inf"
#define EMOTION_FILE "/home/root/remoteDevEMORec.inf"

IoTkit iotkit;
char dataBuf[256];

void initializeNetwork() {
    iotkit.begin();
}

void sendDataToRemoate(char* compName, int value) {
  iotkit.send(compName, value);   
}

// Just support heartb1 and emot1 only.
int retriveRemoteData(char* compName) {  
  FILE *pFile;
  int lSize = 0;
  
  if (strcmp(compName, "heartb1") == 0 ) {
    int state = readFile(HB_FILE);
    if (state < 0)
        return state;
    return refineExactValue(dataBuf, lSize);
  }
  else if (strcmp(compName, "emot1") == 0) {
    // file open EMOTON_FILE
    // read contents       
    int state = readFile(EMOTION_FILE);
    if (state < 0)
        return state;    
    return refineExactValue(dataBuf, lSize);
  }
  else 
      return -1;
}


int readFile(char* fileName) {
    FILE *pFile;
    int lSize = 0;
  
  // file open HB_FILE
    pFile = fopen(fileName, "r");
    fseek(pFile, 0 , SEEK_END);
    lSize = ftell(pFile);
    rewind(pFile);
    
    if (lSize <= 0) {
      // empty state
      return -1;
    }
    memset(dataBuf, 0 , 256);    
    fread(dataBuf, 1, lSize, pFile);    
    // read contents... we get last one.
    fclose(pFile);

    return 1;
}


int refineExactValue(char* fullString,int leng ) {
  char* retValue = NULL;
  char* tok = NULL;

  tok = strtok(fullString, ",");
  while (tok != NULL) {
    retValue = tok;
    tok = strtok(NULL, ",");
  }

  if (retValue == NULL)
      return -1;
  return atoi(retValue);
}

