#include "include.h"
extern float SDS_OutData[4];
uint8_t Send_Count,i;
struct InfoStruct Info;
struct FlagStruct Flag;
struct SysStruct Sys;
struct ParameterStruct Par;
extern volatile float mygetqval[9];	//用于存放传感器转换结果的数组

int main(void)
{ 
	Sys.timer=0;
	QuadrotorInit();
	ParameterInit();
	Flag.UnlockMotor=1;// default for unlock
	if(GPIOIin(0))UnlockMotor();
	digitalToggle(GPIOD,GPIO_Pin_12);
	OLED_P8x16Str(0,3,(uint8_t*)"Ready to GO!");
	delay_ms(2000);
	OLED_Fill(0);
	Start();
	Buzzer();
	for(;;){
		LOOP();
	}

}


