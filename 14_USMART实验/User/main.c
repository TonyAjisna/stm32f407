#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/LCD/lcd.h"
#include "./USMART/usmart.h"


/* LED״̬���ú��� */
void led_set(uint8_t sta)
{
    LED1(sta);
}

/* �����������ò��Ժ��� */
void test_fun(void(*ledset)(uint8_t), uint8_t sta)
{
    ledset(sta);
}


int main(void)
{
    HAL_Init();
    sys_stm32_clock_init(336, 8, 2, 7);
    delay_init(168);
    usart_init(115200);
    usmart_dev.init(84);
    led_init();
    lcd_init();

    lcd_show_string(30, 50, 200, 16, 16, "STM32", RED);
    lcd_show_string(30, 70, 200, 16, 16, "USMART TEST", RED);
    lcd_show_string(30, 90, 200, 16, 16, "ATOM@ALIENTEK", RED);

    while (1)
    {
        LED0_TOGGLE();  /* �����˸ */
        delay_ms(1000);
    }
    
}

