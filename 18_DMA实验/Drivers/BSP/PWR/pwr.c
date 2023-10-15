#include "./BSP/PWR/pwr.h"
#include "./BSP/LED/led.h"
#include "./BSP/LCD/lcd.h"
#include "./BSP/RTC/rtc.h"

/* 初始化PVD电压监视器 */
void pwr_pvd_init(uint32_t pls)
{
    PWR_PVDTypeDef pvd_handle = {0};

    __HAL_RCC_PWR_CLK_ENABLE();

    pvd_handle.PVDLevel = pls;
    pvd_handle.Mode = PWR_PVD_MODE_IT_RISING_FALLING;
    HAL_PWR_ConfigPVD(&pvd_handle);

    HAL_NVIC_SetPriority(PVD_IRQn, 3, 3);       /* 抢占优先级3，子优先级3 */
    HAL_NVIC_EnableIRQ(PVD_IRQn);
    HAL_PWR_EnablePVD();
}

/* PVD中断服务函数 */
void PVD_IRQHandler(void)
{
    HAL_PWR_PVD_IRQHandler();   /* 直接调用中断回调函数 */
}

/* PVD/AVD终中断服务回调函数 */
void HAL_PWR_PVDCallback(void)
{
    if (__HAL_PWR_GET_FLAG(PWR_FLAG_PVDO))   /* 电压比PLS所选电压还低 */
    {
        lcd_show_string(30, 130, 200, 16, 16, "PVD Low Voltage!", RED); /* LCD显示电压低 */
        LED1(0);    /* 点亮绿灯, 表明电压低了 */
    }
    else
    {
        lcd_show_string(30, 130, 200, 16, 16, "PVD Voltage OK! ", BLUE);/* LCD显示电压正常 */
        LED1(1);    /* 灭掉绿灯 */
    }
}

/* *************************睡眠模式实验程序******************************** */

/* 低功耗模式下的按键初始化（用于唤醒睡眠模式/停止模式/待机模式） */
void pwr_wkup_key_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;

    PWR_WKUP_GPIO_CLK_ENABLE();     /* WKUP时钟使能 */

    gpio_init_struct.Pin = PWR_WKUP_GPIO_PIN;               /* WK_UP引脚 */
    gpio_init_struct.Mode = GPIO_MODE_IT_RISING;            /* 中断上升沿 */
    gpio_init_struct.Pull = GPIO_PULLDOWN;                  /* 设置下拉模式 */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;          /* 高速 */
    HAL_GPIO_Init(PWR_WKUP_GPIO_PORT, &gpio_init_struct);   /* WK_UP引脚初始化 */

    HAL_NVIC_SetPriority(PWR_WKUP_INT_IRQn, 2, 2);            /* 抢占优先级2，子优先级2 */
    HAL_NVIC_EnableIRQ(PWR_WKUP_INT_IRQn); 
}


/* WK_UP按键 外部中断程序 */
void PWR_WKUP_INT_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(PWR_WKUP_GPIO_PIN);
}


/* 进入CPU睡眠模式 */
void pwr_enter_sleep(void)
{
    HAL_SuspendTick();              /* 暂停滴答时钟中断唤醒 */

    HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI); /* 执行WFI指令, 进入待机模式 */
}


/* 外部中断回调函数 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == PWR_WKUP_GPIO_PIN)
    {
        /* HAL_GPIO_EXTI_IRQHandler()函数已经为我们清除了中断标志位，所以我们进了回调函数可以不做任何事 */
    }
}