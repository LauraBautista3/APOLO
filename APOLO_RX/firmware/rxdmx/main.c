#include "soc-hw.h"
#include "rxdmx.h"



int main()
{
	uint32_t dato=0;
	gpio0->dir=0xFE;
	gpio0->write=0xFE;

//	tic_init0();

//	irq_set_mask(0x02);
//	irq_enable();

//	for(;;);



	for(;;)
	{
		while (gpio0->read & 0x01);
		timebreak();
		timeMAB();
 		sleep2us();
		dato = leerdatos();
		if (error==0)
		{
			while (gpio0->read & 0x01);
			sleep2us();
			ch1 = leerdatos();
			while (gpio0->read & 0x01);
			sleep2us();
			ch2 = leerdatos();
			while (gpio0->read & 0x01);
			sleep2us();
			ch3 = leerdatos();
			valorchs();
		}
		error=0;
	}

}


