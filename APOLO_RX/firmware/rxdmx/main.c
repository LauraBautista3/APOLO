#include "soc-hw.h"
#include "rxdmx.h"




//#define DEBUG 

int main()
{

uint32_t ch1;
uint32_t ch2;
uint32_t ch3;

	gpio0->dir=0x00;
	for(;;)
	{
		while (gpio0->read & 0x01);
		timebreak();
		timeMAB();
		if (!(error))
		{
				while (gpio0->read & 0x01);
				sleep2us();
				dato = leerdatos();
 				if (!(error) && (dato ==0))
				{

					while (gpio0->read & 0x01);
					//sleep2us();
					ch1 = leerdatos();
					while (gpio0->read & 0x01);
					sleep2us();
					ch2 = leerdatos();
					while (gpio0->read & 0x01);
					sleep2us();
					ch3 = leerdatos();
					if (!(error))
					{
					uart_putchar(ch1);
					uart_putchar(ch2);
					uart_putchar(ch3);
					}

	
				}			    	  
			}
		error=0;
	}

}

