#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/TIMER/gtim.h"


extern TIM_HandleTypeDef g_timx_pwm_chy_handle; /* 定时器x句柄 */

int main(void)
{
    uint16_t ledrpwmval = 0;
    uint8_t dir = 1;
    
    HAL_Init();                                 /* 初始化HAL库 */
    sys_stm32_clock_init(336, 8, 2, 7);         /* 设置时钟,168Mhz */
    delay_init(168);                            /* 延时初始化 */
    usart_init(115200);                         /* 串口初始化为115200 */
    led_init();                                 /* 初始化LED */
    gtim_timx_pwm_chy_init(500 - 1, 84 - 1);    /* 84 000 000 / 84 = 1 000 000 1Mhz的计数频率，2Khz的PWM */
    
    while (1)
    {
        delay_ms(10);

        if (dir)ledrpwmval++;                   /* dir==1 ledrpwmval递增 */
        else ledrpwmval--;                      /* dir==0 ledrpwmval递减 */

        if (ledrpwmval > 300)dir = 0;           /* ledrpwmval到达300后，方向为递减 */
        if (ledrpwmval == 0)dir = 1;            /* ledrpwmval递减到0后，方向改为递增 */

        /* 修改比较值控制占空比 */
        __HAL_TIM_SET_COMPARE(&g_timx_pwm_chy_handle, GTIM_TIMX_PWM_CHY, ledrpwmval);
    }
}


