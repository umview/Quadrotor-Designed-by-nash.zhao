#include "include.h"
extern struct SysStruct Sys;
extern struct ParameterStruct Par;
extern struct FlagStruct Flag;
void InnerLoopController(){ //内环 PD 控制器
		Sys.InnerYaw = Sys.YawS * Par.IP;// + Sys.YawA * Par.ID;
		Sys.InnerPitch = Sys.PitchS * Par.IP + Sys.PitchA * Par.ID;
		Sys.InnerRoll = Sys.RollS * Par.IP + Sys.RollA * Par.ID;	

		/*内外环融合 总输出 = 内环 * Inner2Outer + 外环 * (1 - Inner2Outer)*/
		Sys.OutputYaw = Par.Inner2Outer/100.0f * (Sys.InnerYaw - Sys.OuterYaw) + Sys.OuterYaw;
		Sys.OutputPitch = Par.Inner2Outer/100.0f * (Sys.InnerPitch - Sys.OuterPitch) + Sys.OuterPitch;
		Sys.OutputRoll = Par.Inner2Outer/100.0f * (Sys.InnerRoll - Sys.OuterRoll) + Sys.OuterRoll;

		/*ypr输出限幅 限在 可用占空比 * DutyAvailabe */
		Sys.OutputYaw=LIMIT(Sys.OutputYaw,-DutyAvailable*YawAvailable,DutyAvailable*YawAvailable);
		Sys.OutputPitch=LIMIT(Sys.OutputPitch,-DutyAvailable*PitchAvailabe,DutyAvailable*PitchAvailabe);
		Sys.OutputRoll=LIMIT(Sys.OutputRoll,-DutyAvailable*RollAvailable,DutyAvailable*RollAvailable);
//		Sys.OutputYaw=0;
//		Sys.OutputRoll=0;
		/*ypr融合输出 总输出 = 油门 + roll + pitch + yaw + 怠速 */
		Sys.MotorDuty[0]=Par.Thr - Sys.OutputRoll - Sys.OutputPitch + Sys.OutputYaw + Par.IdleThr;
		Sys.MotorDuty[1]=Par.Thr + Sys.OutputRoll - Sys.OutputPitch - Sys.OutputYaw + Par.IdleThr;
		Sys.MotorDuty[2]=Par.Thr + Sys.OutputRoll + Sys.OutputPitch + Sys.OutputYaw + Par.IdleThr;
		Sys.MotorDuty[3]=Par.Thr - Sys.OutputRoll + Sys.OutputPitch - Sys.OutputYaw + Par.IdleThr;
	
		/*总输出限幅*/
		Sys.MotorDuty[0]=LIMIT(Sys.MotorDuty[0],3300,DutyMAX);
		Sys.MotorDuty[1]=LIMIT(Sys.MotorDuty[1],3300,DutyMAX);
		Sys.MotorDuty[2]=LIMIT(Sys.MotorDuty[2],3300,DutyMAX);
		Sys.MotorDuty[3]=LIMIT(Sys.MotorDuty[3],3300,DutyMAX);
}
void OuterLoopController(){//外环 PI 控制器
		float AngleError[3]={0,0,0};
		/*求角度误差*/
		
		AngleError[0]=Sys.Yaw - Par.EY/10.0f;
		AngleError[1]=Sys.Pitch - Par.EP/10.0f;
		AngleError[2]=Sys.Roll - Par.ER/10.0f;
		/*积分分离*/
		Sys.YawErrInt += AngleError[0] * dt * Par.OI;
		Sys.PitchErrInt += AngleError[1] * dt * Par.OI;
		Sys.RollErrInt += AngleError[2] * dt * Par.OI;
		/*积分限幅*/
		Sys.YawErrInt = LIMIT(Sys.YawErrInt,-YEI,YEI);
		Sys.PitchErrInt = LIMIT(Sys.PitchErrInt,-PEI,PEI);
		Sys.RollErrInt = LIMIT(Sys.RollErrInt,-REI,REI);
		/*比例运算*/
		Sys.OuterYaw = AngleError[0] * Par.OP;
		Sys.OuterPitch = AngleError[1] * Par.OP;
		Sys.OuterRoll = AngleError[2] * Par.OP;
		/*外环输出 PI*/
		Sys.OuterYaw += Sys.YawErrInt;
		//Sys.OuterYaw = 0; //防止数据突变，暂无Yaw控制
		Sys.OuterPitch += Sys.PitchErrInt;
		Sys.OuterRoll += Sys.RollErrInt;	
}
void UpdateDuty(uint16_t motor[]){
	if(Flag.MotorEnable==1){
		TIM_SetCompare1(TIM9,motor[0]);	//修改比较值，修改占空比5000
		TIM_SetCompare2(TIM9,motor[1]);	//修改比较值，修改占空比5000
		TIM_SetCompare3(TIM2,motor[2]/2);	//修改比较值，修改占空比2500
		TIM_SetCompare4(TIM2,motor[3]/2);	//修改比较值，修改占空比2500
	}else{
		Sys.MotorDuty[0]=3000;
		Sys.MotorDuty[1]=3000;
		Sys.MotorDuty[2]=3000;
		Sys.MotorDuty[3]=3000;
		TIM_SetCompare1(TIM9,motor[0]);	//修改比较值，修改占空比5000 //E5
		TIM_SetCompare2(TIM9,motor[1]);	//修改比较值，修改占空比5000//E6 MOTOR3
		TIM_SetCompare3(TIM2,motor[2]/2);	//修改比较值，修改占空比2500 //A2
		TIM_SetCompare4(TIM2,motor[3]/2);	//修改比较值，修改占空比2500 //A3
	}

}
//void YawOutputSmooth(){//
//  static uint8 cnt=0;
//  static float dValue;
//  cnt++;
//  if(cnt==1)dValue=(Info.turnduty-Info.turndutyLast)/(float),Info.turnduty=Info.turndutyLast;
//  Info.turnduty+=dValue;
//  if(cnt==TurnPeriod)cnt=0,Info.turndutyLast=Info.turnduty;
//}
