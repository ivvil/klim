#ifndef IO_H
#define IO_H

#include <stdint.h>
#include <avr/io.h>

#define IDE_DATA_PORT PORTB
#define IDE_CTRL_PORT PORTD
#define CS_PIN PD2
#define RDY_PIN PD3
#define DIAG_PIN PD4
#define D0_PIN PB0
#define D1_PIN PB1
#define D2_PIN PB2
#define D3_PIN PB3
#define D4_PIN PB4
#define D5_PIN PB5
#define D6_PIN PB6
#define D7_PIN PB7

void sendByte(uint8_t data);
uint8_t reciveByte();
void waitReady();
void sendCommand(uint8_t command);

#endif /* IO_H */
