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
 	TX9 = 0; // 8-bit transmission (TXSTA reg)
 	BRGH = 1; // asynchronous high-speed (TXSTA reg)
 	TXEN = 1; // transmit enable (TXSTA reg)

 	for(;;) // foreground routine
 	{
 		while(!TRMT); // wait until transmit shift register is empty
 		TXREG = 'A'; // write data to be sent to TXREG
		delay(500);
 	}
}
