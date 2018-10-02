#ifndef _CONFIG_H_
#define _CONFIG_H_
#define STM32F429CORE 1
#define MotorTest 1
#define Kp 1.0f   // proportional gain governs rate of convergence to accelerometer/magnetometer
#define Ki 0.01f   // integral gain governs rate of convergence of gyroscope biases
#define DutyMAX 4999
#define DutyAvailable 2000
#define PitchAvailabe 1
#define YawAvailable 1
#define RollAvailable 1
//#define Inner2Outer 0.7
#define dt 0.005f
#define YEI 600
#define PEI 400
#define REI 400
struct InfoStruct
{
    int16_t     GyroXOffset;
    int16_t     GyroYOffset;
    int16_t     GyroZOffset;
    int16_t     AccXOffset;
    int16_t     AccYOffset;
    int16_t     AccZOffset; 
    int16_t     MagXOffset;
    int16_t     MagYOffset;
    int16_t     MagZOffset;
    float       MagXScale;
    float       MagYScale;
    float       MagZScale;    
};
struct SysStruct
{
	uint32_t timer;
	float Yaw;
	float Pitch;
	float Roll;
	float YawS;
	float PitchS;
	float RollS;
	float YawA;
	float PitchA;
	float RollA;
	float PitchErrInt;
	float YawErrInt;
	float RollErrInt;
	float Altitude,AltitudeS,AltitudeA;
	float Left,LeftS,LeftA;
	float Right,RightS,RightA;
	float Forward,ForwardS,ForwardA;
	float Backward,BackwardS,BackwardA;
	float AbsDistance;
	uint16_t MotorDuty[4];
	int	OutputYaw;
	int OutputPitch;
	int OutputRoll;
	int InnerPitch;
	int InnerRoll;
	int InnerYaw;
	int OuterPitch;
	int OuterYaw;
	int OuterRoll;
	uint8 dip[5];
	uint8 telecontrol[5];
};
struct ParameterStruct
{
	int16_t Thr;
	int16_t IP;
	int16_t ID;
	int16_t	OP;
	int16_t OD;
	int16_t OI;
	int16_t EY;
	int16_t EP;
	int16_t ER;
	int16_t Inner2Outer;
	int16_t YO;
	int16_t PO;
	int16_t RO;
	int16_t IdleThr;
	uint8_t uartbuff[7];
};
struct IMURawStruct
{
	int16_t RawAX;
	int16_t	RawAY;
	int16_t RawAZ;
	int16_t RawGX;
	int16_t RawGY;
	int16_t RawGZ;
	int16_t RawMX;
	int16_t	RawMY;
	int16_t RawMZ;
};
struct FlagStruct
{
		volatile uint8_t FlagSendData;
		volatile int8_t MotorEnable;
		volatile uint8_t Flag1Ms;
		volatile uint8_t Flag2Ms;
		volatile uint8_t Flag5Ms;
		volatile uint8_t Flag20Ms;
		volatile uint8_t Flag254Ms;
		volatile uint8_t UnlockMotor;
		volatile uint8_t Ready;
		volatile uint8_t MenuState;
		volatile int16_t *pMenu[10];
		volatile uint8_t ButtonState[3];
};
#define ABS(x) ( (x)>0?(x):-(x) )
#define LIMIT( x,min,max ) ( (x) < (min)  ? (min) : ( (x) > (max) ? (max) : (x) ) )
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define Buzzer() 	digitalToggle(GPIOD,GPIO_Pin_11)
#define Blink()	{digitalToggle(GPIOI,GPIO_Pin_4);digitalToggle(GPIOI,GPIO_Pin_5);digitalToggle(GPIOI,GPIO_Pin_6);digitalToggle(GPIOI,GPIO_Pin_7);digitalToggle(GPIOI,GPIO_Pin_8);digitalToggle(GPIOI,GPIO_Pin_9);}
#define Start() TimerInit(10u-1,9000u-1)
void ParameterInit(void);
void UnlockMotor(void);



#endif
