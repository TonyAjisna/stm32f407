#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/LCD/lcd.h"
#include "./BSP/KEY/key.h"
#include "./BSP/RNG/rng.h"
#include "./USMART/usmart.h"

/* 
    PVD��ѹ������ò��裺
        ����PVD��ʹ��PVDʱ�ӣ���������ѹ����ʹ���жϴ�����ʽ��
        ʹ��PVD��⣬����PVD/AVD�ж����ȼ�������PVD�ж�
        ��д�жϷ�����
*/

int main(void)
{
    uint8_t t = 0;

    HAL_Init();                             /* ��ʼ��HAL�� */
    sys_stm32_clock_init(336, 8, 2, 7);     /* ����ʱ��,168Mhz */
    delay_init(168);                        /* ��ʱ��ʼ�� */
    usart_init(115200);                     /* ���ڳ�ʼ��Ϊ115200 */
    usmart_dev.init(84);                    /* ��ʼ��USMART */
    led_init();                             /* ��ʼ��LED */
    lcd_init();                             /* ��ʼ��LCD */
    
    lcd_show_string(30, 50, 200, 16, 16, "STM32", RED);
    lcd_show_string(30, 70, 200, 16, 16, "PVD TEST", RED);
    lcd_show_string(30, 90, 200, 16, 16, "ATOM@ALIENTEK", RED);
    /* Ĭ�� LCD ��ʾ��ѹ���� */
    lcd_show_string(30, 130, 200, 16, 16, "PVD Voltage OK! ", BLUE);
    while (1)
    {
        if ((t % 20) == 0)
            {
                LED0_TOGGLE(); /* ÿ 200ms,��תһ�� LED0 */
            }
        delay_ms(10);
        t++;
    }
}


