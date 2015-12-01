#include "soc-hw.h"

uart_t  *uart0  = (uart_t *)   0x20000000;
timer_t *timer0 = (timer_t *)  0x30000000;
gpio_t  *gpio0  = (gpio_t *)   0x40000000;
spi_t   *spi0   = (spi_t *)    0x50000000;

int v_ch1=250;
int v_ch2=125;
int v_ch3=40;
int contador;
int status=0;

uint8_t tmp_var=0;
uint8_t tmp_num=0;
uint8_t channel=1;
int w_c=0;

/***************************************************************************
 * IRQ handling
 */

void irq_handler(uint32_t pending)
{

	timer0->tcr0     = TIMER_EN | TIMER_AR | TIMER_IRQEN;
	contador =contador+1;
     if (contador > 255)
		contador =0;
	//uart_putchar(contador);
	if ( uart0->ucr & UART_DR)
	{
         status =1;
	}

	else{

	pwm(PIN_R, v_ch1);
	pwm(PIN_G, v_ch2);
	pwm(PIN_B, v_ch3);

 	}
}


void pwm(uint8_t PINRGB, int Valor_C)
{
	if (contador < Valor_C)
    		set_pin(1,PINRGB);
	else 
    		set_pin(0,PINRGB);     
}


void leer_datos()
{
	tmp_var=uart_getchar();
	if(tmp_var=='<')
		{
			uart_putstr("\nok <\n");
			tmp_num=uart_getchar();
				uart_putchar(tmp_num);
			tmp_var=uart_getchar();
				uart_putchar(tmp_var);
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

				uart_putstr("\n asignacion \n");
				uart_putchar(v_ch1);
				uart_putchar(v_ch2);
				uart_putchar(v_ch3);	
	
			}
		}
	else if (tmp_var=='>')
	{
	status=0;
	}
//	status=0;
}

/***************************************************************************
 * TIMER Functions
 */


void tic_init0()
{
	timer0->compare0 = (FCPU/1000000)*10;
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

