#include "soc-hw.h"
#include "mdmx.h"


int main()
{

	config_dmx();
	for(;;)
	{
		dmx_init_send();      
		dmx_channel_send(0xaa);
		dmx_channel_send(2);
		dmx_channel_send(3);
	} 
}


/*	uint8_t tmp_var=0;
	uint8_t tmp_num=0;
	uint8_t channel=0;
	uint8_t w_c=0;
	
	for(;;)
	{
	while(tmp_var!='<')
		tmp_var=uart_getchar();
	tmp_num=uart_getchar();
	tmp_var=uart_getchar();
	if (tmp_var == 'c')
		channel = tmp_num;
   else if (tmp_var == 'w') 
		w_c = tmp_num;
     else
       uart_putstr("error de comando");

//      llamar funcion codificador dmx     
	uart_putchar(channel);
        uart_putchar(w_c);
 }*/
