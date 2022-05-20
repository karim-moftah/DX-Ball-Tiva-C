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


