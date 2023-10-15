#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/LCD/lcd.h"
#include "./BSP/KEY/key.h"
#include "./BSP/RNG/rng.h"
#include "./USMART/usmart.h"

/* 
    PVD电压监控配置步骤：
        配置PVD，使能PVD时钟：包括检测电压级别、使用中断触发方式等
        使能PVD检测，配置PVD/AVD中断优先级，开启PVD中断
        编写中断服务函数
*/

int main(void)
{
    uint8_t t = 0;

    HAL_Init();                             /* 初始化HAL库 */
    sys_stm32_clock_init(336, 8, 2, 7);     /* 设置时钟,168Mhz */
    delay_init(168);                        /* 延时初始化 */
    usart_init(115200);                     /* 串口初始化为115200 */
    usmart_dev.init(84);                    /* 初始化USMART */
    led_init();                             /* 初始化LED */
    lcd_init();                             /* 初始化LCD */
    
    lcd_show_string(30, 50, 200, 16, 16, "STM32", RED);
    lcd_show_string(30, 70, 200, 16, 16, "PVD TEST", RED);
    lcd_show_string(30, 90, 200, 16, 16, "ATOM@ALIENTEK", RED);
    /* 默认 LCD 显示电压正常 */
    lcd_show_string(30, 130, 200, 16, 16, "PVD Voltage OK! ", BLUE);
    while (1)
    {
        if ((t % 20) == 0)
            {
                LED0_TOGGLE(); /* 每 200ms,翻转一次 LED0 */
            }
        delay_ms(10);
        t++;
    }
}


