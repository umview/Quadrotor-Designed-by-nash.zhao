#include "include.h"
#include "Driver.h"
#include "../HARDWARE/TIMER/timer.h"
extern struct ParameterStruct Par;
extern struct SysStruct Sys;
void QuadrotorInit(){
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//ÉèÖÃÏµÍ³ÖĞ¶ÏÓÅÏÈ¼¶·Ö×é2
	delay_init(180);
	OLED_Init();
	OLED_P8x16Str(0,0,(uint8_t*)"SystemIniting...");
	LED_GPIO_Config();
	Buzzer();
	KEY_Init();
	TeleControlInit();
	digitalToggle(GPIOD,GPIO_Pin_12);
	uart_init(115200);//³õÊ¼»¯´®¿Ú²¨ÌØÂÊÎª115200
	TIM9_OC1_PWM_Init(5000-1,90-1);
	TIM9_OC2_PWM_Init(5000-1,90-1);
	TIM2_OC3_PWM_Init(2500-1,90-1);
	TIM2_OC4_PWM_Init(2500-1,90-1);
  /*³õÊ¼»¯SDRAMÄ£¿é*/
  SDRAM_Init();
	delay_ms(2000);
//	MPU6050_Initialize();    
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
	
		/*¶¨ÒåÒ»¸öGPIO_InitTypeDefÀàĞÍµÄ½á¹¹Ìå*/
		GPIO_InitTypeDef GPIO_InitStructure;

		/*¿ªÆôLEDÏà¹ØµÄGPIOÍâÉèÊ±ÖÓ*/
		RCC_AHB1PeriphClockCmd ( RCC_AHB1Periph_GPIOD, ENABLE); 

		/*Ñ¡ÔñÒª¿ØÖÆµÄGPIOÒı½Å*/															   
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;	 

		/*ÉèÖÃÒı½ÅÄ£Ê½ÎªÊä³öÄ£Ê½*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;   
    
    /*ÉèÖÃÒı½ÅµÄÊä³öÀàĞÍÎªÍÆÍìÊä³ö*/
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    
    /*ÉèÖÃÒı½ÅÎªÉÏÀ­Ä£Ê½£¬Ä¬ÈÏLEDÁÁ*/
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

		/*ÉèÖÃÒı½ÅËÙÂÊÎª50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; 

		/*µ÷ÓÃ¿âº¯Êı£¬Ê¹ÓÃÉÏÃæÅäÖÃµÄGPIO_InitStructure³õÊ¼»¯GPIO*/
		GPIO_Init(GPIOD, &GPIO_InitStructure);	
    GPIO_ResetBits(GPIOD,GPIO_Pin_12);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;	 //·äÃùÆ÷
		GPIO_Init(GPIOD, &GPIO_InitStructure);	
		GPIO_SetBits(GPIOD,GPIO_Pin_11);
/******************************************/
		/*¿ªÆôLEDÏà¹ØµÄGPIOÍâÉèÊ±ÖÓ*/
		RCC_AHB1PeriphClockCmd ( RCC_AHB1Periph_GPIOI|RCC_AHB1Periph_GPIOH, ENABLE); 

		/*Ñ¡ÔñÒª¿ØÖÆµÄGPIOÒı½Å*/															   
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;	 

		/*ÉèÖÃÒı½ÅÄ£Ê½ÎªÊä³öÄ£Ê½*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;   
    
    /*ÉèÖÃÒı½ÅµÄÊä³öÀàĞÍÎªÍÆÍìÊä³ö*/
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    
    /*ÉèÖÃÒı½ÅÎªÉÏÀ­Ä£Ê½£¬Ä¬ÈÏLEDÁÁ*/
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

		/*ÉèÖÃÒı½ÅËÙÂÊÎª50MHz */   
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

		/*Ñ¡ÔñÒª¿ØÖÆµÄGPIOÒı½Å*/															   
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;	 

		/*ÉèÖÃÒı½ÅÄ£Ê½ÎªÊä³öÄ£Ê½*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;   
    
    /*ÉèÖÃÒı½ÅµÄÊä³öÀàĞÍÎªÍÆÍìÊä³ö*/
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
    
    /*ÉèÖÃÒı½ÅÎªÉÏÀ­Ä£Ê½£¬Ä¬ÈÏLEDÁÁ*/
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

		/*ÉèÖÃÒı½ÅËÙÂÊÎª50MHz */   
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
	 int16_t aacx,aacy,aacz;		//¼ÓËÙ¶È´«¸ĞÆ÷Ô­Ê¼Êı¾İ
	short gyrox,gyroy,gyroz;	//ÍÓÂİÒÇÔ­Ê¼Êı¾İ
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//ÉèÖÃÏµÍ³ÖĞ¶ÏÓÅÏÈ¼¶·Ö×é2
	delay_init(168);  //³õÊ¼»¯ÑÓÊ±º¯Êı
	uart_init(115200);//³õÊ¼»¯´®¿Ú²¨ÌØÂÊÎª115200
 	//TIM14_PWM_Init(500-1,84-1);	//84M/84=1MhzµÄ¼ÆÊıÆµÂÊ,ÖØ×°ÔØÖµ500£¬ËùÒÔPWMÆµÂÊÎª 1M/2500=400hz. 
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
		TIM_SetCompare1(TIM9,a);	//ĞŞ¸Ä±È½ÏÖµ£¬ĞŞ¸ÄÕ¼¿Õ±È
		TIM_SetCompare2(TIM9,b);	//ĞŞ¸Ä±È½ÏÖµ£¬ĞŞ¸ÄÕ¼¿Õ±È
		TIM_SetCompare3(TIM2,c);	//ĞŞ¸Ä±È½ÏÖµ£¬ĞŞ¸ÄÕ¼¿Õ±È
		TIM_SetCompare4(TIM2,d);	//ĞŞ¸Ä±È½ÏÖµ£¬ĞŞ¸ÄÕ¼¿Õ±È 
   while(1) //ÊµÏÖ± È½ÏÖµ´Ó0-300µİÔö£¬µ½300ºó´Ó300-0µİ¼õ£¬Ñ­»·
	{ 
		//KEY_Scan();
		//KEY_Scan1();
		delay_ms(100);
		OLEDShowNum(0,0,e,16,16);
		e++;
		MPU_Get_Accelerometer(&aacx,&aacy,&aacz);	//µÃµ½¼ÓËÙ¶È´«¸ĞÆ÷Êı¾İ
		MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);	//µÃµ½ÍÓÂİÒÇÊı¾İ
		OLEDShowNum(0,2,(int)aacx,16,16);
		OLEDShowNum(0,4,(int)gyrox,16,16);
		USART_SendData(USART1,e);         //Ïò´®¿Ú1·¢ËÍÊı¾İ
	}
	*/

