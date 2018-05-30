#include <ChainableLED.h>
int data [2][200] = {
  {1000,200,99,552,97,154,47,153,47,54,48,54,48,54,48,51,50,48,53,54,48,154,46,53,48,54,47,54,48,54,47,48,53,49,53,153,47,53,48,153,47,53,48,53,48,54,48,48,53,48,53,53,48,53,48,54,48,54,48,54,48,54,48,48,53,48,53,54,48,54,48,154,46,54,48,153,47,153,47,48,53,153,47,150,50,48},
  {1000,329,161,43,37,43,38,43,118,44,38,43,118,43,38,43,38,43,38,43,118,43,118,43,38,43,37,44,37,44,118,43,118,44,38,43,37,44,37,43,37,43,38,43,37,43,38,43,37,43,38,43,37,43,37,44,37,44,37,43,118,43,38,43,38,43,38,43,38,43,38,43,37,43,38,43,118,44,38,43,38,43,38,42,38,43,119,43,38,43,38,43,38,43,38,43,37,44,37,44,118,43,38,43,118,43,118,43,118,44,118,44,118,43,119,43}  
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
  if (Serial.available() > 0) {
    String command = Serial.readString();
    if(command=="do_t_on_L"){
      sendSignal(0);
    }
    if(command=="do_t_off_L"){
      sendSignal(0);
    }
    if(command=="do_t_on_A"){
      sendSignal(1);
    }
    if(command=="do_t_off_A"){
      sendSignal(1);
    }
    if(command=="do_rang"){
      
    }
  } 
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
