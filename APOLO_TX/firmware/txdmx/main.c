#include "soc-hw.h"
#include "txdmx.h"

//#define DEBUG 

int main()
{
	config_dmx();
	gpio0->dir = 0xFF;
	gpio0->write = 0xFF;

	tic_init0();

	irq_set_mask(0x02);
	irq_enable();

	for(;;)
	{
			dmx_init_send();
			sleept1();
			dmx_channel_send(v_ch1);
			sleept1();
			dmx_channel_send(v_ch2);
			sleept1();
			dmx_channel_send(v_ch3);
			sleept1();
		if (status)	
		{
//			uart_putchar(uart_getchar());
//			v_ch1=v_ch1+10;
//			uart_putchar(v_ch1);
//			status=0;

			leer_datos();
		}			
	}
}

