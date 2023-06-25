// CableIDPrinter.h

#ifndef CableIDPrinter_h
#define CableIDPrinter_h

#include "Arduino.h"
#include <InkShieldMega.h>

class CableIDPrinter {
public:
  CableIDPrinter(int pin);
  void printCableIDToInkShield(String cableID);

private:
  void spray_letter(int letter);
  InkShieldA0A3 _inkShield;
};

#endif
