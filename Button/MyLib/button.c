#include "button.h"

__weak  void btn_pressing_callback(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin) //nhan xuong
{
	
}
__weak void btn_presshort_callback(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin) // nhan nha nhanh
{ 

}
__weak void btn_release_callback(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin) // nha nut ra sau nhan lau
{

}
__weak void btn_press_timeout_callback(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{

}

void button_handle(Button_Typdef *buttonX)
	
{
	// Loc nhieu---------------------------------------------------------------------------------
	uint8_t sta = HAL_GPIO_ReadPin(buttonX -> GPIOx, buttonX->GPIO_Pin);//sua code o doan nayGPIO_PIN_0
	if(sta != buttonX ->  btn_filter)
	{
		buttonX ->btn_filter = sta;
		buttonX ->is_debouncing = 1;
		buttonX ->time_deboune = HAL_GetTick();
	}

	// Tin hieu da xac lap---------------------------------------------------------------------------------
	if(buttonX ->is_debouncing && (HAL_GetTick() - buttonX -> time_deboune >= 15))
	{
	buttonX -> btn_current = buttonX -> btn_filter;
		buttonX ->is_debouncing = 0;
	}
	// Xu li------------------------------------------------------------------------------------------------
	if(buttonX ->btn_current != buttonX ->btn_last)
	{
		if(buttonX ->btn_current == 0) //nhan xuong
		{
			buttonX ->press_timeout = 1;
			btn_pressing_callback(buttonX-> GPIOx,buttonX-> GPIO_Pin);
		buttonX ->time_start_press = HAL_GetTick();
		}
		else //nha nut-------------------------------------------------------------------------------------------
		{
			if(HAL_GetTick()- buttonX ->time_start_press <=1000)
			{
				btn_presshort_callback(buttonX-> GPIOx,buttonX-> GPIO_Pin); 
			}
			btn_release_callback(buttonX-> GPIOx,buttonX-> GPIO_Pin);
			buttonX ->press_timeout = 0;
		}
		buttonX ->btn_last = buttonX ->btn_current;
	}
	//nhan giu------------------------------------------------------------------------------------------- 
	if(buttonX ->press_timeout &&(HAL_GetTick()- buttonX ->time_start_press >=3000))
	{
		btn_press_timeout_callback(buttonX-> GPIOx,buttonX-> GPIO_Pin);
		buttonX -> press_timeout = 0;
	}
}
void button_init(Button_Typdef *ButtonX,GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	ButtonX -> GPIOx = GPIOx;
	ButtonX -> GPIO_Pin = GPIO_Pin;	
}
