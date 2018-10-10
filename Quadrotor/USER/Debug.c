#include "include.h"
extern struct SysStruct Sys;
extern struct ParameterStruct Par;
extern struct FlagStruct Flag;
extern volatile float angle[3];
void LOOP(void){
		if(Flag.FlagSendData){
			SendData();
			Plot(SDS_OutData);
			Flag.FlagSendData=0;
		}
		BlueToothCtrl();
		ShowMenu();
		DebugKey();
}
#define n 3
void Decoder(void){
	static uint8 i=0;
	static uint8 buff[3]={0};
	if(!i&&Par.uartbuff[n]==0x00){
		i++;
	}else if(Par.uartbuff[n]==0xff&&i==1){
		i++;
	}else if(Par.uartbuff[n]==0xff&&i==5){
		i++;
	}else if(Par.uartbuff[n]==0x00&&i==6){
		i++;
	}else if(i>=2 && i<=4){
		buff[i++]=Par.uartbuff[n];
	}
	if(i==7){
		i=0;
		Sys.LeftS=(float)buff[0];
		Sys.RightS=(float)buff[1];
		Sys.AbsDistance=(float)(Par.uartbuff[n]*10);//(float)buff[2];
	}
}
#define N 6
void SendData(void){
	if(Flag.ButtonState[1]%N==0){
		SDS_OutData[0]=(int16)Sys.Yaw*10;
		SDS_OutData[1]=(int16)Sys.Pitch*10;
		SDS_OutData[2]=(int16)Sys.Roll*10;
		SDS_OutData[3]=Par.Thr;
	}else if(Flag.ButtonState[1]%N==1){
		SDS_OutData[0]=(int16)Sys.YawS*10;
		SDS_OutData[1]=(int16)Sys.PitchS*10;
		SDS_OutData[2]=(int16)Sys.RollS*10;
		SDS_OutData[3]=Par.Thr;
	}else if(Flag.ButtonState[1]%N==2){
		SDS_OutData[0]=(int16)Sys.YawA*10;
		SDS_OutData[1]=(int16)Sys.PitchA*10;
		SDS_OutData[2]=(int16)Sys.RollA*10;
		SDS_OutData[3]=Par.Thr;
	}else if(Flag.ButtonState[1]%N==3){
		SDS_OutData[0]=Sys.MotorDuty[0];
		SDS_OutData[1]=Sys.MotorDuty[1];
		SDS_OutData[2]=Sys.MotorDuty[2];
		SDS_OutData[3]=Sys.MotorDuty[3];
	}else if(Flag.ButtonState[1]%N==4){
		SDS_OutData[0]=(int16)Sys.OutputYaw;
		SDS_OutData[1]=(int16)Sys.OutputPitch;
		SDS_OutData[2]=(int16)Sys.OutputRoll;
		SDS_OutData[3]=0;
	}else if(Flag.ButtonState[1]%N==5){
		SDS_OutData[0]=(int16)Sys.YawErrInt;
		SDS_OutData[1]=(int16)Sys.PitchErrInt;
		SDS_OutData[2]=(int16)Sys.RollErrInt;
		SDS_OutData[3]=0;
	}else if(Flag.ButtonState[1]%N==6){
		SDS_OutData[0]=(int16)Sys.OutputYaw;
		SDS_OutData[1]=(int16)Sys.OutputPitch;
		SDS_OutData[2]=(int16)Sys.OutputRoll;
		SDS_OutData[3]=0;
	}
}
void BlueToothCtrl(void){
	static uint8_t offset=0;
	if(Par.uartbuff[6]>='0'&&Par.uartbuff[6]<='9'){
		Blink();
		offset=(int16_t)(Par.uartbuff[6]-0x30);
		Par.uartbuff[6]=0;
		return;
	}
	if(Par.uartbuff[6]=='+'){
		Blink();
		*(Flag.pMenu[offset])=*(Flag.pMenu[offset])+1;
		Par.uartbuff[6]=0;
		return;
	}
	if(Par.uartbuff[6]=='-'){
		Blink();
		*(Flag.pMenu[offset])=*(Flag.pMenu[offset])-1;
		Par.uartbuff[6]=0;
		return;
	}
	if(Par.uartbuff[6]=='s'){
		Blink();
		Flag.MotorEnable=-1;
		Par.uartbuff[6]=0;
	}
	if(Par.uartbuff[6]=='r'){
		Blink();
		Par.YO=(int16_t)(angle[0]*100.0f);
		Par.PO=(int16_t)(angle[1]*100.0f);
		Par.RO=(int16_t)(angle[2]*100.0f);
		Par.uartbuff[6]=0;
	}
	if(Par.uartbuff[6]=='S'){
		Blink();
		Par.uartbuff[6]=0;
		Flag.MotorEnable=1;
	}
		
}
void DebugKey(){
	static uint8 buff[6][2]={0};
	uint8 i=0;
	for(i=0;i<6;i++){
		buff[i][0]=buff[i][1];
	}
	buff[0][1]=GPIO_ReadInputDataBit(GPIOH,GPIO_Pin_9);
	buff[1][1]=GPIO_ReadInputDataBit(GPIOH,GPIO_Pin_10);
	buff[2][1]=GPIO_ReadInputDataBit(GPIOH,GPIO_Pin_11);
	buff[3][1]=GPIO_ReadInputDataBit(GPIOH,GPIO_Pin_12);
	buff[4][1]=GPIO_ReadInputDataBit(GPIOH,GPIO_Pin_13);
	buff[5][1]=GPIO_ReadInputDataBit(GPIOH,GPIO_Pin_14);
	Sys.dip[0]=GPIOIin(0);
	Sys.dip[1]=GPIOIin(1);
	Sys.dip[2]=GPIOIin(2);
	Sys.dip[3]=GPIOIin(3);
	Sys.telecontrol[0]=GPIOCin(1);
	Sys.telecontrol[1]=GPIOCin(2);
	Sys.telecontrol[2]=GPIOCin(3);
	Sys.telecontrol[3]=GPIOCin(4);
	if(Sys.telecontrol[0]){
			Flag.MotorEnable*=-1;	
			delay_ms(800);
			digitalToggle(GPIOI,GPIO_Pin_4);
			digitalToggle(GPIOI,GPIO_Pin_5);		
			digitalToggle(GPIOI,GPIO_Pin_6);		
			digitalToggle(GPIOI,GPIO_Pin_7);		
			digitalToggle(GPIOI,GPIO_Pin_8);
			digitalToggle(GPIOI,GPIO_Pin_9);
	}
	if(buff[0][0]&&!buff[0][1]){//H9
		Flag.ButtonState[0]++;
		OLED_Fill(0);
					//digitalToggle(GPIOD,GPIO_Pin_11);
//		if(Sys.dip[1]&&Sys.dip[2])Par.IP++;
//		if(!Sys.dip[1]&&Sys.dip[2])Par.OP++;
//		if(!Sys.dip[1]&&!Sys.dip[2])Par.YO+=0.01f;
	}
	if(buff[1][0]&&!buff[1][1]){//H10
		Flag.ButtonState[1]++;
					//digitalToggle(GPIOD,GPIO_Pin_11);
//		if(Sys.dip[1]&&Sys.dip[2])Par.IP--;
//		if(!Sys.dip[1]&&Sys.dip[2])Par.OP--;
//		if(!Sys.dip[1]&&!Sys.dip[2])Par.YO-=0.01f;
	}
	if(buff[2][0]&&!buff[2][1]){//H11
		Flag.ButtonState[2]++;
					//digitalToggle(GPIOD,GPIO_Pin_11);
//		if(Sys.dip[1]&&Sys.dip[2])Par.ID++;
//		if(!Sys.dip[1]&&Sys.dip[2])Par.OI++;
//		if(!Sys.dip[1]&&!Sys.dip[2])Par.PO+=0.01f;
	}
//	if(buff[3][0]&&!buff[3][1]){//D12
//					//digitalToggle(GPIOD,GPIO_Pin_11);
//		if(Sys.dip[1]&&Sys.dip[2])Par.ID--;
//		if(!Sys.dip[1]&&Sys.dip[2])Par.OI--;
//		if(!Sys.dip[1]&&!Sys.dip[2])Par.PO-=0.01f;
//	}
//	if(buff[4][0]&&!buff[4][1]){//D13
//					//digitalToggle(GPIOD,GPIO_Pin_11);
//		if(!Sys.dip[1]&&!Sys.dip[2])Par.RO+=0.01f;
//	}
//	if(buff[5][0]&&!buff[5][1]){//D14
//					//digitalToggle(GPIOD,GPIO_Pin_11);
//		if(!Sys.dip[1]&&!Sys.dip[2])Par.RO-=0.01f;
//	}
}
void EXTI9_5_IRQHandler(void){
	if(EXTI_GetITStatus(EXTI_Line8)!= RESET) //确保是否产生了EXTI Line中断
	{
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)){//PA8
			delay_ms(50);
			if(GPIOAin(8)){
			//Flag.UnlockMotor=1;
			//digitalToggle(GPIOD,GPIO_Pin_11);
			if(Flag.Ready==1)Flag.MotorEnable=1;
			else{
				Flag.MotorEnable=-1;
				Flag.Ready=0;
			}
			digitalToggle(GPIOI,GPIO_Pin_4);
			digitalToggle(GPIOI,GPIO_Pin_5);		
			digitalToggle(GPIOI,GPIO_Pin_6);		
			digitalToggle(GPIOI,GPIO_Pin_7);		
			digitalToggle(GPIOI,GPIO_Pin_8);
			digitalToggle(GPIOI,GPIO_Pin_9);
			}
		}
	}		
}
void USART6_IRQHandler(){
	if(USART_GetITStatus(USART6, USART_IT_RXNE) != RESET)
	{ 	
			Par.uartbuff[6] = (uint16_t)(USART6->DR & (uint16_t)0x01FF);
			//Par.uartbuff[3]= Par.uartbuff[6];
			//Decoder();
	} 
}
void USART2_IRQHandler(){
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
	{ 	
			Par.uartbuff[2] = (uint16_t)(USART2->DR & (uint16_t)0x01FF);
			//Decoder();
	} 
}
void USART3_IRQHandler(){
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
	{ 	
			Par.uartbuff[3] = (uint16_t)(USART3->DR & (uint16_t)0x01FF);
			Decoder();
	} 
}
void EXTI0_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line0)!= RESET) //确保是否产生了EXTI Line中断
	{
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)){//PA0
			//Flag.UnlockMotor=1;
			//Flag.Ready=1;
			//digitalToggle(GPIOD,GPIO_Pin_11);
			Flag.MotorEnable=-1;
			digitalToggle(GPIOI,GPIO_Pin_4);
			digitalToggle(GPIOI,GPIO_Pin_5);		
			digitalToggle(GPIOI,GPIO_Pin_6);		
			digitalToggle(GPIOI,GPIO_Pin_7);		
			digitalToggle(GPIOI,GPIO_Pin_8);
			digitalToggle(GPIOI,GPIO_Pin_9);
		}
	}		 

	 EXTI_ClearITPendingBit(EXTI_Line0); //清除LINE0上的中断标志位 
}	
void ShowMenu(){
	static uint16_t i=0;
	if(i++>65530){
		if(Flag.ButtonState[0]%3==0){
			OLED_P6x8Str(0,0,"IP");OLED_Print_Num1(12,0,Par.IP);
			OLED_P6x8Str(54,0,"ID");OLED_Print_Num1(66,0,Par.ID);//OLED_Print_Num1(108,0,Sys.dip[1]);
			OLED_P6x8Str(0,1,"OP");OLED_Print_Num1(12,1,Par.OP);
			OLED_P6x8Str(54,1,"OI");OLED_Print_Num1(66,1,Par.OI);
			OLED_P6x8Str(0,2,"TH");OLED_Print_Num1(12,2,Par.Thr);
			OLED_P6x8Str(60,2,"EY");OLED_Print_Num1(66,2,Par.EY);
			OLED_P6x8Str(0,3,"EP");OLED_Print_Num1(12,3,Par.EP);
			OLED_P6x8Str(54,3,"ER");OLED_Print_Num1(66,3,Par.ER);
			OLED_P6x8Str(0,4,"YO");OLED_Print_Num1(12,4,Par.YO);
			OLED_P6x8Str(54,4,"PO");OLED_Print_Num1(66,4,Par.PO);
			OLED_P6x8Str(0,5,"RO");OLED_Print_Num1(12,5,Par.RO);
			OLED_P6x8Str(54,5,"I0");OLED_Print_Num1(66,5,Par.Inner2Outer);
			OLED_P6x8Str(0,6,"M1");OLED_Print_Num1(12,6,Sys.MotorDuty[0]);
			OLED_P6x8Str(54,6,"M2");OLED_Print_Num1(66,6,Sys.MotorDuty[1]);
			OLED_P6x8Str(0,7,"M3");OLED_Print_Num1(12,7,Sys.MotorDuty[2]);
			OLED_P6x8Str(54,7,"M4");OLED_Print_Num1(66,7,Sys.MotorDuty[3]);
		}else if(Flag.ButtonState[0]%3==1){
			OLED_P8x16Str(2,0,"Y");OLED_Print_Num(20,0,Sys.Yaw*100);
			OLED_P8x16Str(2,2,"P");OLED_Print_Num(20,2,Sys.Pitch*100);//OLED_Print_Num1(108,0,Sys.dip[1]);
			OLED_P8x16Str(2,4,"R");OLED_Print_Num(20,4,Sys.Roll*100);
		}else if(Flag.ButtonState[0]%3==2){
			OLED_P8x16Str(2,0,"X");OLED_Print_Num(20,0,Sys.LeftS*100);
			OLED_P8x16Str(2,2,"Y");OLED_Print_Num(20,2,Sys.RightS*100);//OLED_Print_Num1(108,0,Sys.dip[1]);
			OLED_P8x16Str(2,4,"Z");OLED_Print_Num(20,4,Par.uartbuff[2]);
		}
		i=0;
	}
}
