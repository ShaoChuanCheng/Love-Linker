void startPairPAN() {
  Serial.print("PAN Event");
  system("./home/root/startNetworkPairing.sh &");
}

void startPairBracelet() {
  system("./home/root/pairBracelet.py &");
}

void waitForPairBracelet() {
  system("./home/root/pairBraceletCli.sh &");
}
