#include <ChainableLED.h>
int data [1][300] = {
  {500,910,450,59,167,60,167,60,53,60,168,62,51,62,164,60,54,60,167,62,164,60,54,59,167,60,167,60,53,60,54,59,168,61,166,60,167,60,167,62,165,60,54,60,53,59,53,61,53,60,53,60,53,60,54,59,54,60,166,60,167,60,168,60,167,60,168,60}
};
int mode=0;
ChainableLED leds(7, 8, 1);
void setup(){
  leds.init();
  pinMode(9, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

  Serial.begin(9600);
}

void loop(){
  sendSignal(0);
  delay(3000);
}
void sendSignal(int mode) {
   for(int i=0;i<5;i++){
    digitalWrite(12,HIGH);
    delay(30);
    digitalWrite(12,LOW);
    delay(30);
  }
  int dataSize = sizeof(data[mode]) / sizeof(data[mode][0]);
  for (int cnt = 0; cnt < dataSize; cnt++) {
    unsigned long len = data[mode][cnt]*10;
    unsigned long us = micros();
    do {
      digitalWrite(9, (cnt%2) ? LOW : HIGH);
      delayMicroseconds(8);
      digitalWrite(9, LOW);
      delayMicroseconds(7);
    } while (long(us + len - micros()) > 0);
  }
}
