/*
 * IRsendDemo.cpp
 *
 *  Demonstrates sending IR codes in standard format with address and command
 *
 * An IR LED must be connected to Arduino PWM pin 3 (IR_SEND_PIN).
 * To receive IR signals in compatible format, you must activate the line #define USE_STANDARD_DECODE in IRremote.h.
 *
 *
 *  Copyright (C) 2020-2021  Armin Joachimsmeyer
 *  armin.joachimsmeyer@gmail.com
 *
 *  This file is part of Arduino-IRremote https://github.com/z3t0/Arduino-IRremote.
 */

#include <IRremote.h>
#if defined(__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__) || defined(__AVR_ATtiny87__) || defined(__AVR_ATtiny167__)
#include "ATtinySerialOut.h"
#endif

IRsend IrSender;

const int pins[] = {2, 4, 5, 7, 9, 11};
int state[] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH};
int count[] = {0, 0, 0, 0, 0, 0};
int len = sizeof(pins) / sizeof(int);

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(pins[0], INPUT_PULLUP );
    pinMode(pins[1], INPUT_PULLUP );
    pinMode(pins[2], INPUT_PULLUP );
    pinMode(pins[3], INPUT_PULLUP );
    pinMode(pins[4], INPUT_PULLUP );
    pinMode(pins[5], INPUT_PULLUP );
    
    Serial.begin(115200);
#if defined(__AVR_ATmega32U4__) || defined(SERIAL_USB) || defined(SERIAL_PORT_USBVIRTUAL)
    delay(2000); // To be able to connect Serial monitor after reset and before first printout
#endif
    // Just to know which program is running on my Arduino
    //Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRREMOTE));
    Serial.print(F("Ready to send IR signals at pin "));
    Serial.println(IR_SEND_PIN);
    Serial.println(F("Send with standard protocol encoders"));
    
}

void toIR(int pin){
  Serial.print("sendIR:");
  Serial.println(pin);
  if(pin == 2){
    // power
    sendIR(2704);// 電源:0xA90:2704
  }else if(pin == 4){
    // pro1
    sendIR(2704);// 電源:0xA90:2704
    delay(100);
    sendIR(1488);// 画面表示:0x5D0:1488
    delay(100);
    sendIR(656);// mute:0x290:656
    delay(100);
    sendIR(1168);// 音量+:0x490:1168
    delay(100);
    sendIR(2704);// 電源:0xA90:2704
  }else if(pin == 5){
    // service
    sendIR(2704);// 電源:0xA90:2704
    delay(100);
    sendIR(1488);// 画面表示:0x5D0:1488
    delay(100);
    sendIR(528);// 5:0x210:528
    delay(100);
    sendIR(1168);// 音量＋:0x490:1168
    delay(100);
    sendIR(2704);// 電源:0xA90:2704
  }else if(pin == 7){
    // pro2
    sendIR(2704);// 電源:0xA90:2704
    delay(100);
    sendIR(1488);// 画面表示:0x5D0:1488
    delay(100);
    sendIR(656);// mute:0x290:656
    delay(100);
    sendIR(3216);// 音量-:0xC90:3216
    delay(100);
    sendIR(2704);// 電源:0xA90:2704
  }else if(pin == 9){
    sendIR(2640);// 入力切替:0xA50:2640
  }else if(pin == 11){
    // pro3
    sendIR(1488);// 画面表示:0x5D0:1488
    delay(100);
    sendIR(656);// mute:0x290:656
    delay(100);
    sendIR(1168);// 音量＋:0x490:1168
    delay(100);
    sendIR(112);// home:0x070:112
  }
}

void sendIR(unsigned long num){
  for (int i = 0; i < 3; i++) {
   IrSender.sendSony(num, 12);
   delay(40);
  }
}

void loop() {
  for (int i=0; i < len; i++){
    if(count[i] > 100){
      if (digitalRead(pins[i]) == HIGH) {
        if(state[i] == LOW){
          toIR(pins[i]);
          state[i] = HIGH;
          count[i] = 0;
        }
      } else {
          state[i] = LOW;
          count[i] = 0;
      }
    }else{
      count[i] ++;
    }
  }
  
  delay(1);
}
