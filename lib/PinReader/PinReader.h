/**************************************************************
   PinReader nacita hodnoty PINu,
   pracuje pouze v rezimu pro cteni
 **************************************************************/

 class PinReader {
  public:
    PinReader(const int pinNumber);

    void setCallback(void (*callback)(int oldValue, int newValue));
    void init();
    void monitorChanges();
    const int getPinNumber();
    const int getValue();
  private:
    int   _pinNumber;
    int   _value;
    void  (*_callback)(int oldValue, int newValue);
};
