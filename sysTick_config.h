#include <stdint.h>
#include "clock_config.h"

#define SysTickControlStatusRegister		0xE000E010
#define SysTickReloadValueRegister			0xE000E014
#define SysTickCurrentValueRegister			0xE000E018
#define SysTickCalibrationValueRegister	0xE000E01C

static uint32_t *sysTickCSR = (uint32_t *)SysTickControlStatusRegister;
static uint32_t *sysTickRVR = (uint32_t *)SysTickReloadValueRegister;
static uint32_t *sysTickCVR = (uint32_t *)SysTickCurrentValueRegister;
static uint32_t *sysTickCalibrationVR = (uint32_t *)SysTickCalibrationValueRegister;

//Function Prototype
void initSysTickTimerInMiliseconds(uint16_t, uint32_t);
