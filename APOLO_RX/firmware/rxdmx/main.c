#include "soc-hw.h"
#include "rxdmx.h"




//#define DEBUG 

int main()
{
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

		error=0;
	}

}


