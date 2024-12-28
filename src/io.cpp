#include <avr/io.h>
#include <util/delay.h>
#include "io.hpp"

void sendByte(uint8_t data) {
  for (uint8_t i = 0; i < 8; ++i) {
    if (data & (1 << i)) {
      IDE_DATA_PORT |= (1 << D7_PIN - i); // Set the corresponding bit
    } else {
      IDE_DATA_PORT &= ~(1 << D7_PIN - i); // Clear the corresponding bit
    }
  }
}

uint8_t receiveByte() {
  uint8_t data = 0;
  for (uint8_t i = 0; i < 8; ++i) {
    if (IDE_DATA_PORT & (1 << D7_PIN - i)) {
      data |= (1 << i); // Set the corresponding bit
    }
  }
  return data;
}

void waitReady() {
  while (!(IDE_CTRL_PORT & (1 << RDY_PIN))) {
    _delay_us(1); // Small delay to avoid busy-waiting
  }
}

void sendCommand(uint8_t command) {
  // Select the drive
  IDE_CTRL_PORT &= ~(1 << CS_PIN);

  // Send the command byte
  sendByte(command);

  // Deselect the drive
  IDE_CTRL_PORT |= (1 << CS_PIN);
}
