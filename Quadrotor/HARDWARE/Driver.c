#include "include.h"
#include "Driver.h"
#include "../HARDWARE/TIMER/timer.h"
extern struct ParameterStruct Par;
extern struct SysStruct Sys;
void QuadrotorInit(){
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(180);
	OLED_Init();
	OLED_P8x16Str(0,0,(uint8_t*)"SystemIniting...");
	LED_GPIO_Config();
	Buzzer();
	KEY_Init();
	TeleControlInit();
	digitalToggle(GPIOD,GPIO_Pin_12);
	uart_init(115200);//初始化串口波特率为115200
  /*初始化SDRAM模块*/
  SDRAM_Init();
	delay_ms(2000);
	MPU6050_Initialize();    
	getOffset();
	/*MotorInit*/
	TIM9_OC1_PWM_Init(5000-1,90-1);
	TIM9_OC2_PWM_Init(5000-1,90-1);
	TIM2_OC3_PWM_Init(2500-1,90-1);
	TIM2_OC4_PWM_Init(2500-1,90-1);
	Sys.MotorDuty[0]=0;
	Sys.MotorDuty[1]=0;
	Sys.MotorDuty[2]=0;
	Sys.MotorDuty[3]=0;
	UpdateDuty(Sys.MotorDuty);
	Init_Quaternion();
	OLED_Fill(0);
}


void LED_GPIO_Config(void)
{		
	
		/*定义一个GPIO_InitTypeDef类型的结构体*/
		GPIO_InitTypeDef GPIO_InitStructure;

		/*开启LED相关的GPIO外设时钟*/
		RCC_AHB1PeriphClockCmd ( RCC_AHB1Periph_GPIOD, ENABLE); 

		/*选择要控制的GPIO引脚*/															   
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;	 

		/*设置引脚模式为输出模式*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;   
    
    /*设置引脚的输出类型为推挽输出*/
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    
    /*设置引脚为上拉模式，默认LED亮*/
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

		/*设置引脚速率为50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; 

		/*调用库函数，使用上面配置的GPIO_InitStructure初始化GPIO*/
		GPIO_Init(GPIOD, &GPIO_InitStructure);	
    GPIO_ResetBits(GPIOD,GPIO_Pin_12);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;	 //蜂鸣器
		GPIO_Init(GPIOD, &GPIO_InitStructure);	
		GPIO_SetBits(GPIOD,GPIO_Pin_11);
/******************************************/
		/*开启LED相关的GPIO外设时钟*/
		RCC_AHB1PeriphClockCmd ( RCC_AHB1Periph_GPIOI|RCC_AHB1Periph_GPIOH, ENABLE); 

		/*选择要控制的GPIO引脚*/															   
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;	 

		/*设置引脚模式为输出模式*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;   
    
    /*设置引脚的输出类型为推挽输出*/
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    
    /*设置引脚为上拉模式，默认LED亮*/
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

		/*设置引脚速率为50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; 
				GPIO_Init(GPIOI, &GPIO_InitStructure);	

		GPIO_SetBits(GPIOI,GPIO_Pin_6);
		GPIO_SetBits(GPIOI,GPIO_Pin_7);
		GPIO_SetBits(GPIOI,GPIO_Pin_8);
		GPIO_SetBits(GPIOI,GPIO_Pin_9);
//		GPIO_SetBits(GPIOI,GPIO_Pin_10);
//		GPIO_SetBits(GPIOI,GPIO_Pin_11);
		GPIO_SetBits(GPIOI,GPIO_Pin_4);
		GPIO_SetBits(GPIOI,GPIO_Pin_5);
			RCC_AHB1PeriphClockCmd ( RCC_AHB1Periph_GPIOH, ENABLE); 

		/*选择要控制的GPIO引脚*/															   
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;	 

		/*设置引脚模式为输出模式*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;   
    
    /*设置引脚的输出类型为推挽输出*/
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
    
    /*设置引脚为上拉模式，默认LED亮*/
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

		/*设置引脚速率为50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; 
				GPIO_Init(GPIOH, &GPIO_InitStructure);	
				GPIO_SetBits(GPIOH,GPIO_Pin_14);

}
/*
	u16 a,b,c,d,e=0;
	a=0;
	b=0;
	c=0;
	d=0;
	 int16_t aacx,aacy,aacz;		//加速度传感器原始数据
	short gyrox,gyroy,gyroz;	//陀螺仪原始数据
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);  //初始化延时函数
	uart_init(115200);//初始化串口波特率为115200
 	//TIM14_PWM_Init(500-1,84-1);	//84M/84=1Mhz的计数频率,重装载值500，所以PWM频率为 1M/2500=400hz. 
		TIM9_OC1_PWM_Init(5000-1,90-1);
		TIM9_OC2_PWM_Init(5000-1,90-1);
		TIM2_OC3_PWM_Init(2500-1,90-1);
		TIM2_OC4_PWM_Init(2500-1,90-1);
		
		OLED_GPIO_Init();
		OLEDInit();
		//OLED_Display_On();
		OLEDClear();
		KEY_Init();
		MPU_Init();
		TIM_SetCompare1(TIM9,a);	//修改比较值，修改占空比
		TIM_SetCompare2(TIM9,b);	//修改比较值，修改占空比
		TIM_SetCompare3(TIM2,c);	//修改比较值，修改占空比
		TIM_SetCompare4(TIM2,d);	//修改比较值，修改占空比 
   while(1) //实现� 冉现荡�0-300递增，到300后从300-0递减，循环
	{ 
		//KEY_Scan();
		//KEY_Scan1();
		delay_ms(100);
		OLEDShowNum(0,0,e,16,16);
		e++;
		MPU_Get_Accelerometer(&aacx,&aacy,&aacz);	//得到加速度传感器数据
		MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);	//得到陀螺仪数据
		OLEDShowNum(0,2,(int)aacx,16,16);
		OLEDShowNum(0,4,(int)gyrox,16,16);
		USART_SendData(USART1,e);         //向串口1发送数据
	}
	*/

