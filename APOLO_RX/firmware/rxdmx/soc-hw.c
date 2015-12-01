#include "soc-hw.h"

uart_t  *uart0  = (uart_t *)   0x20000000;
timer_t *timer0 = (timer_t *)  0x30000000;
gpio_t  *gpio0  = (gpio_t *)   0x40000000;
spi_t   *spi0   = (spi_t *)    0x50000000;



volatile uint32_t ch1=0;
volatile uint32_t ch2=255;
volatile uint32_t ch3=0;
int contador;


/***************************************************************************
 * IRQ handling
 */

void irq_handler(uint32_t pending)
{
	timer0->tcr0     = TIMER_EN | TIMER_AR | TIMER_IRQEN;
	contador =contador+1;
     if (contador >255)
		contador =0;
	//uart_putchar(contador);


	tic_isr(PIN_R, ch1);
	tic_isr(PIN_G, ch2);
	tic_isr(PIN_B, ch3);
}


/***************************************************************************
 * TIMER Functions
 */
void msleep(uint32_t msec)
{
	uint32_t tcr;

	timer0->compare1 = (FCPU/1000)*msec;
	timer0->counter1 = 0;
	timer0->tcr1 = TIMER_EN;

	do {

		tcr = timer0->tcr1;
 	} while ( ! (tcr & TIMER_TRIG) );
}


void usleep(uint32_t usec)
{
	uint32_t tcr;

	timer0->compare1 = (FCPU/1000000)*usec;
	timer0->counter1 = 0;
	timer0->tcr1 = TIMER_EN   ;

	do {
 		tcr = timer0->tcr1;
 	} while ( ! (tcr & TIMER_TRIG) );
}


void nsleep(uint32_t nsec)
{
	uint32_t tcr;

	timer0->compare1 = (FCPU/1000000)*nsec;
	timer0->counter1 = 0;
	timer0->tcr1 = TIMER_EN;

	do {
 		tcr = timer0->tcr1;
 	} while ( ! (tcr & TIMER_TRIG) );
}


void tic_isr(uint8_t PINRGB, uint8_t Valor_C)
{
	

	if (contador < Valor_C)
    		set_pin(1,PINRGB);
	else 
    		set_pin(0,PINRGB);
	
     
}

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

