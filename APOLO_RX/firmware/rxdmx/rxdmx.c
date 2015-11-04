#include "soc-hw.h"
#include "rxdmx.h"


volatile uint32_t datain;
volatile uint32_t error=0;
volatile uint32_t dato;



void timebreak()
{
	uint32_t tcr;
	timer0->counter1 = 0;
	timer0->compare1 = (FCPU/1000000)*(85);
	timer0->tcr1 = TIMER_EN;
	do {
 		tcr = timer0->tcr1;
 	} while ( ! ((tcr & TIMER_TRIG)) );
	timer0->tcr1=0;
	while (!(gpio0->read & 0x01));

}

void timeMAB()
{
	uint32_t tcr;
	timer0->counter1 = 0;
	timer0->compare1 = (FCPU/1000000)*(4);
	timer0->tcr1 = TIMER_EN;
	do {
 		tcr = timer0->tcr1;
 	} while ( ! ((tcr & TIMER_TRIG)) );
	timer0->tcr1=0;
//	while ((gpio0->read & 0x01));
// 	} while ( ! ((tcr & TIMER_TRIG) | !(gpio0->read & 0x01) ) );
//		if (!(tcr & TIMER_TRIG))
//			error=1;
}

void sleep2us()
{
	uint32_t tcr;
	timer0->counter1 = 0;
	timer0->compare1 = (FCPU/1000000)*(2);
	timer0->tcr1 = TIMER_EN;
	do {
 		tcr = timer0->tcr1;
 	} while ( ! (tcr & TIMER_TRIG) );
		
}


void sleep3us()
{
	uint32_t tcr;
	timer0->counter1 = 0;
	timer0->compare1 = (FCPU/1000000)*(3);
	timer0->tcr1 = TIMER_EN;
	do {
 		tcr = timer0->tcr1;
 	} while ( ! (tcr & TIMER_TRIG) );

}

uint8_t leerdatos()
{
	uint8_t valor_bit=0, i;
	valor_bit=(gpio0->read & 0x01);
//	if (valor_bit)
//		error=1;
	if (!(valor_bit))
	{
		valor_bit=0;
		for(i=0;i<8;i++)
		{
			sleep2us();
			valor_bit=valor_bit<<1;
			valor_bit=valor_bit + (gpio0->read & 0x01);
		}


	}	

	return valor_bit;
}




