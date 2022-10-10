#include <stdio.h>
#include <wiringPi.h>

#define LEFT_IR_PIN		27
#define RIGHT_IR_PIN		26


int main(void)
{
	int 	nLValue =0, nRValue=0;
	
	if(wiringPiSetup() == -1)
		 return 0;
	
	pinMode(LEFT_IR_PIN,   INPUT);
	pinMode(RIGHT_IR_PIN, INPUT);

	
	while(1)
	{
			nLValue = digitalRead(LEFT_IR_PIN);
			nRValue = digitalRead(RIGHT_IR_PIN);
			
		    printf( "R = %d, L = %d\n", nRValue,  nLValue);
	        delay(500);	
	}
	
	return 0;
}

	
	
