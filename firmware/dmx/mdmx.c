#include "soc-hw.h"
#include "mdmx.h"


void sleept1()
{
	uint32_t tcr;
	timer0->counter1 = 0;
	timer0->tcr1 = TIMER_EN;
	do {
 		tcr = timer0->tcr1;
 	} while ( ! (tcr & TIMER_TRIG) );
}


void set_pin(uint8_t pin_act)
{
     if (pin_act)
		gpio0->write = gpio0->read | DMX_PIN;
	else
		gpio0->write = gpio0->read & (~DMX_PIN);

}
void pin_inv(uint32_t num)
{
	uint32_t i;
	uint32_t pin_act;
	pin_act = (~gpio0->read) & DMX_PIN;
     set_pin(pin_act);
	for(i=0;i<num;i++)
		sleept1();
}



void config_dmx()
{
//configurar pin DMX_PIN como pin de salida 
	gpio0->dir |= DMX_PIN;
    //   gpio0->dir = gpio0->dir  | DMX_PIN;
    // config Use timer 1
	timer0->compare1 = (FCPU/1000000)*(TBIT); // for usecond
	gpio0->write = gpio0->read | DMX_PIN;
 
}

void dmx_init_send()
{
	pin_inv(22);
	pin_inv(2);
	pin_inv(8);
     	pin_inv(2);
 }


void dmx_channel_send(uint8_t value)
{
	uint8_t bit, i;
       pin_inv(1); // bita start
 	//nsleep(4000);
	for(i=0;i<8;i++)
	{
		bit=value & 0x01;
 		set_pin(bit);	
		value=value>>1;
		sleept1();
        }
	gpio0->write = gpio0->read | DMX_PIN;
	sleept1();
	sleept1();
	
	}
