#include "io.hpp"
#include "uart.hpp"
#include <avr/sleep.h>

#define UBRR 103

#define F_CPU 16000000UL

#define USART_BAUDRATE 9600 // Desired Baud Rate
#define BAUD_PRESCALER (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

#define SCL_FREQ 100000UL
#define TWCBR ((F_CPU / SCL_FREQ) - 16) / 2

int main() {
  UART::init(BAUD_PRESCALER);

  FILE uart_io;
  fdev_setup_stream(&uart_io, UART::stream_putchar, UART::stream_getchar,
                    _FDEV_SETUP_RW);

  stdout = stdin = &uart_io;

  UART::put_string("Hello, world!\r\n");
  UART::put_string("UART init. Type something!\r\n");

  IO io = IO(0x42);
  bool state = true;

  // char buf[20];

  TWI::init(72);

  while (true) {
    // fgets(buf, sizeof buf - 1, stdin);
    // printf("You typed: %s\n", buf);

    char in = UART::get_char();
    if (in == 't') {
      state = !state;
      io.write(state ? 0xFF : 0x00);
      printf("GPIO Toggled: %s\n", state ? "Encendido" : "Apagado");
    }
  }
}
