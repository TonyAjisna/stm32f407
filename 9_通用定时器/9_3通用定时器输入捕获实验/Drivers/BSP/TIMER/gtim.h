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


/* --------------------------------���������벶����---------------------------------------------------- */

/* 
    ��������벶��ʹ�ö�ʱ��TIM5_CH1������WK_UP����������
    Ĭ�����TIM2~5
    ע��: ͨ���޸��⼸���궨��,����֧��TIM1~TIM8����һ����ʱ��,����һ��IO�������벶��
         �ر�Ҫע��:Ĭ���õ�PA0,���õ�����������!���������IO,��Ӧ����������ʽҲ�ø�!
 */
#define GTIM_TIMX_CAP_CHY_GPIO_PORT         GPIO_A
#define GTIM_TIMX_CAP_CHY_GPIO_PIN          GPIO_PIN_0
#define GTIM_TIMX_CAP_CHY_GPIO_CLK_ENABLE() do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0) /* PA��ʱ��ʹ�� */
#define GTIM_TIMX_CAP_CHY_GPIO_AF           GPIO_AF2_TIM5                               /* AF����ѡ�� */

#define GTIM_TIMX_CAP                       TIM5 
#define GTIM_TIMX_CAP_IRQn                  TIM5_IRQn
#define GTIM_TIMX_CAP_IRQnHandler           TIM5_IRQHandler
#define GTIM_TIMX_CAP_CHY                   TIM_CHANNEL_1                               /* ͨ��Y�� 1<= Y <=4 */
#define GTIM_TIMX_CAP_CHY_CCRX              TIM5->CCR1                                  /* ͨ��Y������ȽϼĴ��� */
#define GTIM_TIMX_CAP_CHY_CLK_ENABLE()      do{ __HAL_RCC_TIM5_CLK_ENABLE(); }while(0); /* TIM5ʱ��ʹ�� */

/* --------------------------------------------------------------------------------------------- */

void gtim_timx_int_init(uint16_t arr, uint16_t psc);        /* ͨ�ö�ʱ�� ��ʱ�жϳ�ʼ������ */
void gtim_timx_pwm_chy_init(uint16_t arr, uint16_t psc);    /* ͨ�ö�ʱ�� PWM��ʼ������ */
void gtim_timx_cap_chy_init(uint32_t arr, uint16_t psc);    /* ͨ�ö�ʱ�� ���벶���ʼ������ */

#endif
