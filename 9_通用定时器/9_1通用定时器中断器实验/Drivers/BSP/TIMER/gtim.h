#ifndef __GTIM_H
#define __GTIM_H

#include "./SYSTEM/sys/sys.h"


/* ͨ�ö�ʱ������ */

/* ͨ���޸���4���궨�壬����֧��TIM1~8����һ����ʱ�� */

#define GTIM_TIMX_INT                   TIM3
#define GTIM_TIMX_INT_IRQn              TIM3_IRQn
#define GTIM_TIMX_INT_IRQHandler        TIM3_IRQHandler
#define GTIM_TIMX_INT_CLK_ENABLE()      do{ __HAL_RCC_TIM3_CLK_ENABLE(); }while(0)  /* TIM3 ʱ��ʹ�� */


void gtim_timx_int_init(uint16_t arr, uint16_t psc);        /* ͨ�ö�ʱ�� ��ʱ�жϳ�ʼ������ */


#endif
