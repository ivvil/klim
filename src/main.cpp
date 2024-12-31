#include "uart.hpp"

#define UBRR 103

int main() {
  UART::init(UBRR);

  while (true) {
	UART::puts("Hello, world!\n");
  }
}
