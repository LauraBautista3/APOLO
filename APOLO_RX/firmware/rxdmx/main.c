#include "soc-hw.h"
#include "rxdmx.h"


#define DEBUG

int main()
{

	uint32_t dato=0;

	gpio0->dir = 0x7F; // 0111 1111 pin 1 para la entrada del dmx 
	gpio0->write = 0x7F; 

	tic_init0();

	irq_set_mask(0x02);
	irq_enable();


	for(;;)
	{
		while (gpio0->read & 0x01);
		timebreak();
		timeMAB();
 		sleep2us();
		dato = leerdatos();
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
}
