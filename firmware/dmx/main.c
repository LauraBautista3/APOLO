/**
 * 
 */

#include "soc-hw.h"


char glob[] = "Global";

volatile uint32_t *p;
volatile uint8_t *p2;

extern uint32_t tic_msec;

void inicio()
{
  uart_putstr("SerialToDmx ready ");
  uart_putstr("Syntax:");
  uart_putstr(" 123c : use DMX channel 123");
  uart_putstr(" 45w  : set current channel to value 45");

}
int main()
{
	uint8_t value = 0;
	uint8_t channel;
	uint8_t c;

	inicio();

	for(;;)  
	{
		c = uart_getchar();
		if ((c>='0') && (c<='9')) 
	  		value = 10*value + c - '0';
		else if (c=='c') 
		  	channel = value;
		else if (c=='w') 
		{
		/// ACÁ VA EL ENVIO POR DMX
			 uart_putstr(" OK DATO");
			 uart_putstr(" channel");
			 uart_putchar(channel);
			 uart_putstr("  value");
			 uart_putchar(value);

		}
		value = 0;
	 }
}

