#include "include.h"
extern struct ParameterStruct Par;
extern struct SysStruct Sys;
extern struct FlagStruct Flag;
void ParameterInit(){
	Par.EY=0;
	Par.EP=0;
	Par.ER=0;
	Par.IP=10;
	Par.ID=10;
	Par.OP=46;
	Par.OI=68;
//	Par.IP=0;
//	Par.ID=0;
//	Par.OP=5;
//	Par.OI=0;
	Par.OD=0;
	Par.Thr=0;
	Par.IdleThr=3400;
	Par.Inner2Outer=70;
	Sys.YawErrInt=0;
	Sys.PitchErrInt=0;
	Sys.RollErrInt=0;
	Par.PO=-50;
	Par.RO=30;
	Par.YO=0;
/*******************************/
	Flag.MotorEnable=-1;
	Flag.UnlockMotor=0;
	Flag.Ready=1;
	Flag.MenuState=0;
	Flag.pMenu[0]=&Par.Thr;
	Flag.pMenu[1]=&Par.YO;
	Flag.pMenu[2]=&Par.PO;
	Flag.pMenu[3]=&Par.RO;
	Flag.pMenu[4]=&Par.IP;
	Flag.pMenu[5]=&Par.ID;
	Flag.pMenu[6]=&Par.OP;
	Flag.pMenu[7]=&Par.OI;
	Flag.pMenu[8]=&Par.Inner2Outer;
	Flag.pMenu[9]=&Par.IdleThr;
	Flag.ButtonState[0]=1;
	Flag.ButtonState[1]=0;
	Flag.ButtonState[2]=0;
	digitalToggle(GPIOI,GPIO_Pin_4);
	digitalToggle(GPIOI,GPIO_Pin_5);		
	digitalToggle(GPIOI,GPIO_Pin_6);		
	digitalToggle(GPIOI,GPIO_Pin_7);		
	digitalToggle(GPIOI,GPIO_Pin_8);
	digitalToggle(GPIOI,GPIO_Pin_9);
}
void UnlockMotor(void){
	while(1){
		if(Flag.UnlockMotor){
				u16 pwm=0;
			Flag.MotorEnable=1;
			while(!GPIOCin(2)){
			Sys.MotorDuty[0]=pwm;
			Sys.MotorDuty[1]=pwm;
			Sys.MotorDuty[2]=pwm;
			Sys.MotorDuty[3]=pwm;
			OLED_Print_Num(0,0,pwm);
				UpdateDuty(Sys.MotorDuty);
				SDS_OutData[3]=pwm;
				Plot(SDS_OutData);
				delay_ms(200);
				pwm+=30;
				if(pwm>=360){
					//Flag.MotorEnable=-1;
						//OLED_Print_Num1(12,6,pwm);
					OLED_Fill(0);
					Flag.MotorEnable=-1;
					break;
				}
			}
			break;
		}
	}
}
