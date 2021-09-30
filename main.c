/*
Author			 : Mehmet KORAL
Title				 : SysTick Timer
Date		     : 30.09.2021
Useful Links :
	*[1]Cortex M3 Technical Referenca Manual - r2p0   - http://www.keil.com/dd/docs/datashts/arm/cortex_m3/r2p0/ddi0337g_cortex_m3_r2p0_trm.pdf
	*[2]Reference Manual 							      - RM0038 - https://www.st.com/resource/en/reference_manual/cd00240193-stm32l100xx-stm32l151xx-stm32l152xx-and-stm32l162xx-advanced-arm-based-32-bit-mcus-stmicroelectronics.pdf
	*[3]STM32L152RE Datasheet 												 - https://www.st.com/resource/en/datasheet/stm32l152re.pdf
*/

#include "stm32l1xx.h"                  // Device header
#include <stdint.h>

#define rcc_base			0x40023800
#define ahb_offset		0x1c
#define rcc_ahb_enr		(rcc_base + ahb_offset)

#define gpioa_base 		0x40020000
#define moder_offset  0x00
#define bsrr_offset		0x18
#define gpioa_moder		(gpioa_base + moder_offset)
#define gpioa_bsrr		(gpioa_base + bsrr_offset)

#define SysTickControlStatusRegister		0xE000E010
#define SysTickReloadValueRegister			0xE000E014
#define SysTickCurrentValueRegister			0xE000E018
#define SysTickCalibrationValueRegister	0xE000E01C

void initSysTickTimer(uint16_t);
void gpio_pin_set(uint8_t);
void gpio_pin_reset(uint8_t);

/*
"This timer is dedicated to the OS, but could also be used as a standard downcounter. 
It is based on a 24-bit downcounter with autoreload capability and a programmable clock source. 
It features a maskable system interrupt generation when the counter reaches 0."[1]
*/

uint32_t clock;

uint32_t *ahb_enr_reg = (uint32_t *)rcc_ahb_enr;
uint32_t *gpioa_moder_reg = (uint32_t *)gpioa_moder;
uint32_t *gpioa_bsrr_reg = (uint32_t *)gpioa_bsrr;

uint32_t *sysTickCSR = (uint32_t *)SysTickControlStatusRegister;
uint32_t *sysTickRVR = (uint32_t *)SysTickReloadValueRegister;
uint32_t *sysTickCVR = (uint32_t *)SysTickCurrentValueRegister;
uint32_t *sysTickCalibrationVR = (uint32_t *)SysTickCalibrationValueRegister;

int8_t pinStatus = 0;

void initSysTickTimer(uint16_t delayMS) {
	uint32_t reloadValue = 0;
	//Clock source -> Core Clock
	*sysTickCSR |= 1ul << 2;
	//SysTick Handler is enabled
	*sysTickCSR |= 1ul << 1;
	//Calculate RELOAD Value  (SystemCoreClock -> 2097000 as a default value)
	reloadValue = (delayMS * SystemCoreClock / 1000) - 1;
	*sysTickRVR = reloadValue;
	//SysTick Enable
	*sysTickCSR |= 1ul << 0;
}

void SysTick_Handler(void) {
	pinStatus++;
	if(pinStatus == 1) gpio_pin_set(5);
	if(pinStatus == 2) {
		gpio_pin_reset(5);
		pinStatus = 0;
	}
}

void gpio_pin_set(uint8_t pinNo) {
	*gpioa_bsrr_reg |= 1ul << pinNo;
}

void gpio_pin_reset(uint8_t pinNo) {
	*gpioa_bsrr_reg |= 1ul << (pinNo + 16);
}

int main() {
	/*
	"The MSI clock is used as system clock after restart from Reset, wake-up from Stop, and Standby low-power mode. 
	After restart from Reset or wake-up from Standby, the MSI frequency is set to its default value.
	2.097 MHz is default value."[2]
	*/
	clock = SystemCoreClock;
	*ahb_enr_reg |= 1ul << 0;				//GPIOA Clock enable over RCC_AHBENR REGISTER
	*gpioa_moder_reg |= 1ul << 10;	//PA5 is output
	
	initSysTickTimer(1000);					//1000ms

	while(1) {

	}
}
