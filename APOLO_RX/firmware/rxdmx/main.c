#include "soc-hw.h"
#include "rxdmx.h"


#define DEBUG

int main()
{
	uint32_t dato=0;
	gpio0->dir=0x00;
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
