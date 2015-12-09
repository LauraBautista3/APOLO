#ifndef _MDMX_H
#define _MDMX_H

#define TBIT 4  // in us


void timebreak();

void timeMAB();
void sleep2us();

uint8_t leerdatos();

void valorchs();


extern volatile uint32_t error;
extern volatile uint32_t dato;
extern  uint32_t ch1;
extern  uint32_t ch2;
extern  uint32_t ch3;
#endif // _MDMX
