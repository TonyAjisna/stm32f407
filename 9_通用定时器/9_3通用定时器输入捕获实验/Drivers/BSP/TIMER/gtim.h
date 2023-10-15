#ifndef __GTIM_H
#define __GTIM_H

#include "./SYSTEM/sys/sys.h"


/* 通用定时器定义 */

/* 通过修改这4个宏定义，可以支持TIM1~8任意一个定时器 */

#define GTIM_TIMX_INT                       TIM3
#define GTIM_TIMX_INT_IRQn                  TIM3_IRQn
#define GTIM_TIMX_INT_IRQHandler            TIM3_IRQHandler
#define GTIM_TIMX_INT_CLK_ENABLE()          do{ __HAL_RCC_TIM3_CLK_ENABLE(); }while(0)   /* TIM3 时钟使能 */


/* -------------------------------以下是通用定时器PWM输出实验相关宏定义------------------------------------ */

/* 
    这里输出的PWM控制LED0（RED）的亮度
    默认是针对TIM2~5
    注意：通过修改几个宏定义，可以支持TIM1~8任意一个定时器，任意一个IO口输出PWM
 */
#define GTIM_TIMX_PWM_CHY_GPIO_PORT         GPIOF
#define GTIM_TIMX_PWM_CHY_GPIO_PIN          GPIO_PIN_9
#define GTIM_TIMX_PWM_CHY_GPIO_CLK_ENABLE() do{ __HAL_RCC_GPIOF_CLK_ENABLE(); }while(0)  /* PF口时钟使能 */
#define GTIM_TIMX_PWM_CHY_GPIO_AF           GPIO_AF9_TIM14                             /* 端口复用到TIM14 */

/* 
    TIMX REMAP设置
    因为我们LED0连接在PF9上，必须通过开启TIM14的部分重映射功能，才能将TIM14——CH1输出到PF9上
*/

#define GTIM_TIMX_PWM                       TIM14                                        /* TIM14 */
#define GTIM_TIMX_PWM_CHY                   TIM_CHANNEL_1                                /* 通道Y,  1<= Y <=4 */
#define GTIM_TIMX_PWM_CHY_CCRX              TIM14->CCR1                                  /* 通道Y的输出比较寄存器 */
#define GTIM_TIMX_PWM_CHY_CLK_ENABLE()      do{ __HAL_RCC_TIM14_CLK_ENABLE(); }while(0)  /* TIM14 时钟使能 */

/* ------------------------------------------------------------------------------------------- */


/* --------------------------------以下是输入捕获定义---------------------------------------------------- */

/* 
    这里的输入捕获使用定时器TIM5_CH1，捕获WK_UP按键的输入
    默认针对TIM2~5
    注意: 通过修改这几个宏定义,可以支持TIM1~TIM8任意一个定时器,任意一个IO口做输入捕获
         特别要注意:默认用的PA0,设置的是下拉输入!如果改其他IO,对应的上下拉方式也得改!
 */
#define GTIM_TIMX_CAP_CHY_GPIO_PORT         GPIO_A
#define GTIM_TIMX_CAP_CHY_GPIO_PIN          GPIO_PIN_0
#define GTIM_TIMX_CAP_CHY_GPIO_CLK_ENABLE() do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0) /* PA口时钟使能 */
#define GTIM_TIMX_CAP_CHY_GPIO_AF           GPIO_AF2_TIM5                               /* AF功能选择 */

#define GTIM_TIMX_CAP                       TIM5 
#define GTIM_TIMX_CAP_IRQn                  TIM5_IRQn
#define GTIM_TIMX_CAP_IRQnHandler           TIM5_IRQHandler
#define GTIM_TIMX_CAP_CHY                   TIM_CHANNEL_1                               /* 通道Y， 1<= Y <=4 */
#define GTIM_TIMX_CAP_CHY_CCRX              TIM5->CCR1                                  /* 通道Y的输出比较寄存器 */
#define GTIM_TIMX_CAP_CHY_CLK_ENABLE()      do{ __HAL_RCC_TIM5_CLK_ENABLE(); }while(0); /* TIM5时钟使能 */

/* --------------------------------------------------------------------------------------------- */

void gtim_timx_int_init(uint16_t arr, uint16_t psc);        /* 通用定时器 定时中断初始化函数 */
void gtim_timx_pwm_chy_init(uint16_t arr, uint16_t psc);    /* 通用定时器 PWM初始化函数 */
void gtim_timx_cap_chy_init(uint32_t arr, uint16_t psc);    /* 通用定时器 输入捕获初始化函数 */

#endif
