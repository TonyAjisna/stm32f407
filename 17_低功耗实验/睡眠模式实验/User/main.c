#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/LCD/lcd.h"
#include "./BSP/KEY/key.h"
#include "./BSP/PWR/pwr.h"

/* 
    睡眠模式配置步骤：
        配置唤醒睡眠模式的方式：配置一个外部中断功能，用WK_UP按键作为中断触发源
        进入CPU睡眠模式
        通过按下按键触发外部中断唤醒睡眠模式
*/

int main(void)
{
    uint8_t t = 0, key;
    
    HAL_Init();                             /* 初始化HAL库 */
    sys_stm32_clock_init(336, 8, 2, 7);     /* 设置时钟,168Mhz */
    delay_init(168);                        /* 延时初始化 */
    usart_init(115200);                     /* 串口初始化为115200 */
    led_init();                             /* 初始化LED */
    lcd_init();                             /* 初始化LCD */
    key_init();                             /* 初始化按键 */
    pwr_wkup_key_init();                    /* 唤醒按键初始化 */
    
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
            LED1(0);            /* 点亮绿灯，提示进入停止模式 */
            pwr_enter_sleep();  /* 进入睡眠模式 */
            HAL_ResumeTick();   /* 恢复滴答时钟 */
            LED1(1);            /* 关闭绿灯，提示退出停止模式 */
        }

        if ((t % 20) == 0)
        {
            LED0_TOGGLE();      /* 每200ms翻转一次 */
        }

        delay_ms(10);       
        t++;       
    }
    
}


