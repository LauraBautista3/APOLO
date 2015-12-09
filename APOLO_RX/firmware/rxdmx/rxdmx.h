#ifndef _MDMX_H
#define _MDMX_H

#define TBIT 4  // in us


void timebreak();

void timeMAB();
void sleep2us();
void sleep4us();
uint8_t leerdatos();

void valorchs();


extern int error;
extern uint32_t dato;
extern int ch1;
extern int ch2;
extern int ch3;
#endif // _MDMX
