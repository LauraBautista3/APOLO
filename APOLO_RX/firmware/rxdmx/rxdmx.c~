#include "soc-hw.h"
#include "rxdmx.h"


volatile uint32_t error=0;
volatile uint32_t ch1;
volatile uint32_t ch2;
volatile uint32_t ch3;


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
	timer0->compare1 = (FCPU/1000000)*(5);
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
	timer0->compare1 = (FCPU/1000000)*(2);
	timer0->tcr1 = TIMER_EN;
	do {
 		tcr = timer0->tcr1;
 	} while ( ! (tcr & TIMER_TRIG) );
		
}void sleep3us()
{
	uint32_t tcr;
	timer0->counter1 = 0;
//	timer0->compare1 = 270;
	timer0->compare1 = ((FCPU/1000000)*(2))+70 ;
	timer0->tcr1 = TIMER_EN;
	do {
 		tcr = timer0->tcr1;
 	} while ( ! (tcr & TIMER_TRIG) );

}

uint8_t leerdatos()
{
	uint8_t valor_bit=0, i;
	valor_bit=gpio0->read & 0x01;
	valor_bit=0;
	for(i=0;i<8;i++)
	{
		sleep3us();
		valor_bit=valor_bit<<1;
		valor_bit=valor_bit + (gpio0->read & 0x01);
	}
	sleep3us();
	return valor_bit;
}


void valorchs(){
	uart_putchar(ch1);
	uart_putchar(ch2);
	uart_putchar(ch3);
}



void periododmx()
{


}


void pwm(uint8_t canal){
	
	
	
	
	
	
	}
