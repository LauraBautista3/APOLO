#include "soc-hw.h"


int main()
{

//	gpio0->read = 0x000000ff;
	
	DMX_protocol();
	for(;;)
	{
		Break();
                nsleep(88000);

		MAB();
                nsleep(8000);

		start_code();
                nsleep(44000);
		
		chanel_1()
		nsleep(44000);
		
		chanel_2()
		nsleep(44000);

		chanel_3()
		nsleep(44000);



//		gpio0->write = 0x11;
/*		uint32_t i=0;
		
	
		for(i=0; i<8; i++) 
		{
			uint32_t out1, out2;
			out1 = 0x01 << i;
			out2 = 0x80 >> i;
			gpio0->write = out1 | out2;

			msleep(100000);
		}*/
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
