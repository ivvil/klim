#ifndef UART_H
#define UART_H

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

namespace UART {
  void init(uint16_t ubrr);
  
  void putc(unsigned char data);
  void puts(const char* str);

  char getc();
  void getLine(char* buf, uint8_t n);
};

#endif /* UART_H */

