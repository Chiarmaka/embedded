
#include "mbed.h"

//#include "rtos.h"
#include "hts221.h"
#include "LPS25H.h"
#include "time.h"
//#include "stdio.h"

#define BUFFER 32

DigitalOut myled(LED1);
I2C i2c2(I2C_SDA, I2C_SCL);

void Function1();
void Function2();
void Function3();
Thread t1;
Thread t2;
Thread t3;
float data[8][120];
char array[100][120];
//int times[5][120];
int i = 0;
char dates[8] = "";
float tempCelsius = 25.50;
float humi = 55;
char string[30][120];
int humiMax = 100; 
char cmd=NULL;
uint32_t seconds = 0, minutes=0, hours=0, day=0, month=0,year=0; 

char myStr[BUFFER]={0};

LPS25H barometer(i2c2, LPS25H_V_CHIP_ADDR);
//have greetings/instructions
//user has to input date and time - year, month, day, hour/minute/second, use ints
//scanf scans what the user inputs and puts into a variable
//change sample rate, default is 15 seconds, need to change this
//store data in chip on board up to 120 records - circular buffer, FIFO, 

int main()
  {
char test=1;
		int x = 0;
	while (test!=0x13){
				myStr[x]=getchar();
				test=myStr[x];
			x++;
		if (x > 32){
			test = 0x13;
		}
	}
		//gets(myStr,BUFFER);
		scanf("%s",myStr);
		printf("%s\n\r",myStr);
		sleep();
		hts221_init();
		HTS221_Calib();
		
		char hyph = '/';
		char col = ':';
		char str[2];
		
		printf("SOFT253 simple Temperature Humidity and Pressure Sensor Monitor\n\r");
		printf("Using the X-NUCLEO-IKS01A1 shield and MBED Libraries\n\r");
		
		printf("Welcome to our submission for GroupT Soft 253 :)\n\r");
		
		printf("SETDATE: dd/mm/yyyy\n\r");
		
		scanf("%s", dates);	
		
		str[0] = dates[0];
		str[1] = dates[1];
		day = atoi(str);
		
		str[0] = dates[3];
		str[1] = dates[4];
		month = atoi(str);
		
		str[0] = dates[6];
		str[1] = dates[7];
		year = atoi(str);	
	
		
		printf("SETTIME: hh:mm:ss\n\r\n");
		
		scanf("%s", dates);	
		
		str[0] = dates[0];
		str[1] = dates[1];
		hours = atoi(str);
		
		str[0] = dates[3];
		str[1] = dates[4];
		minutes = atoi(str);
		
		str[0] = dates[6];
		str[1] = dates[7];
		seconds = atoi(str);
		
		
		
		t1.start(Function1);
		t2.start(Function2);
		t3.start(Function3);
		
	}
	
	//saving data is priority
	//respond to commands 
	//order date time
	
		void Function1(){
			
			while (true) {		
				Thread::wait(15000);
				if (cmd==NULL){
				HTS221_ReadTempHumi(&tempCelsius, &humi);       			
        barometer.get();        
				
				data[0][i] = tempCelsius;
				data[1][i] = humi;
				data[2][i] = barometer.pressure();
				data[3][i] = seconds;
				data[4][i] = minutes;
				data[5][i] = hours;
				data[6][i] = day;
				data[7][i] = month;
				data[8][i] = year;				
				
				
        Thread::wait(100); // 100 ms
				i++;
				if (i == 120){
					i = 0;
				}
				
			}}
  }


void Function2()
{
	while (true) {
		//Why we had to slow down the thread???
		Thread::wait(2000);				
				seconds++;									
				if(seconds++ >59){
					seconds = seconds - 60;
					minutes++;
					if(minutes >59){
						minutes = minutes -60;
						hours++;
						if(hours >23){
						hours = hours -24;
						day++;
						if(day >28){
							day =day - 28;
						month++;
						if(month > 12){
							year++;
							month = month - 12;
						}
				}
			}
		}
	}	
}
}

void Function3()
{
	while (true) {
		
		Thread::wait(0);
		cmd=getchar();{
			if(cmd=='R'){
			       
				int y = 0;
				int m = 0;
				int d = 0;
				int h = 0;
				int mm = 0;
				int s = 0;
				
				HTS221_ReadTempHumi(&tempCelsius, &humi);       			
        barometer.get();        
				
				data[0][i] = tempCelsius;
				data[1][i] = humi;
				data[2][i] = barometer.pressure();
				data[3][i] = seconds;
				data[4][i] = minutes;
				data[5][i] = hours;
				data[6][i] = day;
				data[7][i] = month;
				data[8][i] = year;				
				
				
				int x = 0;
				for (x = 0; x < i ; x++){
					y = data[8][x];
					m = data[7][x];
					d = data[6][x];
					h = data[5][x];
					mm = data[4][x];
					s = data[3][x];
					 printf("\nTemperature is: %4.2fC. Humidity is: %3.1f%%. Pressure is: %6.1f. Date: %d/%d/%d. Time: %d:%d:%d. Record no: %d\r\n",  data[0][x],  data[1][x], data[2][x], y, m, d, h,  mm, s, x);
				 }			
        				
			}
			else if(cmd=='?'){
				printf("\nSOFT253 simple Temperature Humidity and Pressure Sensor Monitor\n\r");
        printf("Using the X-NUCLEO-IKS01A1 shield and MBED Libraries\n\r");
			}
			cmd= NULL;
  }
}
}
	

void getStr(){
	char test=1;
		int x = 0;
	while (test!=0x13){
				myStr[x]=getchar();
				test=myStr[x];
			x++;
		if (x > 32){
			test = 0x13;
		}
}
	}

