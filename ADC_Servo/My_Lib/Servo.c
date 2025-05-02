#include "Servo.h"
//ham map adruino google search
long map(long x, long in_min, long in_max, long out_min, long out_max)
	{
      return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
  }
	
void servo_write(Servo *sv, uint8_t goc)
{
	//goc :0-180
	//CCR: 1ms-2ms : 1000-2000 gia tri thuc su trong file lib servo arduino 
	//: 544-2400 //2580 gia tri tu hieu chinh
	//unit16_t CCR = (goc-0)*(2000-1000)/(180-0)+1000;
	uint16_t CCR = map(goc,0,180,544,2580);
	switch(sv->channel)
	{
		case TIM_CHANNEL_1:
			sv->htim ->Instance ->CCR1 = CCR;
			break;
		case TIM_CHANNEL_2:
			sv->htim ->Instance ->CCR2 = CCR;
			break;
		case TIM_CHANNEL_3:
			sv->htim ->Instance ->CCR3 = CCR;
			break;
		case TIM_CHANNEL_4:
			sv->htim ->Instance ->CCR4 = CCR;
			break;
	}
}
void servo_init(Servo *sv,TIM_HandleTypeDef *htim, uint16_t channel)
{
	sv-> htim = htim;
	sv-> channel = channel;
	HAL_TIM_PWM_Start(htim,channel);
	
}
