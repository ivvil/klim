#include "uart.hpp"
#include <avr/sleep.h>

#define UBRR 103

int main() {
  UART::init(UBRR);

  UART::puts("Hello, world!\r\n");

  uint8_t bufSize = 20;
  char buf[bufSize];

  UART::getLine(buf, bufSize);

  UART::puts("You entered: ");
  UART::puts(buf);
  UART::puts("\r\n");
}
