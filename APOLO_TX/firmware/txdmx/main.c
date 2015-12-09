#include "soc-hw.h"
#include "txdmx.h"


int main()
{
	config_dmx();
	gpio0->dir = 0xFF;
	gpio0->write = 0x0F;

//	tic_init0();

//	irq_set_mask(0x02);
//	irq_enable();

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
			if ( uart0->ucr & UART_DR)
				leer_datos();				
	}
}

