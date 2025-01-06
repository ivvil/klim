#ifndef TWI_H
#define TWI_H

#include <avr/io.h>
#include <stdint.h>
#include <util/twi.h>

namespace TWI {
  enum TWIError { ACK, NACK, LOST, ERR, UNKNOWN };

struct DataResponse {
  TWI::TWIError err;
  uint8_t data;
};

TWI::TWIError status_to_TWI_error();

void init(uint32_t twbr);

bool start();

void send_start();
void send_stop();

void send_data(uint8_t data);

TWI::TWIError write(uint8_t addr, uint8_t data);
TWI::DataResponse read(uint8_t addr, bool ack);

}; // namespace TWI

namespace TWI_commands {
  void init(uint32_t twbr);

  void start();
  void stop();

  void write(uint8_t data);
  void read();
}

#endif /* TWI_H */
