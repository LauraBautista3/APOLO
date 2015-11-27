#ifndef _MDMX_H
#define _MDMX_H

#define TBIT 4  // in us
#define DMX_PIN 1 // GPIO PIN 

void sleept1();

void config_dmx();

void pin_inv_old();

void dmx_init_send();

void dmx_channel_send(uint8_t value);


#endif // _MDMX
