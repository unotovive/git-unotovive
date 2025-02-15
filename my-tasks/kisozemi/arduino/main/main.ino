#include <ChainableLED.h>
const int buttonPin = 3;
int buttonState = 0;
int data [4][300] = {
  //ac on
  {329,160,43,38,43,38,43,119,43,38,43,118,43,37,44,37,43,38,43,118,43,119,43,38,43,37,44,37,44,119,43,119,43,37,43,38,43,38,43,38,43,37,44,37,44,37,43,38,43,38,43,37,44,37,44,37,43,38,43,118,44,37,44,37,44,38,43,38,43,38,43,38,43,37,44,118,43,38,43,37,44,37,44,37,43,118,44,118,43,118,43,118,43,118,44,118,43,119,43,118,43,118,43,38,43,118,43,37,44,37,43,38,43,37,43,118,43,38,43,38,43,37,44,37,44,37,43,119,43,37,44,118,43,38,43,118,44,118,43,118,44,37,44,37,44,118,43,118,44,37,44,37,44,38,43,38,43,37,44,37,44,37,44,118,43,38,43,37,44,37,44,37,44,37,44,37,44,37,44,37,43,37,44,37,44,37,44,37,44,38,43,38,43,37,44,37,44,37,44,37,43,38,43,37,44,37,44,37,44,37,44,37,43,38,43,38,43,37,44,37,44,37,43,38,43,38,43,38,43,37,44,38,43,37,44,37,43,38,43,38,43,37,44,37,44,118,43,38,43,119,43,118,43,38,43,37,44,37,44,118,43,118,44,37,44,37,44,38,43,38,43,37,44,37,44,118,43,118,44,37,44,37,43,38,43,37,44,37,44,37,44},
  //ac off
  {329,161,43,37,43,38,43,118,44,38,43,118,43,38,43,38,43,38,43,118,43,118,43,38,43,37,44,37,44,118,43,118,44,38,43,37,44,37,43,37,43,38,43,37,43,38,43,37,43,38,43,37,43,37,44,37,44,37,43,118,43,38,43,38,43,38,43,38,43,38,43,37,43,38,43,118,44,38,43,38,43,38,42,38,43,119,43,38,43,38,43,38,43,38,43,37,44,37,44,118,43,38,43,118,43,118,43,118,44,118,44,118,43,119,43},
  //light
  {200,99,552,97,154,47,153,47,54,48,54,48,54,48,51,50,48,53,54,48,154,46,53,48,54,47,54,48,54,47,48,53,49,53,153,47,53,48,153,47,53,48,53,48,54,48,48,53,48,53,53,48,53,48,54,48,54,48,54,48,54,48,48,53,48,53,54,48,54,48,154,46,54,48,153,47,153,47,48,53,153,47,150,50,48},

  {909,450,60,167,60,167,60,53,60,168,59,54,60,167,60,53,60,167,60,168,59,53,61,167,60,167,60,54,59,54,59,168,60,167,60,167,60,168,59,168,59,54,59,54,59,53,60,53,60,53,62,51,60,54,60,54,59,168,60,167,60,167,60,168,59,168,60,3742,907,223,60}
};
int BassTab[]={1911,1702,1516,1431,1275,1136,1012};//bass 1~7
boolean rang=false;
ChainableLED leds(7, 8, 1);
void setup(){
  pinMode(buttonPin, INPUT);
  pinMode(3,OUTPUT);
  digitalWrite(3,LOW);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  leds.init();
  leds.setColorRGB(0,100, 255, 50);
  pinMode(9, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(6,OUTPUT);

  Serial.begin(9600);
}

void loop(){
  if(rang){
        buttonState = digitalRead(buttonPin);
        if (buttonState == HIGH) {
          rang=false;
          digitalWrite(6,LOW);
        }
        sound(2);
  }
  if (Serial.available() > 0) {
    String command = Serial.readString();
    if(command=="do_t_L"){
      sendSignal(2);
    }
    if(command=="do_t_on_A"){
      sendSignal(0);
    }
    if(command=="do_t_off_A"){
      sendSignal(1);
    }
    if(command=="do_rang"){
      digitalWrite(6,HIGH);
      rang=true;
    }
    if(command=="cc_N"){
      leds.setColorRGB(0,100, 255, 50);
    }
    if(command=="cc_S"){
      leds.setColorRGB(0,255 , 150, 0);
    }
    if(command=="stop"){
      rang=false;
      digitalWrite(6,LOW);
    }
    if(command=="test"){
      sendSignal(3);
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
void sound(uint8_t note_index)
{
    for(int i=0;i<100;i++)
    {
        digitalWrite(2,HIGH);
        delayMicroseconds(BassTab[note_index]);
        digitalWrite(2,LOW);
        delayMicroseconds(BassTab[note_index]);
    }
}
