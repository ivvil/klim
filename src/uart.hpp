#ifndef UART_H
#define UART_H

#include <stdint.h>
#include <avr/io.h>

class UART {
public:
  static void init(uint16_t ubrr);
  
  static void putc(unsigned char data);
  static void puts(const char* str);

  static char getc();
  static void getLine(char* buf, uint8_t n);
};

#endif /* UART_H */
