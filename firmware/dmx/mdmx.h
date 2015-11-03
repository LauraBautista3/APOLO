#ifndef _MDMX_H
#define _MDMX_H

#define TBIT 4  // in us
#define DMX_PIN 1 // GPIO PIN 

void config_dmx();

void dmx_init_send();

void dmx_channel_send(uint8_t value);

void config_pt();


#endif // _MDMX
