#ifndef UART_H
#define UART_H

#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>

namespace UART {
  static volatile bool echo = true;
  
  void init(uint16_t ubrr);
  
  void put_char(unsigned char data);
  void put_string(const char* str);
  void printf(const char* format, ...);

  int stream_putchar(char c, FILE* stream);
  int stream_getchar(FILE* stream);

  char get_char();
  void get_line(char* buf, uint8_t n);
};

#endif /* UART_H */

