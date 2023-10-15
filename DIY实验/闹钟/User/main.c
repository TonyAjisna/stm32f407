#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/LCD/lcd.h"
#include "./BSP/BEEP/beep.h"
#include "./BSP/KEY/key.h"
#include "./BSP/RTC/rtc.h"

/* 自定义闹钟
    需求：  暂时不能使用者设置闹钟时间，MCU屏会显示当前时间和设定闹钟时间和距离响铃时间；
            绿色呼吸灯在非响铃期间0.5s翻转提示系统运行，响铃期间红色呼吸灯0.2s翻转；
            到达设定闹钟时间蜂鸣器会响起，持续60s，不关闭会在每隔两分钟响一次；
            KEY0关闭闹钟，KEY1延时5分钟响铃，WK_UP直接废弃闹钟，KEY_3启用闹钟；

    模块：
            KEY0、KEY1、WK_UP、LED0、LED1、BEEP、RTC实时时钟、LCD；
    
    思路：
            配置好RTC实时时钟，初始化各类模块，实现模块之间的逻辑关系；
            重点在于时间的格式设置和时间差；
            
*/

int main(void)
{
    HAL_Init();                                 /* 初始化HAL库 */
    sys_stm32_clock_init(336, 8, 2, 7);         /* 设置时钟,168Mhz */
    delay_init(168);                            /* 延时初始化 */
    led_init();                                 /* 初始化LED */
    lcd_init();                                 /* 初始化LCD */
    beep_init();                                /* 初始化蜂鸣器 */
    rtc_init();                                 /* 初始化rtc实时时钟 */
    key_init();                                 /* 初始化按键 */

    while(1)
    {
        
        /* 1、在MCU屏打印出实时日期和时间 */

        /* 2、打印出闹钟时间 */

        /* 3、打印出距离响铃时间 */

        /* 4、状态呼吸灯设置 */

        /* 5、蜂鸣器设置 */

        /* 6、按键扫描(终止、废弃、启用闹钟) */

        /* 7、响铃设置 */

        /* 8、延期事件设置 */

    }
}

