/*
Author			 : Mehmet KORAL
Title				 : SysTick Timer with Variable Clock Frequencies supplied by MSI
Date		     : 30.09.2021
Useful Links :
	*[1]Cortex M3 Technical Referenca Manual - r2p0   - http://www.keil.com/dd/docs/datashts/arm/cortex_m3/r2p0/ddi0337g_cortex_m3_r2p0_trm.pdf
	*[2]Reference Manual 							      - RM0038 - https://www.st.com/resource/en/reference_manual/cd00240193-stm32l100xx-stm32l151xx-stm32l152xx-and-stm32l162xx-advanced-arm-based-32-bit-mcus-stmicroelectronics.pdf
	*[3]STM32L152RE Datasheet 												 - https://www.st.com/resource/en/datasheet/stm32l152re.pdf
*/

#include "gpio_config.h"
#include "sysTick_config.h"

#define MSI_CLOCK_RANGE		RANGE5

uint32_t clockFrequency;					//This variable for debugging 
int8_t pinStatus = 0;

int main() {
	clockFrequency = MSI_Clock_Speed_Change(MSI_CLOCK_RANGE);
	setUserLedOutput();	
	initSysTickTimerInMiliseconds(100, clockFrequency);							
	
	while(1) {

	}
}

void SysTick_Handler(void) {
	pinStatus++;
	if(pinStatus == 1) {
		gpioPinSet(5);
	}
	if(pinStatus == 2) {
		gpioPinReset(5);
		pinStatus = 0;
	}
}
