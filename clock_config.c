#include "clock_config.h"

uint32_t MSI_Clock_Speed_Change(int8_t MSI_Clock_Speed_Index) {
	/*
	MSIRANGE : 0->6 
	When range 0 (65.536 kHz) is selected, the system is break!
	Go to "options for target"
	"Debug" -> "Settings"
	"Connect & Reset Options" is located at the bottom of the window
	Connect: "under reset"
	*/
	//Clear MSIRANGE[2:0]
	*clock_calibration_register = 0x007A1052; 
	while(!((*clock_control_register) & 0x00000200) >> 9);		//Check MSIRDY?
	//Check MSI Range
	if(MSI_Clock_Speed_Index <= 0) MSI_Clock_Speed_Index = 0;
	if(MSI_Clock_Speed_Index >= 6) MSI_Clock_Speed_Index = 6;
	//Change MSI value to new range
	*clock_calibration_register |= MSI_Clock_Speed_Index << 13; 
	while(!((*clock_control_register) & 0x00000200) >> 9);		//Check MSIRDY?
	//MSI clock frequency has been changed to new value
	if(MSI_Clock_Speed_Index == 0) return (uint32_t)MSI_RANGE0;
	else if(MSI_Clock_Speed_Index == 1) return (uint32_t)MSI_RANGE1;
	else if(MSI_Clock_Speed_Index == 2) return (uint32_t)MSI_RANGE2;
	else if(MSI_Clock_Speed_Index == 3) return (uint32_t)MSI_RANGE3;
	else if(MSI_Clock_Speed_Index == 4) return (uint32_t)MSI_RANGE4;
	else if(MSI_Clock_Speed_Index == 5) return (uint32_t)MSI_RANGE5;
	else if(MSI_Clock_Speed_Index == 6) return (uint32_t)MSI_RANGE6;
	else return 0;
}
