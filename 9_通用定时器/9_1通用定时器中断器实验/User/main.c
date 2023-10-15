#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/TIMER/gtim.h"
/* 
    LED0用来指示程序正在运行，200ms翻转一次。LED1在定时器中断中翻转，500ms进入中断一次

    原理：定时器属于开发板内部资源，只需要软件设置好即可正常运行，
          通过LED1来指示定时器进入中断的频率，LED0则指示程序的运行状态

    程序设计：main函数中并没有对LED1的操作，我们把对LED1的操作放到定时器的中断中进行处理
 */

int main(void)
{    
    HAL_Init();                             /* 初始化HAL库 */
    sys_stm32_clock_init(336, 8, 2, 7);     /* 设置时钟,168Mhz */
    delay_init(168);                        /* 延时初始化 */
    usart_init(115200);                     /* 串口初始化为115200 */
    led_init();                             /* 初始化LED */
    gtim_timx_int_init(5000 - 1, 8400 - 1); /* 84 000 000 / 84 00 = 10 000 10Khz的计数频率，计数5K次为500ms */
    
    while(1)
    {
        LED0_TOGGLE();                      /* LED0(红灯) 翻转 */
        delay_ms(200);
    }
}

