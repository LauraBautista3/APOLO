#include "soc-hw.h"
#include "rxdmx.h"

 uint32_t dato;
int error=0;
int ch1;
int ch2;
int ch3;


void timebreak()
{
	uint32_t tcr;
     uint8_t p =gpio0->read & 0x01;
	timer0->counter1 = 0;
	timer0->compare1 = (FCPU/1000000)*(90);
	timer0->tcr1 = TIMER_EN;
	do {
 		tcr = timer0->tcr1;
	} while ( (! (tcr & TIMER_TRIG)) && (!p) );
	timer0->tcr1=0;
	if (!(tcr & TIMER_TRIG))
		error = 1;
	else
		while (!(gpio0->read & 0x01));
}


void timeMAB()
{
	uint32_t tcr;
	timer0->counter1 = 0;
	timer0->compare1 = (FCPU/1000000)*(8);
	timer0->tcr1 = TIMER_EN;
	do {
 		tcr = timer0->tcr1;
 	} while ( ! ((tcr & TIMER_TRIG)) );
	timer0->tcr1=0;
	while ((gpio0->read & 0x01));

}

void sleep2us()
{
	uint32_t tcr;
	timer0->counter1 = 0;
	timer0->compare1 = 273;
//	timer0->compare1 = (FCPU/1000000)*(2);
	timer0->tcr1 = TIMER_EN;
	do {
 		tcr = timer0->tcr1;
 	} while ( ! (tcr & TIMER_TRIG) );
		
}void sleep4us()
{
	uint32_t tcr;
	timer0->counter1 = 0;
	timer0->compare1 = 360;
//	timer0->compare1 = (FCPU/1000000)*(4);
	timer0->tcr1 = TIMER_EN;
	do {
 		tcr = timer0->tcr1;
 	} while ( ! (tcr & TIMER_TRIG) );

}

uint8_t leerdatos()
{
	uint8_t valor_bit=0, i, valor=0;
	valor_bit=gpio0->read & 0x01;
	valor_bit=0;
	for(i=0;i<8;i++)
	{
		sleep4us();
		valor_bit=valor_bit<<1;
		valor_bit=valor_bit + (gpio0->read & 0x01);
	}

	sleep4us();
	return valor_bit;
	
//	for (i=0;i<8;i++)
//	{
//	valor = valor + (valor_bit & 0x01);
//	valor = valor<<1;
//	valor_bit = valor_bit>>1;
//	}
//	sleep4us();
	//return valor;
	
}


void valorchs(){
	uart_putchar(ch1);
	uart_putchar(ch2);
	uart_putchar(ch3);
	uart_putchar(13);
	uart_putchar(10);
}


