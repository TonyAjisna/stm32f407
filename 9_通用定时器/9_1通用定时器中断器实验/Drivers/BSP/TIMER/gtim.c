#include "./BSP/TIMER/gtim.h"
#include "./BSP/LED/led.h"

/* ��ʱ�����þ�� ���� */
TIM_HandleTypeDef g_time_handle;    /* ��ʱ����� */


void gtim_timx_int_init(uint16_t arr, uint16_t psc)
{
    GTIM_TIMX_INT_CLK_ENABLE();                         /* ʹ��TIMxʱ�� */

    g_time_handle.Instance = GTIM_TIMX_INT;             /* ͨ�ö�ʱ��x */
    g_time_handle.Init.Prescaler = psc;                 /* Ԥ��Ƶϵ�� */
    g_time_handle.Init.CounterMode = TIM_COUNTERMODE_UP;/* ��������ģʽ */  
    g_time_handle.Init.Period = arr;                    /* �Զ�װ��ֵ */

    HAL_TIM_Base_Init(&g_time_handle);

    HAL_NVIC_SetPriority(GTIM_TIMX_INT_IRQn, 1, 3);     /* �����ж����ȼ�����ռ���ȼ�1�������ȼ�3 */
    HAL_NVIC_EnableIRQ(GTIM_TIMX_INT_IRQn);             /* ����ITMx�ж� */

    HAL_TIM_Base_Start_IT(&g_time_handle);              /* ʹ�ܶ�ʱ��x�Ͷ�ʱ��x�����ж� */
}


/* ��ʱ���жϷ����� */

/* 
    ���Կ������ﲢû��ʹ��HAL��Ķ�ʱ�������������������жϲ��ֵĴ��룬����ͨ�������ж��жϱ�־λ�ķ�ʽ������
    ֻ������ȡ��־λ�ķ�ʽ����ʹ��HAL��ĺ�����__HAL_TIM_GET_FLAG()��ͨ��__HAL_TIM_GET_FLAG()��ȡ�жϱ�־λ���ж��Ƿ�������жϣ�Ȼ�����жϳ���
    ����жϱ�־λ���㣬�����������һ�ζ��жϵĴ���
 */
void GTIM_TIMX_INT_IRQHandler(void)
{
    /* ���´���û��ʹ�ö�ʱ��HAL�⹲�ô���������������ֱ��ͨ���ж��жϱ�־λ�ķ�ʽ */
    if (__HAL_TIM_GET_FLAG(&g_time_handle, TIM_FLAG_UPDATE) != RESET)
    {
        LED1_TOGGLE();
        __HAL_TIM_CLEAR_IT(&g_time_handle, TIM_IT_UPDATE);  /* �����ʱ������жϱ�־λ */
    }
    
}

