#define READ_PIN 11
#define LOW_STATE 0
#define HIGH_STATE 1
//https://www.erestage.com/arduino/remo_recv/
void setup(){
  Serial.begin(115200UL);
  pinMode(READ_PIN,INPUT);
  pinMode(10,OUTPUT);
  digitalWrite(10,HIGH);
 
  Serial.println("Ready to receive");
}
 
void waitLow() {
  while (digitalRead(READ_PIN)==LOW) {
    ;
  }
}
 
int waitHigh() {
  unsigned long start = micros();
  while (digitalRead(READ_PIN)==HIGH) {
    if (micros() - start > 5000000) {
      return 1;
    }
  }
  return 0;
}
 
unsigned long now = micros();
unsigned long lastStateChangedMicros = micros();
int state = HIGH_STATE;
 
void loop() {
    if (state == LOW_STATE) {
      waitLow();
    } else {
      int ret = waitHigh();
      if (ret == 1) {
        Serial.print("\n");
        return;
      }
    }
 
    now = micros();
    Serial.print((now - lastStateChangedMicros) / 10, DEC);
    Serial.print(",");
    lastStateChangedMicros = now;
    if (state == HIGH_STATE) {
      state = LOW_STATE;
    } else {
      state = HIGH_STATE;
    }
}
