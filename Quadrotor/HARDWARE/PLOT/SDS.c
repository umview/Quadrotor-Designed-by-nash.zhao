#include "SDS.h"
#include "include.h"

//#include "uart.h"  //LINK TO UART

float SDS_OutData[4];


unsigned short CRC_CHECK(unsigned char *Buf, unsigned char CRC_CNT)
{
    unsigned short CRC_Temp;
    unsigned char i,j;
    CRC_Temp = 0xffff;

    for (i=0;i<CRC_CNT; i++){
        CRC_Temp ^= Buf[i];
        for (j=0;j<8;j++) {
            if (CRC_Temp & 0x01)
                CRC_Temp = (CRC_Temp >>1 ) ^ 0xa001;
            else
                CRC_Temp = CRC_Temp >> 1;
        }
    }
    return(CRC_Temp);
}

void Plot(float S_Out[])
{
  int temp[4] = {0};
  unsigned int temp1[4] = {0};
  unsigned char databuf[10] = {0};
  unsigned char i;
  unsigned short CRC16 = 0;
 // float SDS_OutData[4];
  /*for(i=0;i<4;i++) {
  SDS_OutData[i]=S_Out[i];
  }*/
  for(i=0;i<4;i++)
   {

    temp[i]  = (int)SDS_OutData[i];
    temp1[i] = (unsigned int)temp[i];

   }

  for(i=0;i<4;i++)
  {
    databuf[i*2]   = (unsigned char)(temp1[i]%256);
    databuf[i*2+1] = (unsigned char)(temp1[i]/256);
  }

  CRC16 = CRC_CHECK(databuf,8);
  databuf[8] = CRC16%256;
  databuf[9] = CRC16/256;

  //SDS_UART_Init();
  for(i=0;i<10;i++)
  {
    //USART_SendData(USART6,databuf[i]);
    //LPLD_UART_PutChar(UART5, databuf[i]);  //LINK TO UART
//#ifdef STM32F429CORE
			while((USART1->SR&0X40)==0);  
			USART1->DR = databuf[i]; 
		//USART6->DR = (databuf[i] & (uint16_t)0x01FF);
		//USART_SendData(USART6,databuf[i]);
//#else
//			while((USART1->SR&0X40)==0);  
//			USART1->DR = databuf[i]; 
//#endif
  }
}
