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
void GTIM_TIMX_INT_IRQHandler(void)
{
    /* 以下代码没有使用定时器HAL库共用处理函数来处理，而是直接通过判断中断标志位的方式 */
    if (__HAL_TIM_GET_FLAG(&g_time_handle, TIM_FLAG_UPDATE) != RESET)
    {
        LED1_TOGGLE();
        __HAL_TIM_CLEAR_IT(&g_time_handle, TIM_IT_UPDATE);  /* 清除定时器溢出中断标志位 */
    }
    
}

TIM_HandleTypeDef g_timx_pwm_chy_handle;                    /* 定时器句柄 */

/**
 * @brief       通用定时器TIMX 通道Y PWM输出 初始化函数（使用PWM模式1）
 * @note
 *              通用定时器的时钟来自APB1,当PPRE1 ≥ 2分频的时候
 *              通用定时器的时钟为APB1时钟的2倍, 而APB1为42M, 所以定时器时钟 = 84Mhz
 *              定时器溢出时间计算方法: Tout = ((arr + 1) * (psc + 1)) / Ft us.
 *              Ft = 定时器工作频率,单位:Mhz
 *
 * @param       arr: 自动重装值
 * @param       psc: 预分频系数
 * @retval      无
 */
void gtim_timx_pwm_chy_init(uint16_t arr, uint16_t psc)
{
    TIM_OC_InitTypeDef timx_oc_pwm_chy = {0};                       /* 定时器输出句柄 */

    g_timx_pwm_chy_handle.Instance = GTIM_TIMX_PWM;                 /* 定时器x */
    g_timx_pwm_chy_handle.Init.Prescaler = psc;                     /* 预分频系数 */
    g_timx_pwm_chy_handle.Init.CounterMode = TIM_COUNTERMODE_UP;    /* 计数器模式--递增 */
    g_timx_pwm_chy_handle.Init.Period = arr;                        /* 自动重装载值 */
    HAL_TIM_PWM_Init(&g_timx_pwm_chy_handle);                       /* 初始化PWM */

    timx_oc_pwm_chy.OCMode = TIM_OCMODE_PWM1;                       /* 模式选择PWM1 */
    timx_oc_pwm_chy.Pulse = arr / 2;                                /* 设置比较值，此值用来确定占空比 */

    timx_oc_pwm_chy.OCPolarity = TIM_OCPOLARITY_LOW;                                        /* 输出比较极性为低 */
    HAL_TIM_PWM_ConfigChannel(&g_timx_pwm_chy_handle, &timx_oc_pwm_chy, GTIM_TIMX_PWM_CHY); /* 配置TIMx通道y */
    HAL_TIM_PWM_Start(&g_timx_pwm_chy_handle, GTIM_TIMX_PWM_CHY);                           /* 开启对应PWM通道 */
}


/* 
    定时器底层驱动，时钟使能，引脚配置
    此函数会被HAL_TIM_PWM_Init()调用
*/
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == GTIM_TIMX_PWM)
    {
        GPIO_InitTypeDef gpio_init_struct;
        GTIM_TIMX_PWM_CHY_GPIO_CLK_ENABLE();                            /* 开启通道y的CPIO时钟 */
        GTIM_TIMX_PWM_CHY_CLK_ENABLE();                                 /* 使能定时器时钟 */

        gpio_init_struct.Pin = GTIM_TIMX_PWM_CHY_GPIO_PIN;              /* 通道y的CPIO口 */
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;                        /* 复用推完输出 */
        gpio_init_struct.Pull = GPIO_PULLUP;                            /* 上拉 */
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;                  /* 高速 */
        gpio_init_struct.Alternate = GTIM_TIMX_PWM_CHY_GPIO_AF;         /* IO口REMAP设置, 是否必要查看头文件配置的说明! */
        HAL_GPIO_Init(GTIM_TIMX_PWM_CHY_GPIO_PORT, &gpio_init_struct);
    }
}


/* -----------------------------------以下是通用定时器输入捕获实验程序-------------------------------------------- */

TIM_HandleTypeDef g_time_cap_chy_handle;    /* 定时器句柄 */

/* 
    通用定时器TIMX 通道Y 输入捕获 初始化函数
*/
void gtim_timx_cap_chy_init(uint32_t arr, uint16_t psc)
{
    TIM_IC_InitTypeDef timx_ic_cap_chy = {0};

    g_time_cap_chy_handle.Instance = GTIM_TIMX_CAP;                     /* 定时器5 */
    g_time_cap_chy_handle.Init.Prescaler = psc;                         /* 预分频系数 */
    g_time_cap_chy_handle.Init.CounterMode = TIM_COUNTERMODE_UP;        /* 向上计数模式 */
    g_time_cap_chy_handle.Init.Period = arr;                            /* 自动重转载值 */

    HAL_TIM_IC_Init(&g_time_cap_chy_handle);                            /* 初始化定时器 */

    timx_ic_cap_chy.ICPolarity = TIM_ICPOLARITY_RISING;                 /* 上升沿捕获 */
    timx_ic_cap_chy.ICSelection = TIM_ICSELECTION_DIRECTTI;             /* 映射到TI1上 */
    timx_ic_cap_chy.ICPrescaler = TIM_ICPSC_DIV1;                       /* 配置输入分频，不分频 */
    HAL_TIM_IC_ConfigChannel(&g_time_cap_chy_handle, &timx_ic_cap_chy, GTIM_TIMX_CAP_CHY);  /* 配置TIM5通道1 */

    __HAL_TIM_ENABLE_IT(&g_time_cap_chy_handle, TIM_IT_UPDATE);         /* 使能更新中断 */  
    HAL_TIM_IC_Start_IT(&g_time_cap_chy_handle, GTIM_TIMX_CAP_CHY);     /* 开始捕获TIM5的通道1 */
}