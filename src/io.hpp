#ifndef IO_H
#define IO_H

#include "twi.hpp"
#include <stdint.h>

class IO {
  uint8_t addr;
public:
  IO(uint8_t addr): addr(addr) {};
  bool write(uint8_t data);
  uint8_t read();
};

#endif /* IO_H */
