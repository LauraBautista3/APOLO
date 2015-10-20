#include "soc-hw.h"


int main()
{
	uint8_t value;
	uint8_t channel=0;
	uint8_t c=0;
	

//	uart_putstr("               Envio serial para el DMX       \n\n\n");
	
        value=0;
	for(;;)
	{
		//c=uart_getchar();
                //uart_putchar(4);
                c='1';
		if ((c>='0') && (c<='9')) 
		{
			value = (2*value) + c - '0';
			uart_putchar(value);
		//	value =0;
		}

		else if (c=='c')
		{ 
			channel = value;
			value=0;
		}
		else if (c=='w') 
		{
		//        uart_putstr("el canal elegido es: ");
			uart_putchar(channel);
		//	uart_putstr("\n");
		//	uart_putstr("el valor para el canal es: ");
			uart_putchar(value);
	//		uart_putstr("\n");
			value = 0;
		}	
	 }
}
