#include "soc-hw.h"

uart_t  *uart0  = (uart_t *)   0x20000000;
timer_t *timer0 = (timer_t *)  0x30000000;
gpio_t  *gpio0  = (gpio_t *)   0x40000000;
spi_t   *spi0   = (spi_t *)    0x50000000;

uint32_t ch1_=255;
uint32_t ch2_=170;
uint32_t ch3_=0;
int contador;


/***************************************************************************
 * IRQ handling
 */

void irq_handler(uint32_t pending)
{

	timer0->tcr0     = TIMER_EN | TIMER_AR | TIMER_IRQEN;
     
	contador =contador+1;
     if (contador > 255)
		contador =0;
//	uart_putchar(contador);


	pwm(PIN_R, ch1_);
	pwm(PIN_G, ch2_);
	pwm(PIN_B, ch3_);

}


void pwm(uint8_t PINRGB, int Valor_C)
{
	if (contador < Valor_C)
    		set_pin(1,PINRGB);
	else 
    		set_pin(0,PINRGB);     
}



/***************************************************************************
 * TIMER Functions
 */


void tic_init0()
{
	timer0->compare0 = (FCPU/1000000)*5;
	timer0->counter0 = 0;
	timer0->tcr0     = TIMER_EN | TIMER_AR| TIMER_IRQEN;
	contador=0;
}

/**********************************************************
 * GPIO Functions
 */

void set_pin(uint8_t value, uint8_t npin)
{
     if (value)
		gpio0->write = gpio0->read | npin;
	else
		gpio0->write = gpio0->read & (~npin);

}

void set_pinDMX(uint8_t value)
{
     if (value)
		gpio0->write = gpio0->read | 0x01;
	else
		gpio0->write = gpio0->read & 0xFE;

}

void pin_inv(uint8_t npin)
{
	uint32_t val;
	val = (~gpio0->read) & npin;
	set_pin(val,npin);
}



/***************************************************************************
 * UART Functions
 */

char uart_getchar()
{   
	while (! (uart0->ucr & UART_DR)) ;
	return uart0->rxtx;
}

void uart_putchar(char c)
{
	while (uart0->ucr & UART_BUSY) ;
	uart0->rxtx = c;
}

void uart_putstr(char *str)
{
	char *c = str;
	while(*c) {
		uart_putchar(*c);
		c++;
	}
}


