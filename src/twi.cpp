#include "twi.hpp"

void TWI::init(uint32_t twbr) {
  TWSR = 0x00;
  TWBR = twbr;

  // Enable TWI
  TWCR = (1 << TWEN);
}

void TWI::send_start() {
  TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN); // Send START packet
  while (!(TWCR & _BV(TWINT)))
    ; // Wait for it to be sent
}

bool TWI::start() {
begin:
  TWI::send_start();

  switch (TW_STATUS) {
  case TW_REP_START:
  case TW_START:
    return true;

  case TW_MR_ARB_LOST:
    goto begin;

  default:
    return false;
  }
}

void TWI::send_stop() {
  TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWSTO); // Send STOP packet
}

void TWI::send_data(uint8_t data) {
  TWDR = data;
  TWDR = _BV(TWEN) | _BV(TWINT);

  while (!(TWCR & _BV(TWINT)))
    ;
}

TWI::TWIError
TWI::write(uint8_t addr, uint8_t data) { //  HOLD Need to rethink error handling
  TWI::TWIError response;

  TWI::send_data(addr);

  response = TWI::status_to_TWI_error();

  if (response != TWI::TWIError::ACK) {
    return response;
  }

  TWI::send_data(data);

  return TWI::status_to_TWI_error();
}

TWI::TWIError TWI::status_to_TWI_error() {
  switch (TW_STATUS) {
  case TW_MT_DATA_ACK:
    return TWI::TWIError::ACK;

  case TW_MT_DATA_NACK:
    return TWI::TWIError::NACK;

  case TW_MT_ARB_LOST:
    return TWI::TWIError::LOST;

  default:
    return TWI::TWIError::ERR;
  }
}

TWI::DataResponse TWI::read(uint8_t addr, bool ack) {
  TWI::TWIError response;

  TWI::send_data(addr);

  response = TWI::status_to_TWI_error();

  if (response != TWI::TWIError::ACK) {
	TWI::DataResponse error;

	error.err = response;
	error.data = 0;

    return error;
  }

  uint8_t snd = _BV(TWEN) | _BV(TWINT);

  if (ack) {
    snd |= _BV(TWEA);
  }

  TWCR = snd;

  while (!(TWCR & _BV(TWINT)));

  TWI::DataResponse data;

  data.data = TWDR;
  data.err = status_to_TWI_error();
  
  return data;
}

