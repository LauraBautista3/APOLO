#include "soc-hw.h"
#include "txdmx.h"

 #define DEBUG 

void main()
{
	#ifdef DEBUG
		uart_putstr("modo debug\n");	
     	#endif
	config_dmx();
//	uint8_t tmp_var=0;
//	uint8_t tmp_num=0;
//	uint8_t channel=0;
//	int w_c=0;


	gpio0->dir = 0xFF;
	gpio0->write = 0xFF;

	tic_init0();

	irq_set_mask(0x02);
	irq_enable();


	for(;;)
	{
/*		//while((tmp_var!='<')&&(tmp_var!='>'))
			tmp_var=uart_getchar();
		if(tmp_var=='<')
		{
			irq_disable();
			#ifdef DEBUG
				uart_putstr("\nok <\n");
		     #endif
	         
			tmp_num=uart_getchar();
			#ifdef DEBUG
//				uart_putstr("\ndebug numero: ");	
				uart_putchar(tmp_num);
	
		     #endif
			tmp_var=uart_getchar();
			#ifdef DEBUG
//				uart_putstr("\ndebug variable ");
				uart_putchar(tmp_var);	
		     #endif
			if (tmp_var == 'c')
			{
			if (tmp_num <= 3)
					channel = tmp_num;				
			}
			else if (tmp_var == 'w') 
			{
				w_c = tmp_num;

	   			if (channel==1) 
					v_ch1 = w_c;
				else if (channel==2) 
					v_ch2 = w_c;
				else if (channel==3) 
					v_ch3 = w_c;

				#ifdef DEBUG
					uart_putstr("\ndebug case\n");
					uart_putchar(v_ch1);
					uart_putchar(v_ch2);
					uart_putchar(v_ch3);	
		     	#endif		
			}
		}
		else
		{
			irq_enable();
			tmp_var=0;
//			#ifdef DEBUG
//				uart_putstr("\nok >\n");
//		     #endif


*/
			dmx_init_send();  //      llamar funcion codificador 	dmx         
			sleept1();
			dmx_channel_send(v_ch1);
			sleept1();
			dmx_channel_send(v_ch2);
			sleept1();
			dmx_channel_send(v_ch3);
			sleept1();

//		} 
	
	}
}

