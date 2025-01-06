#include "uart.hpp"

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 64
#endif /* BUFFER_SIZE */

static volatile char rx_buff[BUFFER_SIZE];
static volatile uint8_t rx_head = 0;
static volatile uint8_t rx_tail = 0;

ISR(USART_RX_vect) {
  uint8_t next_head = (rx_head + 1) % BUFFER_SIZE;
  if (next_head != rx_tail) {
    rx_buff[rx_head] = UDR0; // Store received character
	
	if (UART::echo) {
	  UDR0 = rx_buff[rx_head]; // Loopback
	}
	
    rx_head = next_head;
  }
}

// Got this from http://rjhcoding.com/avrc-uart.php

void UART::init(uint16_t ubrr) {
  // Baud rate setting
  UBRR0L = (uint8_t)(ubrr & 0xFF);
  UBRR0H = (uint8_t)(ubrr >> 8);

  // Enable transmitter and reciver
  UCSR0B |= (1 << RXEN0) | (1 << TXEN0);

  sei();

  UCSR0B |= (1 << RXCIE0);
}

void UART::put_char(unsigned char data) {
  while (!(UCSR0A & (1 << UDRE0)));

  UDR0 = data;
}

void UART::put_string(const char* str) {
  while (*str) {
	UART::put_char(*str++);
  }
}

void UART::printf(const char *format, ...) {
  char buff[128];

  va_list args;

  va_start(args, format);
  vsnprintf(buff, sizeof(buff), format, args);
  va_end(args);

  UART::put_string(buff);
}

char UART::get_char() {
  while (rx_head == rx_tail); // Wait if buffer is empty
  
  if (UCSR0A & ((1 << FE0) | (1 << DOR0) | (1 << UPE0))) {
    // Handle framing error, data overrun, or parity errork
    return '\0'; // Return a null character or handle differently
  }
  
  char c = rx_buff[rx_tail];
  rx_tail = (rx_tail + 1) % BUFFER_SIZE;
  return c;
}

void UART::get_line(char* buf, uint8_t n) {
  uint8_t bufIdx = 0;

  while (bufIdx < n - 1) {
	if (rx_head != rx_tail) {
	  char c = UART::get_char();
	  
	  if (c == '\r') break;

	  buf[bufIdx++] = c;
	}
  }

  buf[bufIdx] = '\0';				// Null termination

  UART::put_string("\r\n");
}

int UART::stream_putchar(char c, FILE *stream) {
  if (c == '\n')
	UART::stream_putchar('r', stream);

  UART::put_char(c);

  return 0;
}

int UART::stream_getchar(FILE *stream) {
  return UART::get_char();
}
