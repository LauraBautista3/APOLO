#include "soc-hw.h"

uart_t  *uart0  = (uart_t *)   0x20000000;
timer_t *timer0 = (timer_t *)  0x30000000;
gpio_t  *gpio0  = (gpio_t *)   0x40000000;
spi_t   *spi0   = (spi_t *)    0x50000000;

//isr_ptr_t isr_table[32];

int v_ch1=0;
int v_ch2=125;
int v_ch3=255;
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
	pwm(PIN_R, v_ch1);
	pwm(PIN_G, v_ch2);
	pwm(PIN_B, v_ch3);

	if ( uart0->ucr & UART_DR)
		leer_datos();

	
}


void leer_datos()
{
	uint8_t tmp_var=0;
	uint8_t tmp_num=0;
	uint8_t channel=0;
	int w_c=0;
	

	tmp_var=uart_getchar();
		if(tmp_var=='<')
		{
			irq_disable();	         
			tmp_num=uart_getchar();
			tmp_var=uart_getchar();
			if (tmp_var == 'c')
			{
			if (tmp_num <= 3)
					channel = tmp_num;				
			}
			else if (tmp_var == 'w') 
			{
				w_c = tmp_num;

	   			if (channel==1) 
					v_ch1 = w_c;
				else if (channel==2) 
					v_ch2 = w_c;
				else if (channel==3) 
					v_ch3 = w_c;
			}
		}
		else
		{
		irq_enable();
		}




}

/***************************************************************************
 * TIMER Functions
 */
void msleep(uint32_t msec)
{
	uint32_t tcr;

	timer0->compare0 = (FCPU/1000)*msec;
	timer0->counter0 = 0;
	timer0->tcr0 = TIMER_EN;

	do {
 		tcr = timer0->tcr0;
 	} while ( ! (tcr & TIMER_TRIG) );
}


void usleep(uint32_t usec)
{
	uint32_t tcr;

	timer0->compare0 = (FCPU/1000000)*usec;
	timer0->counter0 = 0;
	timer0->tcr0 = TIMER_EN   ;

	do {
 		tcr = timer0->tcr0;
 	} while ( ! (tcr & TIMER_TRIG) );
}


void nsleep(uint32_t nsec)
{
	uint32_t tcr;

	timer0->compare0 = (FCPU/1000000)*nsec;
	timer0->counter0 = 0;
	timer0->tcr0 = TIMER_EN;

	do {
 		tcr = timer0->tcr0;
 	} while ( ! (tcr & TIMER_TRIG) );
}


//uint32_t tic_msec;

/*void tic_isr()
{
//	tic_msec++;
//	timer0->tcr0     = TIMER_EN | TIMER_AR | TIMER_IRQEN;


	timer0->tcr0     = TIMER_EN | TIMER_AR | TIMER_IRQEN;
	pin_inv(PIN_R);
//	pin_inv(PIN_G);
	if (contador && 1)
    		set_pin(1,PIN_G);
	else 
    		set_pin(0,PIN_G);
	
	contador =contador+1;
     
}
*/

void pwm(uint8_t PINRGB, uint8_t Valor_C)
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

