#include "sysTick_config.h"

/*
"This timer is dedicated to the OS, but could also be used as a standard downcounter. 
It is based on a 24-bit downcounter with autoreload capability and a programmable clock source. 
It features a maskable system interrupt generation when the counter reaches 0."[1]
*/

void initSysTickTimerInMiliseconds(uint16_t delayMS, uint32_t clockFreq) {
	uint32_t reloadValue = 0;
	//Clock source -> Core Clock
	*sysTickCSR |= 1ul << 2;
	//SysTick Handler is enabled
	*sysTickCSR |= 1ul << 1;
	//Calculate RELOAD Value 
	if(clockFreq == MSI_RANGE6) {
		if(delayMS >= 4000) delayMS = 4000;
	}
	else if(clockFreq == MSI_RANGE5) {
		if(delayMS >= 8000) delayMS = 8000;
	}
	else {
		if(delayMS >= 10000) delayMS = 10000;
	}
	reloadValue = (delayMS * (clockFreq / 1000)) - 1;
	*sysTickRVR = reloadValue;
	//SysTick Enable
	*sysTickCSR |= 1ul << 0;
}
