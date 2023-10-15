#include "stm32f4xx.h"   
#include "RTE_Components.h"             // Component selection
#include "tz_context.h"                 // ARM::CMSIS:CORE
int main(void)
{
               // Device header
	HAL_Init();

 SystemClock_config();

 MX_GPIO_Init();
 /* USER CODE BEGIN WHILE */
 while (1)
 {
 /* USER CODE END WHILE */
 }
}