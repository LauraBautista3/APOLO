#include "soc-hw.h"
#include "mdmx.h"

#define DEBUG 

int main()
{
	#ifdef DEBUG
		uart_putstr("modo debug\n");	
     #endif
	config_dmx();
	uint8_t tmp_var=0;
	uint8_t tmp_num=0;
	uint8_t channel=0;
	uint8_t v_ch1=0;
	uint8_t v_ch2=0;
	uint8_t v_ch3=0;
	uint8_t w_c=0;
	
	config_pt();
	
	for(;;)
	{
		while(tmp_var!='<')
			tmp_var=uart_getchar();
		#ifdef DEBUG
			uart_putstr("\nok <\n");
	     #endif	
         
		tmp_num=uart_getchar();
		#ifdef DEBUG
			uart_putstr("\ndebug numero: ");	
			uart_putchar(tmp_num);

	     #endif	
		tmp_var=uart_getchar();
		#ifdef DEBUG
			uart_putstr("\ndebug variable ");
			uart_putchar(tmp_var);	
	     #endif	
		if (tmp_var == 'c')
		{	if (tmp_num <= 3)
				channel = tmp_num;				
		}
		else if (tmp_var == 'w') 
		{
			w_c = tmp_num;
		#ifdef DEBUG
			uart_putstr("\ndebug asignacion\n");
			uart_putchar(w_c);	
	     #endif	

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
		dmx_init_send();  //      llamar funcion codificador dmx         
		dmx_channel_send(v_ch1);
		dmx_channel_send(v_ch2);
		dmx_channel_send(v_ch3);
	} 
}

