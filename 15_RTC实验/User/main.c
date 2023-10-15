#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/LCD/lcd.h"
#include "./USMART/usmart.h"
#include "./BSP/RTC/rtc.h"

/* 
    RTC���ò��裺
        ʹ�ܵ�Դʱ�ӣ���ʹ��RTC��RTC�󱸼Ĵ���д����
        �����ⲿ��������LSE��ѡ��RTCʱ�Ӳ�ʹ��
        ��ʼ��RTC, ����RTC�ķ�Ƶ���Լ�����RTC����
        ����RTCʱ��
        ����RTC������
*/

int main(void)
{
    uint8_t hour, min, sec, ampm;
    uint8_t year, month, date, week;
    uint8_t tbuf[40];
    uint8_t t = 0;
    
    HAL_Init();                             /* ��ʼ��HAL�� */
    sys_stm32_clock_init(336, 8, 2, 7);     /* ����ʱ��,168Mhz */
    delay_init(168);                        /* ��ʱ��ʼ�� */
    usart_init(115200);                     /* ���ڳ�ʼ��Ϊ115200 */
    usmart_dev.init(84);                    /* ��ʼ��USMART */
    led_init();                             /* ��ʼ��LED */
    lcd_init();                             /* ��ʼ��LCD */
    rtc_init();                             /* ��ʼ��RTC */
    rtc_set_wakeup(RTC_WAKEUPCLOCK_CK_SPRE_16BITS, 0);  /* ����WAKE UP�ж�,1�����ж�һ�� */

    lcd_show_string(30, 50, 200, 16, 16, "STM32", RED);
    lcd_show_string(30, 70, 200, 16, 16, "RTC TEST", RED);
    lcd_show_string(30, 90, 200, 16, 16, "ATOM@ALIENTEK", RED);

    while (1)
    {
        t++;

        if ((t % 10) == 0)  /* ÿ100ms����һ����ʾ���� */
        {
            rtc_get_time(&hour, &min, &sec, &ampm);
            sprintf((char *)tbuf, "Time:%02d:%02d:%02d", hour, min, sec);
            lcd_show_string(30, 130, 210, 16, 16, (char*)tbuf, RED);
            rtc_get_date(&year, &month, &date, &week);
            sprintf((char *)tbuf, "Date:20%02d-%02d-%02d", year, month, date);
            lcd_show_string(30, 150, 210, 16, 16, (char*)tbuf, RED);
            sprintf((char *)tbuf, "Week:%d", week);
            lcd_show_string(30, 170, 210, 16, 16, (char*)tbuf, RED);
        }

        if ((t % 20) == 0)
        {
            LED0_TOGGLE();  /* ÿ200ms,��תһ��LED0 */
        }

        delay_ms(10);
    }
}
