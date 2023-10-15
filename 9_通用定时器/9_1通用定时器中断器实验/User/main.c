#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/TIMER/gtim.h"
/* 
    LED0����ָʾ�����������У�200ms��תһ�Ρ�LED1�ڶ�ʱ���ж��з�ת��500ms�����ж�һ��

    ԭ����ʱ�����ڿ������ڲ���Դ��ֻ��Ҫ������úü����������У�
          ͨ��LED1��ָʾ��ʱ�������жϵ�Ƶ�ʣ�LED0��ָʾ���������״̬

    ������ƣ�main�����в�û�ж�LED1�Ĳ��������ǰѶ�LED1�Ĳ����ŵ���ʱ�����ж��н��д���
 */

int main(void)
{    
    HAL_Init();                             /* ��ʼ��HAL�� */
    sys_stm32_clock_init(336, 8, 2, 7);     /* ����ʱ��,168Mhz */
    delay_init(168);                        /* ��ʱ��ʼ�� */
    usart_init(115200);                     /* ���ڳ�ʼ��Ϊ115200 */
    led_init();                             /* ��ʼ��LED */
    gtim_timx_int_init(5000 - 1, 8400 - 1); /* 84 000 000 / 84 00 = 10 000 10Khz�ļ���Ƶ�ʣ�����5K��Ϊ500ms */
    
    while(1)
    {
        LED0_TOGGLE();                      /* LED0(���) ��ת */
        delay_ms(200);
    }
}

