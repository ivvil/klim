#include "cdrom.hpp"

CDROM::CDROM(int dataL, int dataH, int regSel) : dataL(dataL), dataH(dataH), regSel(regSel) {}

void CDROM::writeIDE(uint8_t reg, uint8_t value) {
  PORTD &= ~(1 << PD2 );
}
