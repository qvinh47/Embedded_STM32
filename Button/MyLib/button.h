#ifndef BUTTON_H
#define	BUTTON_H
#include "main.h"
typedef struct
{
	uint8_t btn_current;
	uint8_t btn_last;
	uint8_t btn_filter;
	uint8_t is_debouncing;
	uint32_t time_deboune;
	uint32_t time_start_press;
	uint8_t	press_timeout;
	GPIO_TypeDef *GPIOx; 
	uint16_t GPIO_Pin;
}Button_Typdef;

__weak void btn_pressing_callback(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
__weak void btn_presshort_callback(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
__weak void btn_release_callback(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
__weak void btn_press_timeout_callback(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

void button_handle(Button_Typdef *buttonX);
void button_init(Button_Typdef *ButtonX,GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
#endif
