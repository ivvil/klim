#include "uart.hpp"

// Got this from http://rjhcoding.com/avrc-uart.php

void UART::init(uint16_t ubrr) {
  // Baud rate setting
  UBRR0L = (uint8_t)(ubrr & 0xFF);
  UBRR0H = (uint8_t)(ubrr >> 8);

  // Enable transmitter and reciver
  UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
}

void UART::putc(unsigned char data) {
  while (!(UCSR0A & (1 << UDRE0)));

  UDR0 = data;
}

void UART::puts(const char* str) {
  while (*str) {
	UART::putc(*str++);
  }
}

char UART::getc() {				// TODO Update this to use interrupts
  while(!(UCSR0A & (1 << RXC0)));

  return UDR0;
}

void UART::getLine(char* buf, uint8_t n) {
  uint8_t bufIdx = 0;
  char c;

  do {
    c = UART::getc();

	buf[bufIdx++] = c;
  } while ((bufIdx < n) && (c != '\r'));

  buf[bufIdx] = 0;				// Null termination
}


