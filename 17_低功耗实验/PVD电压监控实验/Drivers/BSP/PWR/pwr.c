#include "./BSP/PWR/pwr.h"
#include "./BSP/LED/led.h"
#include "./BSP/LCD/lcd.h"
#include "./BSP/RTC/rtc.h"


/* 初始化PVD电压检测器 */
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


/* PVD中断服务 */
void PVD_IRQHandler(void)
{
    HAL_PWR_PVD_IRQHandler();
}

/* PVD/AVD中断服务回调函数 */
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

