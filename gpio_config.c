#include "gpio_config.h"
#include "clock_config.h"

void setUserLedOutput(void) {
	*ahb_clock_enable_register |= 1ul << 0;				//GPIOA Clock enable over RCC_AHBENR REGISTER
	*gpioa_moder_register |= 1ul << 10;						//PA5 is output
}

void gpioPinSet(uint8_t pinNo) {
	*gpioa_bsrr_register |= 1ul << pinNo;
}

void gpioPinReset(uint8_t pinNo) {
	*gpioa_bsrr_register |= 1ul << (pinNo + 16);
}
