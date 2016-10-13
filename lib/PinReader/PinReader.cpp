/**************************************************************
   PinReader nacita hodnoty PINu,
   pracuje pouze v rezimu pro cteni
 **************************************************************/
#include "Arduino.h"

#include "PinReader.h"

PinReader::PinReader(const int pinNumber) {
  _pinNumber = pinNumber;
  _value = 0;
}

void PinReader::setCallback(void (*callback)(int, int)) {
   _callback = callback;
}

void PinReader::init() {
   pinMode(_pinNumber, INPUT);
}

void PinReader::monitorChanges() {
   int currentValue = digitalRead(_pinNumber);
   if (currentValue != _value) {
      _callback(_value, currentValue);
      _value = currentValue;
   }
}
