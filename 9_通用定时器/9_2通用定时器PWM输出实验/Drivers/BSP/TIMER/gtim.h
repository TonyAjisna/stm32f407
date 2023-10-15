#ifndef __GTIM_H
#define __GTIM_H

#include "./SYSTEM/sys/sys.h"


/* ͨ�ö�ʱ������ */

/* ͨ���޸���4���궨�壬����֧��TIM1~8����һ����ʱ�� */

#define GTIM_TIMX_INT                       TIM3
#define GTIM_TIMX_INT_IRQn                  TIM3_IRQn
#define GTIM_TIMX_INT_IRQHandler            TIM3_IRQHandler
#define GTIM_TIMX_INT_CLK_ENABLE()          do{ __HAL_RCC_TIM3_CLK_ENABLE(); }while(0)   /* TIM3 ʱ��ʹ�� */


/* -------------------------------������ͨ�ö�ʱ��PWM���ʵ����غ궨��------------------------------------ */

/* 
    ���������PWM����LED0��RED��������
    Ĭ�������TIM2~5
    ע�⣺ͨ���޸ļ����궨�壬����֧��TIM1~8����һ����ʱ��������һ��IO�����PWM
 */
#define GTIM_TIMX_PWM_CHY_GPIO_PORT         GPIOF
#define GTIM_TIMX_PWM_CHY_GPIO_PIN          GPIO_PIN_9
#define GTIM_TIMX_PWM_CHY_GPIO_CLK_ENABLE() do{ __HAL_RCC_GPIOF_CLK_ENABLE(); }while(0)  /* PF��ʱ��ʹ�� */
#define GTIM_TIMX_PWM_CHY_GPIO_AF           GPIO_AF9_TIM14                             /* �˿ڸ��õ�TIM14 */

/* 
    TIMX REMAP����
    ��Ϊ����LED0������PF9�ϣ�����ͨ������TIM14�Ĳ�����ӳ�书�ܣ����ܽ�TIM14����CH1�����PF9��
*/

#define GTIM_TIMX_PWM                       TIM14                                        /* TIM14 */
#define GTIM_TIMX_PWM_CHY                   TIM_CHANNEL_1                                /* ͨ��Y,  1<= Y <=4 */
#define GTIM_TIMX_PWM_CHY_CCRX              TIM14->CCR1                                  /* ͨ��Y������ȽϼĴ��� */
#define GTIM_TIMX_PWM_CHY_CLK_ENABLE()      do{ __HAL_RCC_TIM14_CLK_ENABLE(); }while(0)  /* TIM14 ʱ��ʹ�� */

/* ------------------------------------------------------------------------------------------- */

void gtim_timx_int_init(uint16_t arr, uint16_t psc);        /* ͨ�ö�ʱ�� ��ʱ�жϳ�ʼ������ */
void gtim_timx_pwm_chy_init(uint16_t arr, uint16_t psc);    /* ͨ�ö�ʱ�� PWM��ʼ������ */


#endif
