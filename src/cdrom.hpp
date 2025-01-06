#ifndef CDROM_H
#define CDROM_H

#include <stdint.h>
#include <avr/io.h>
#include "twi.hpp"

class CDROM {
  const int dataL;
  const int dataH;
  const int regSel;

public:
  CDROM(int dataL, int dataH, int regSel);
  
  void init();
  bool unitReadyP();
  uint8_t senseError();
  bool checkDisk();
  bool readToc();
  bool readSubchannel();
  
  void writeIDE(uint8_t reg, uint8_t value);
  uint8_t readIDE(uint8_t reg);
};

#endif // CDROM_H
