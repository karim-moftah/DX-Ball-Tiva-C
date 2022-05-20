// Blue Nokia 5110
// ---------------
// Signal        (Nokia 5110) LaunchPad pin
// Reset         (RST, pin 1) connected to PA7
// SSI0Fss       (CE,  pin 2) connected to PA3
// Data/Command  (DC,  pin 3) connected to PA6
// SSI0Tx        (Din, pin 4) connected to PA5
// SSI0Clk       (Clk, pin 5) connected to PA2
// 3.3V          (Vcc, pin 6) power
// back light    (BL,  pin 7) not connected, consists of 4 white LEDs which draw ~80mA total
// Ground        (Gnd, pin 8) ground

#include "tm4c123gh6pm.h"
#include "Nokia5110.h"
#include "TExaS.h"


// *************************** FUNCTIONS DEFINATIONS  ***************************

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void Delay100ms(unsigned long count); // time delay in 0.1 seconds


while(1){
	if(tx >= 0 && ty >= 0 && tx < 21 && ty < (5+level) && foodArr[tx][ty]){
		ballXcord += xval;
		ballYcord += yval;
		if(xval > 0 && yval < 0){// ball is moving up right
			if(foodArr[tx][ty + 1] && foodArr[tx - 1][ty]){ // there is  food down and left of target food
				if(ballXcord>=79){
				yval = -yval;//the ball will move down
				}else{
				xval = -xval;//the ball will move left
				yval = -yval;//the ball will move down
				}
			}else if(foodArr[tx - 1][ty]){// there is food left of target food
				yval = -yval;//the ball will move down right
			}else{//there is no food down or left of target food
				xval = -xval;//the ball will move up left
			}
		}else if(xval < 0 && yval < 0){// ball is moving up left
			if(foodArr[tx + 1][ty] && foodArr[tx][ty + 1]){// there is  food down and right of target food
				if(ballXcord<=0){
				yval = -yval;//the ball will move down
				}else{
				xval = -xval;//the ball will move right
				yval = -yval;//the ball will move down
				}
			}else if(foodArr[tx + 1][ty]){// there is food right of target food
				yval = -yval;//the ball will move down left
			}else{// there is no food down or right of target food
				xval = -xval;//the ball will move up right
			}
		}else if(xval < 0 && yval > 0){//the ball is moving left down
			if(foodArr[tx + 1][ty] && foodArr[tx][ty - 1]){// there is  food above and right of target food
				if(ballXcord<=0){
					yval = -yval;//the ball will move up
				}else{
				xval = -xval;//the ball will move right
				yval = -yval;//the ball will move up
				}}else if(foodArr[tx + 1][ty]){// there is food right of target food
				yval = -yval;//the ball will move up left
			}else{// there is no food above or right of target food
				xval = -xval;//the ball will move down right
			}
		}else{//the ball is moving down right
			if(foodArr[tx - 1][ty] && foodArr[tx][ty - 1]){// there is  food above and left of target food
				if(ballXcord>=79){
				yval = -yval;//the ball will move up
				}else{
				xval = -xval;//the ball will move left
				yval = -yval;//the ball will move up
			}}else if(foodArr[tx - 1][ty]){// there is food left of target food
				yval = -yval;//the ball will move up right
			}else{// there is no food above or left of target food
				xval = -xval;//the ball will move down left
			}
		}
		foodArr[tx][ty] = 0;
		score+=10*level;
		++fe;

		if(fe==63+(21*level)){	
			Nokia5110_Clear();
			Nokia5110_SetCursor(1, 1);
			Nokia5110_OutString("YOU HAVE");
			Nokia5110_SetCursor(1, 2);
			Nokia5110_OutString("PASSED level");
			Nokia5110_SetCursor(1, 3);
			Nokia5110_OutUDec(level);
			Nokia5110_SetCursor(1, 4);
			Nokia5110_OutString(" SCORE");
			Nokia5110_SetCursor(1, 5);
			Nokia5110_OutUDec(score);
			Delay100ms(40);
			++level;
			if(level>3){
				WinGame();
				//return 0;
			}
			ballXcord=36;
			ballYcord=36;
			xval=4;
			yval=-4;

			fe=0;

			Nokia5110_Clear();
			Nokia5110_SetCursor(1, 2);
			Nokia5110_OutString("  Level  ");	
			Nokia5110_SetCursor(1, 4);
			Nokia5110_OutUDec(level);
			Nokia5110_SetCursor(0, 0); // renders screen
			Delay100ms(20);
			display(level);
		}



	}else{
		if(ballXcord <=0 || ballXcord >= 79){//the ball is out of range of the screen left or right 
			xval = -xval;//the ball will reverse its direction 
		}
		if(ballYcord <= 4){//the ball is moving up and  exceeded the foods 
			yval = -yval;//the ball will go down 

		}
		if(ballYcord >= 47){//the player ship missed the ball 
			--lifes;

			if(lifes==0){
			   EndGame();
			    //return 0;
			}
			ballXcord=36;
			ballYcord=36;
			xval=4;
			yval=-4;

		}
		Delay100ms((40-(level*10)));

		ballXcord += xval;
		ballYcord += yval;
	}
}

// *************************** Capture image dimensions out of BMP**********


	
int score=0,level=1,fe=0,lifes=3;
int playerXcord = 32, ballXcord = 36, ballYcord = 36, xval = 4, yval = -4, tx, ty, temp,sw1flag=1,timerflag=1;
int foodArr[21][12]; 
unsigned long Semaphore;
//int SW1 = GPIO_PORTF_DATA_R&0x10;     // read PF4 into SW1
//int SW2 = GPIO_PORTF_DATA_R&0x01;     // read PF0 into SW2



int main(void){
  TExaS_Init(SSI0_Real_Nokia5110_Scope);  // set system clock to 80 MHz
	Nokia5110_Init();

		play();
}

}



void Delay100ms(unsigned long count){unsigned long volatile time;
  while(count>0){
    time = 72724;  // 0.1sec at 80 MHz
    while(time){
	  	time--;
    }
    count--;
  }
}
void draw(int level){
	int i , j ;
for(i=0;i<84;i+=4){
		for(j=8;j<20+level*4;j+=4){
			Nokia5110_PrintBMP(i, j , food, 0);
			
			flage[i/4][j/4] = 1;
		}
	}
}

	void WinGame(){
	Nokia5110_Clear();
  Nokia5110_SetCursor(1, 1);
  Nokia5110_OutString("CONGRATS");
  Nokia5110_SetCursor(1, 2);
  Nokia5110_OutString("YOU WIN");
  Nokia5110_SetCursor(0, 0); // renders screen
	}		
	void startingScreen(){
	Nokia5110_SetCursor(0,0);
	Nokia5110_ClearBuffer();
	Nokia5110_PrintBMP(10, 35, logo, 0);
	Nokia5110_DisplayBuffer();
	Nokia5110_SetCursor(3,5);
	Nokia5110_OutString("DX BALL");	
//	Delay100ms(100);
while(timerflag){//delay 8 sec using timer
    WaitForInterrupt();
  }
	Nokia5110_Clear();
	Nokia5110_ClearBuffer();
	Nokia5110_SetCursor(0,0);
	Nokia5110_OutString("To Play ");	
	Nokia5110_SetCursor(0,1);
	Nokia5110_OutString("Press push ");	
	Nokia5110_SetCursor(0,2);
	Nokia5110_OutString("button 1");	
	/*while(GPIO_PORTF_DATA_R&(1<<4)) {
		
}*/
		while(sw1flag){
		WaitForInterrupt();
}
}
	void display(int level){
	
	Nokia5110_Clear();
  Nokia5110_ClearBuffer();
	Nokia5110_DisplayBuffer();      // draw buffer
	startingScreen();								//draw logo
	Nokia5110_Clear();
  Nokia5110_ClearBuffer();
  Nokia5110_PrintBMP(32, 47, PlayerShip0, 0); // player ship middle bottom
	Nokia5110_PrintBMP(by, by, ball, 0);
  Nokia5110_DisplayBuffer();     // draw buffer
	draw(level);
	Nokia5110_DisplayBuffer();
}



	void Gameover(){
	Nokia5110_Clear();
  Nokia5110_SetCursor(1, 1);
  Nokia5110_OutString("GAME OVER");
  Nokia5110_SetCursor(1, 2);
  Nokia5110_OutString("Nice try,");
	Nokia5110_SetCursor(1, 3);
  Nokia5110_OutString("  Score");
	Nokia5110_SetCursor(1, 4);
  Nokia5110_OutUDec(score);
  Nokia5110_SetCursor(0, 0); // renders screen
	}

// You can use this timer only if you learn how it works
void Timer2_Init(unsigned long period){ 
  unsigned long volatile delay;
  SYSCTL_RCGCTIMER_R |= 0x04;   // 0) activate timer2
  delay = SYSCTL_RCGCTIMER_R;
  Semaphore = 0;
  TIMER2_CTL_R = 0x00000000;    // 1) disable timer2A during setup
  TIMER2_CFG_R = 0x00000000;    // 2) configure for 32-bit mode
  TIMER2_TAMR_R = 0x00000002;   // 3) configure for periodic mode, default down-count settings
  TIMER2_TAILR_R = period-1;    // 4) reload value
  TIMER2_TAPR_R = 0;            // 5) bus clock resolution
  TIMER2_ICR_R = 0x00000001;    // 6) clear timer2A timeout flag
  TIMER2_IMR_R = 0x00000001;    // 7) arm timeout interrupt
  NVIC_PRI5_R = (NVIC_PRI5_R&0x00FFFFFF)|0x80000000; // 8) priority 4
// interrupts enabled in the main program after all devices initialized
// vector number 39, interrupt number 23    for timer2A   datasheet page 104
  NVIC_EN0_R = 1<<23;           // 9) enable IRQ 23 in NVIC  to enable int atasheet page 142
  TIMER2_CTL_R = 0x00000001;    // 10) enable timer2A
}
void Timer2A_Handler(void){		

  TIMER2_ICR_R = 0x00000001;   // acknowledge timer2A timeout
 
  Semaphore = 1; // trigger
	timerflag = 0;
	
}
