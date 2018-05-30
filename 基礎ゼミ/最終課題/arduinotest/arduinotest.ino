#include <ChainableLED.h>
#include <IRremote.h>
//LEDの定義
int ir_out = 9;
int mode_led = 10;
int ir_red = 12;
int sirial_led=13;

//リモコン信号//
int data [2][275] = {
  {1000,200,99,552,97,154,47,153,47,54,48,54,48,54,48,51,50,48,53,54,48,154,46,53,48,54,47,54,48,54,47,48,53,49,53,153,47,53,48,153,47,53,48,53,48,54,48,48,53,48,53,53,48,53,48,54,48,54,48,54,48,54,48,48,53,48,53,54,48,54,48,154,46,54,48,153,47,153,47,48,53,153,47,150,50,48},
  {338,169,42,42,41,42,42,42,42,42,41,43,41,42,41,127,41,43,41,43,41,43,41,42,42,43,41,43,40,43,41,43,41,43,41,42,42,42,41,127,42,42,42,127,42,42,42,42,41,43,40,43,41,43,41,42,42,42,41,43,41,42,42,43,41,127,41,128,40,42,41,43,41,43,41,43,41,43,40,43,41,127,42,42,41,127,41,43,41,43,41,43,41,42,42,42,42,126,42,42,41,44,40,127,41,127,41,43,41,127,41,42,41,42,42,43,40,43,41,43,40,42,42,127,41,128,40,127,41,127,42,127,41,127,42,42,41,42,42,43,41,127,41,42,42,42,41,127,42,127,41,42,41,127,41,127,41,42,42,127,41,42,41,127,41,127,41,44,40,127,41,127,41,42,41,127,42,43,41,42,41,127,41,42,41,127,42,42,41,127,41,44,40,127,41,127,41,127,41,42,42,42,41,42,41,127,42,127,41,42,41,127,41,44,40,43,41,42,42,42,42,42,41,43,41,42,42,42,41,43,41,43,41,42,41,127,41,42,42,42,42,42,42,42,42,41,42,43,41,127,41,42,41,43,41,42,41,43,41,127,41,43,41,127,42,42,41,43,41,42,42,42,42,128,40}
};
////////////////
int mode=0;
float hue = 0.0;
ChainableLED leds(7, 8, 1);
void setup(){
  leds.init();
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  // シリアルポートを9600 bps[ビット/秒]で初期化
  Serial.begin(9600);
}

void loop(){
  if (Serial.available() > 0) {
    String command = Serial.readString();
    if(command=="hello"){
      sendSignal(on_data,dataSize_on);
       leds.setColorHSB(0, 0.5,1, 0.1);
    }
    if(command=="do_t_on_L"){
      sendSignal(on_data,dataSize_on);
    }
    if(command=="do_t_off_L"){
      sendSignal(on_data,dataSize_on);
    }
    if(command=="do_t_on_A"){
      sendSignal(on_data,dataSize_on);
    }
    if(command=="do_rang"){
      sendSignal(on_data,dataSize_on);
    }
  } 
  leds.setColorHSB(0, hue,1, 0.1);
}
void sendSignal(int mode) {
   for(int i=0;i<5;i++){
    digitalWrite(led_out,HIGH);
    delay(30);
    digitalWrite(led_out,LOW);
    delay(30);
  }
  int dataSize = sizeof(data[mode]) / sizeof(data[mode][0]);
  for (int cnt = 0; cnt < dataSize; cnt++) {
    unsigned long len = data[mode][cnt]*10;
    unsigned long us = micros();
    do {
      digitalWrite(LED, (cnt%2) ? LOW : HIGH);
      delayMicroseconds(8);
      digitalWrite(LED, LOW);
      delayMicroseconds(7);
    } while (long(us + len - micros()) > 0);
  }
}


void sendSignal(unsigned int *data, int dataSize) {
  int dataSize = sizeof(data[mode]) / sizeof(data[mode][0]);
  for(int i=0;i<5;i++){
    digitalWrite(led_out,HIGH);
    delay(30);
    digitalWrite(led_out,LOW);
    delay(30);
  }
  for (int cnt = 0; cnt < dataSize; cnt++) {
    unsigned long len = data[mode][cnt]*10;
    unsigned long us = micros();
    do {
      digitalWrite(LED, (cnt%2) ? LOW : HIGH);
      delayMicroseconds(8);
      digitalWrite(LED, LOW);
      delayMicroseconds(7);
    } while (long(us + len - micros()) > 0);
  }
}


void call(){
    
}

