#include "soc-hw.h"
#include "rxdmx.h"


#define DEBUG

int main()
{

	uint32_t dato=0;

//falta la entrada gpio del dmx


	gpio0->dir = 0xFF;
	gpio0->write = 0xFF;

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
