#include "soc-hw.h"
#include "rxdmx.h"

uint32_t datain;
uint32_t error;
uint32_t dato;
uint32_t ch1;
uint32_t ch2;
uint32_t ch3;



//#define DEBUG 

int main()
{
	gpio0->dir=0x00;
	for(;;)
	{
		#ifdef DEBUG
			uart_putstr("modo debug\n");	
	     	#endif
		while (gpio0->read & 0x01);
		#ifdef DEBUG
			uart_putstr("FLAG 1 \n");	
	     	#endif
		timebreak();
		if (!(error))
		{
			while (!(gpio0->read & 0x01));
			#ifdef DEBUG
				uart_putstr("FLAG 2 \n");	
		     	#endif
			timeMAB();
			if (!(error))
			{
				while (gpio0->read & 0x01);
				#ifdef DEBUG
					uart_putstr("FLAG 3 \n");	
			     	#endif

				sleep2us();
				dato = leerdatos();
                        	#ifdef DEBUG
					uart_putchar(dato);	
			     	#endif

 				if (!(error) &&(dato ==0))
				{
					#ifdef DEBUG
						uart_putstr("LEYENDO DATOS  \n");	
				     	#endif

					while (gpio0->read & 0x01);
					sleep2us();
					ch1 = leerdatos();
					while (gpio0->read & 0x01);
					sleep2us();
					ch2 = leerdatos();
					while (gpio0->read & 0x01);
					sleep2us();
					ch3 = leerdatos();
					if (!(error))
					valorchs();
	
				}			    	  
			}
		}
		if ((error))
		{							
		#ifdef DEBUG
			uart_putstr("ERROR \n");	
	     	#endif
		error=0;
		}		
	}

}


