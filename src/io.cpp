#include "io.hpp"

bool IO::write(uint8_t data) {
  if (!TWI::start()) {
    TWI::send_stop();
	return false;
  }

  TWI::write(this->addr, data);
  TWI::send_stop();
  return true;
}

uint8_t IO::read() {
  uint8_t data = 0xff;
  if (!TWI::start()) {
	TWI::send_stop();
	return data;
  }

  TWI::DataResponse response = TWI::read(this->addr, true);

  if (response.err != TWI::ACK) {
    return data;
  }

  return response.data;
}


