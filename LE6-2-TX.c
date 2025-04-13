#include <stdio.h>
#include <xc.h>
#include <string.h>

#pragma config FOSC = XT
#pragma config WDTE = OFF
#pragma config PWRTE = ON
#pragma config BOREN = ON
#pragma config LVP = OFF
#pragma config CPD = OFF
#pragma config WRT = OFF
#pragma config CP = OFF

// for keypad
unsigned char keypadData = 0x00;

// to display in virtual monitor
unsigned char resultData = 0x00;

void delay(int time)
{
	int i, j;
	for (i = 0; i < time; i++)
	{
		for (j = 0; j < 100; j++);
	}
}

void send_data(const char *str) {
	while(*str) {                      // While we haven't reached the end of the string (i.e., '\0')
		while (!TRMT);                 // Wait until the USART transmit register is ready
		TXREG = *str++;                // Send the current character and move to the next one
	}
}

void usart_init(void){
	// transmitter config
 	SPBRG = 0x19; // 9.6K baud rate @ FOSC=4MHz, asynchronous high speed
 			      // (see formula in Table 10-1 data sheet)
 	SYNC = 0; // asynchronous mode (TXSTA reg)
 	SPEN = 1; // enable serial port (RCSTA reg)
 	TX9 = 0; // 8-bit transmission (TXSTA reg)
 	BRGH = 1; // asynchronous high-speed (TXSTA reg)
 	TXEN = 1; // transmit enable (TXSTA reg)
}

void main(void)
{
	// keypad config
    TRISB = 0xFF; // input from keypad 
	PORTB = 0x00; // inital 0 to all 8 bits

	// usart config
	usart_init();

 	for(;;) // foreground routine
 	{
		// collect keypad input
		if (RB4 == 1) // Check if keypad is high (pressed)
		{

			keypadData = PORTB & 0x0F; // collect data in PORTD and mask
			delay(50);
		
			switch (keypadData)
			{
				case 0x00: resultData = '1'; break;
				case 0x01: resultData = '2'; break;
				case 0x02: resultData = '3'; break;
				case 0x04: resultData = '4'; break;
				case 0x05: resultData = '5'; break;
				case 0x06: resultData = '6'; break;
				case 0x08: resultData = '7'; break;
				case 0x09: resultData = '8'; break;
				case 0x0A: resultData = '9'; break;
				case 0x0C: resultData = '*'; break;
				case 0x0D: resultData = '0'; break;
				case 0x0E: resultData = '#'; break;
				default: break;
			}

			if (resultData != 0) {
				char message[20];
				sprintf(message, "You pressed %c.\r\n", resultData);
				send_data(message);
			}

			while (RB4 == 1);
		}
 	}
}
