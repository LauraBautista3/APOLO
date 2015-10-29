#include "soc-hw.h"
#include "mdmx.h"


int main()
{

	config_dmx();
	uint8_t tmp_var=0;
	uint8_t tmp_num=0;
	uint8_t channel=0;
	uint8_t v_ch1=0;
	uint8_t v_ch2=0;
	uint8_t v_ch3=0;
	uint8_t w_c=0;

	for(;;)
	{
		while(tmp_var!='<')
			tmp_var=uart_getchar();
		tmp_num=uart_getchar();
		tmp_var=uart_getchar();
		if (tmp_var == 'c')
		{	if (tmp_num <= 3)
				channel = tmp_num;				
		}
		else if (tmp_var == 'w') 
		{
			w_c = tmp_num;
	   		switch (channel) 
			{
			case 1:
				v_ch1 = w_c;
				break;
			case 2:
				v_ch2 = w_c;
				break;
			case 3:
				v_ch3 = w_c;
				break;
			default:
				break;
			};		
		dmx_init_send();  //      llamar funcion codificador dmx         
		dmx_channel_send(v_ch1);
		dmx_channel_send(v_ch2);
		dmx_channel_send(v_ch3);
		}
	} 
}

