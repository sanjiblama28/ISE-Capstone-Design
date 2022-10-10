#include <stdio.h>
#include <wiringPi.h>

#define TRIG_PIN				28	
#define ECHO_PIN				29

#define IN1_PIN				1		
#define IN2_PIN				4
#define IN3_PIN				5
#define IN4_PIN				6

#define LEFT_IR_PIN		27     
#define RIGHT_IR_PIN		26  


#define INIT_VALUE  		HIGH, HIGH, HIGH , HIGH, "INIT"
#define GO_VALUE  		    HIGH, LOW,   HIGH , LOW,   "GO"
#define BACK_VALUE  		LOW,   HIGH, LOW ,   HIGH, "BACK"
#define LEFT_VALUE  		LOW,   HIGH, HIGH , LOW,   "LEFT"
#define RIGHT_VALUE  		HIGH, LOW,   LOW ,   HIGH, "RIGHT"
#define STOP_VALUE  		LOW,   LOW,   LOW ,   LOW,   "STOP"


#define LIMIT_DISTANCE  20


void controlMotor(int _IN1, int _IN2, int _IN3, int _IN4, char *msg);
void initSensor();
void controlCar();


int gDetect = 0;   
int gCnt = 10;

int main(void)
{
	if(wiringPiSetup() == -1)    return 0;		
	
    initSensor();													
    
	
	while(gCnt-->0)
	{
		     controlCar();
	}
	
	controlMotor(STOP_VALUE);	
	delay(1000);
	return 0;
}


void initSensor()
{
	pinMode(TRIG_PIN, OUTPUT);
	pinMode(ECHO_PIN, INPUT);
	
	
	pinMode(LEFT_IR_PIN,   INPUT);
	pinMode(RIGHT_IR_PIN, INPUT);


	pinMode(IN1_PIN, OUTPUT);
	pinMode(IN2_PIN, OUTPUT);
	pinMode(IN3_PIN, OUTPUT);
	pinMode(IN4_PIN, OUTPUT);	
	
	controlMotor(INIT_VALUE);
	delay(1000);
	
}


void controlMotor(int _IN1, int _IN2, int _IN3, int _IN4, char *msg)
{
		digitalWrite(IN1_PIN, _IN1);
		digitalWrite(IN2_PIN, _IN2);
		digitalWrite(IN3_PIN, _IN3);
		digitalWrite(IN4_PIN, _IN4);		
	
		printf("Move %s~ \n", msg) ;			
}


int getDistance()
{
	int 		start_time=0, end_time=0;
	float 	distance=0;

    digitalWrite(TRIG_PIN, LOW) ;
    delay(500) ;
    digitalWrite(TRIG_PIN, HIGH) ;
    delayMicroseconds(10) ;
    digitalWrite(TRIG_PIN, LOW) ;
    
    while (digitalRead(ECHO_PIN) == 0) ;
    start_time = micros() ;
    
    while (digitalRead(ECHO_PIN) == 1) ;
    end_time = micros() ;
    
    distance = (end_time - start_time) / 29. / 2. ;
	
	return (int)distance;
}
	

void controlCar()
{
	// gives how near is the obsect from the Robot with the help of ultrasonic sensor
	int dis = getDistance();											
	
	int lValue =  digitalRead(LEFT_IR_PIN);			
	int	rValue = digitalRead(RIGHT_IR_PIN);          
	
    // Distance is first measure and if the distance between Robot and obstacle is less than some distance
	//it tackles the obstacle by moving in opposite direction
	if( dis <= LIMIT_DISTANCE){
		    printf(" detect ~!!! [ %dcm ] ",  dis);
			controlMotor(BACK_VALUE);
	        delay(500);
	        controlMotor(STOP_VALUE);
	        delay(500);
	        
	        if( (lValue == LOW)  && ( rValue == LOW))
	        {
				     printf(" ALL detect => ");
					controlMotor(BACK_VALUE);
					delay(500);
					
	        }else if( lValue == LOW ){
				    printf(" LEFT Detect => ");
				    controlMotor(RIGHT_VALUE);
					delay(500);
		   }else if( rValue == LOW ){
			        printf(" RIGHT Detect => ");
				    controlMotor(LEFT_VALUE);
					delay(500);
		   }else{
				     printf(" 0 Detect => ");
				     controlMotor(LEFT_VALUE);
					delay(500);		   
		   }

	}else{
		   controlMotor(GO_VALUE);	
		   delay(500);
	}		
}
