#include<xc.h>

#pragma config FOSC = XT
#pragma config WDTE = OFF
#pragma config PWRTE = ON
#pragma config BOREN = ON
#pragma config LVP = OFF
#pragma config CPD = OFF
#pragma config WRT = OFF
#pragma config CP = OFF

void delay(int time)
{
	int i, j;
	for (i = 0; i < time; i++)
	{
		for (j = 0; j < 100; j++);
	}
}

void main(void)
{
	SPBRG = 0x19; // 9.6K baud rate @ FOSC=4MHz, asynchronous high speed
				// (see formula in Table 10-1 data sheet)
	SYNC = 0; // asynchronous mode (TXSTA reg)
	SPEN = 1; // enable serial port (RCSTA reg)
	RX9 = 0; // 8-bit reception (TXSTA reg)
	BRGH = 1; // asynchronous high-speed (TXSTA reg)
	CREN = 1; // enable continuous receive (RCSTA reg)

	TRISB = 0x00; // set all ports in PORTB to output
	PORTB = 0x00; // all LEDs are off

	for(;;) // foreground routine
	{
		while(!RCIF); // wait until receive buffer is full
		PORTB = RCREG; // read the receive register
	}
} 
