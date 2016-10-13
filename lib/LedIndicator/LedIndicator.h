/**************************************************************
Signalizace blikanim LED;
**************************************************************/

#include <Ticker.h>

#ifndef LED_INDICATOR
#define LED_INDICATOR

class LedIndicator {
public:
   LedIndicator();
   void init(int pin);
   void start(float secs);
   void stop();
private:
   int _pin;
   Ticker _ticker;
   static void tick(int pin);
};

#endif
