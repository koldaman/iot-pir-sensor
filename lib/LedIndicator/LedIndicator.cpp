/**************************************************************
  Signalizace blikanim LED;
 **************************************************************/
#include "Arduino.h"

#include "LedIndicator.h"
#include <Ticker.h>

LedIndicator::LedIndicator() {
   Ticker _ticker;
}

void LedIndicator::init(int pin) {
   _pin = pin;
  pinMode(_pin, OUTPUT);
}

void LedIndicator::tick(int pin) {
  //toggle state
  int state = digitalRead(pin);
  digitalWrite(pin, !state);
}

void LedIndicator::stop() {
   _ticker.detach();
   digitalWrite(_pin, LOW);
}

void LedIndicator::start(float secs) {
   stop();
   _ticker.attach(secs, &LedIndicator::tick, _pin);
}
