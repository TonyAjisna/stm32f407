#include "./BSP/TIMER/gtim.h"
#include "./BSP/LED/led.h"

/* 定时器配置句柄 定义 */
TIM_HandleTypeDef g_time_handle;    /* 定时器句柄 */


void gtim_timx_int_init(uint16_t arr, uint16_t psc)
{
    GTIM_TIMX_INT_CLK_ENABLE();                         /* 使能TIMx时钟 */

    g_time_handle.Instance = GTIM_TIMX_INT;             /* 通用定时器x */
    g_time_handle.Init.Prescaler = psc;                 /* 预分频系数 */
    g_time_handle.Init.CounterMode = TIM_COUNTERMODE_UP;/* 递增计数模式 */  
    g_time_handle.Init.Period = arr;                    /* 自动装载值 */

    HAL_TIM_Base_Init(&g_time_handle);

    HAL_NVIC_SetPriority(GTIM_TIMX_INT_IRQn, 1, 3);     /* 设置中断优先级，抢占优先级1，子优先级3 */
    HAL_NVIC_EnableIRQ(GTIM_TIMX_INT_IRQn);             /* 开启ITMx中断 */

    HAL_TIM_Base_Start_IT(&g_time_handle);              /* 使能定时器x和定时器x更新中断 */
}


/* 定时器中断服务函数 */

/* 
    可以看到这里并没有使用HAL库的定时器公共处理函数来处理中断部分的代码，而是通过自行判断中断标志位的方式来处理。
    只不过获取标志位的方式还是使用HAL库的函数宏__HAL_TIM_GET_FLAG()，通过__HAL_TIM_GET_FLAG()获取中断标志位并判断是否进入了中断，然后处理中断程序，
    最后将中断标志位清零，这样就完成了一次对中断的处理。
 */
void GTIM_TIMX_INT_IRQHandler(void)
{
    /* 以下代码没有使用定时器HAL库共用处理函数来处理，而是直接通过判断中断标志位的方式 */
    if (__HAL_TIM_GET_FLAG(&g_time_handle, TIM_FLAG_UPDATE) != RESET)
    {
        LED1_TOGGLE();
        __HAL_TIM_CLEAR_IT(&g_time_handle, TIM_IT_UPDATE);  /* 清除定时器溢出中断标志位 */
    }
    
}

