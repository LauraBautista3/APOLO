#include "soc-hw.h"
#include "rxdmx.h"


uint32_t datain;
uint32_t error=0;
uint32_t dato;
uint32_t ch1;
uint32_t ch2;
uint32_t ch3;


void timebreak()
{
	uint32_t tcr;
	timer0->counter1 = 0;
	timer0->compare1 = (FCPU/1000000)*(10);
	timer0->tcr1 = TIMER_EN;
	do {
 		tcr = timer0->tcr1;
 	} while ( ! ((tcr & TIMER_TRIG)) );
//	} while ( ! ((tcr & TIMER_TRIG) | (gpio0->read & 0x01) ) );
	if (!(tcr & TIMER_TRIG))
		error=1;
}

void timeMAB()
{
	uint32_t tcr;
	timer0->counter1 = 0;
	timer0->compare1 = (FCPU/1000000)*(8);
	timer0->tcr1 = TIMER_EN;
	do {
 		tcr = timer0->tcr1;
 	} while ( ! ((tcr & TIMER_TRIG) | !(gpio0->read & 0x01) ) );
		if (!(tcr & TIMER_TRIG))
			error=1;
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

uint8_t leerdatos()
{
	uint8_t valor_bit=0, i;
	valor_bit=gpio0->read & 0x01;
	if (valor_bit)
		error=1;
	else
	{
		valor_bit=0;
		for(i=0;i<8;i++)
		{
			sleep2us();
			sleep2us();
			valor_bit=valor_bit<<1;
			valor_bit=valor_bit + gpio0->read & 0x01;
		}
		
		for(i=0;i<2;i++)
		{
			sleep2us();
			sleep2us();
//			if (!(gpio0->read & 0x01));
//				error=1;
			
		}
	}	

	return valor_bit;
}


void valorchs(){
	uart_putchar(ch1);
	uart_putchar(ch2);
	uart_putchar(ch3);
}


