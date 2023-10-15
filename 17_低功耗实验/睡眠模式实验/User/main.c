#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/LCD/lcd.h"
#include "./BSP/KEY/key.h"
#include "./BSP/PWR/pwr.h"

/* 
    ˯��ģʽ���ò��裺
        ���û���˯��ģʽ�ķ�ʽ������һ���ⲿ�жϹ��ܣ���WK_UP������Ϊ�жϴ���Դ
        ����CPU˯��ģʽ
        ͨ�����°��������ⲿ�жϻ���˯��ģʽ
*/

int main(void)
{
    uint8_t t = 0, key;
    
    HAL_Init();                             /* ��ʼ��HAL�� */
    sys_stm32_clock_init(336, 8, 2, 7);     /* ����ʱ��,168Mhz */
    delay_init(168);                        /* ��ʱ��ʼ�� */
    usart_init(115200);                     /* ���ڳ�ʼ��Ϊ115200 */
    led_init();                             /* ��ʼ��LED */
    lcd_init();                             /* ��ʼ��LCD */
    key_init();                             /* ��ʼ������ */
    pwr_wkup_key_init();                    /* ���Ѱ�����ʼ�� */
    
    lcd_show_string(30,  50, 200, 16, 16, "STM32", RED);
    lcd_show_string(30,  70, 200, 16, 16, "STANDBY TEST", RED);
    lcd_show_string(30,  90, 200, 16, 16, "ATOM@ALIENTEK", RED);
    lcd_show_string(30, 110, 200, 16, 16, "KEY0:Enter SLEEP MODE", RED);
    lcd_show_string(30, 130, 200, 16, 16, "KEY_UP:Exit SLEEP MODE", RED);


    while (1)
    {
        key = key_scan(0);

        if (key == KEY0_PRES)
        {
            LED1(0);            /* �����̵ƣ���ʾ����ֹͣģʽ */
            pwr_enter_sleep();  /* ����˯��ģʽ */
            HAL_ResumeTick();   /* �ָ��δ�ʱ�� */
            LED1(1);            /* �ر��̵ƣ���ʾ�˳�ֹͣģʽ */
        }

        if ((t % 20) == 0)
        {
            LED0_TOGGLE();      /* ÿ200ms��תһ�� */
        }

        delay_ms(10);       
        t++;       
    }
    
}


