#include <stdint.h>

//MSI Clock Frequencies in Hz
#define MSI_RANGE0																			65536
#define MSI_RANGE1																			131072
#define MSI_RANGE2																			262144
#define MSI_RANGE3																			524288
#define MSI_RANGE4																			1048000
#define MSI_RANGE5																			2097000
#define MSI_RANGE6																			4194000

static enum {
	RANGE0,
	RANGE1,
	RANGE2,
	RANGE3,
	RANGE4,
	RANGE5,
	RANGE6
}MSI_ranges;

//RCC Registers
#define rcc_base																				0x40023800
#define cr_offset																				0x00
#define icsr_offset																			0x04
#define cfgr_offset																			0x08
#define ahb_offset																			0x1c
#define ClockControlRegister  													(rcc_base + cr_offset)
#define InternalClockSourcesCalibrationRegister  				(rcc_base + icsr_offset)
#define ClockConfigurationRegister											(rcc_base + cfgr_offset)
#define AHBPeripheralClockEnableRegister								(rcc_base + ahb_offset)

static uint32_t *clock_control_register = (uint32_t *)ClockControlRegister;
static uint32_t *clock_calibration_register = (uint32_t *)InternalClockSourcesCalibrationRegister;
static uint32_t *clock_configuration_register = (uint32_t *)ClockConfigurationRegister;
static uint32_t *ahb_clock_enable_register = (uint32_t *)AHBPeripheralClockEnableRegister;

//Function Prototype
uint32_t MSI_Clock_Speed_Change(int8_t);
