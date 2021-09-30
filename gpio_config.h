#include <stdint.h>

#define gpioa_base 		0x40020000
#define moder_offset  0x00
#define bsrr_offset		0x18
#define gpioa_moder		(gpioa_base + moder_offset)
#define gpioa_bsrr		(gpioa_base + bsrr_offset)

static uint32_t *gpioa_moder_register = (uint32_t *)gpioa_moder;
static uint32_t *gpioa_bsrr_register = (uint32_t *)gpioa_bsrr;

//Function Prototype
void setUserLedOutput(void);
void gpioPinSet(uint8_t);
void gpioPinReset(uint8_t);
