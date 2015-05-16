
volatile int rate[10];                    // array to hold last ten IBI values
volatile unsigned long sampleCounter = 0;          // used to determine pulse timing
volatile unsigned long lastBeatTime = 0;           // used to find IBI
volatile int P = 512;                     // used to find peak in pulse wave, seeded
volatile int T = 512;                     // used to find trough in pulse wave, seeded
volatile int thresh = 525;                // used to find instant moment of heart beat, seeded
volatile int amp = 100;                   // used to hold amplitude of pulse waveform, seeded
volatile boolean firstBeat = true;        // used to seed rate array so we startup with reasonable BPM
volatile boolean secondBeat = false;      // used to seed rate array so we startup with reasonable BPM

// Volatile Variables, used in the interrupt service routine!
volatile int BPM;                   // int that holds raw Analog in 0. updated every 2mS
volatile int Signal;                // holds the incoming raw data
volatile int IBI = 600;             // int that holds the time interval between beats! Must be seeded!
volatile boolean Pulse = false;     // "True" when User's live heartbeat is detected. "False" when not a "live beat".
volatile boolean QS = false;        // becomes true when Arduoino finds a beat.
const int DELAY_TIME = 20; //ms
const int BTN_CHECK_TIME = 2000; //ms

const int DARK = 0;
const int GREEN = 1;
const int YELLOW = 2;
const int RED = 3;
typedef enum EMOTION{NOUN,NORMAL, LOWEMO,HIGHEMO};

// Regards Serial OutPut  -- Set This Up to your needs
static boolean serialVisual = true;   // Set to 'false' by Default.  Re-set to 'true' to see Arduino Serial Monitor ASCII Visual Pulse

void setup() {
  Serial.begin(115200);             // we agree to talk fast!
  initializeNetwork();
  setupBtn(BTN_CHECK_TIME / DELAY_TIME);
  setupLED() ;
  setupVibrator();
  startAnalyse();
}


//  Where the Magic Happens
void loop() {
  updateLED();
  updateVibration();
  handleBtnEvent();
  TaskDispatcher();
  serialOutput() ;
  delay(DELAY_TIME);  //  take a break
}

void handleBtnEvent() {
  int btnEvent = BtnEvent();
  switch (btnEvent) {
    case 2:
    setVibration(0, 0, false);
      break;
    case 3:
      //led action
      startPairPAN();
      break;
    case 100:
      //long press
      setVibration(100, 5000, true);
      break;
    default:
      break;
  }

  if (btnEvent != 0) {
    Serial.print("BTN Event: ");
    Serial.println(btnEvent);
  }

}




