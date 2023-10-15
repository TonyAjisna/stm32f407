#include "./BSP/PWR/pwr.h"
#include "./BSP/LED/led.h"
#include "./BSP/LCD/lcd.h"
#include "./BSP/RTC/rtc.h"


/* ��ʼ��PVD��ѹ����� */
void pwr_pvd_init(uint32_t pls)
{
    PWR_PVDTypeDef pvd_handle = {0};

    __HAL_RCC_PWR_CLK_ENABLE();

    pvd_handle.PVDLevel = pls;
    pvd_handle.Mode = PWR_PVD_MODE_IT_RISING_FALLING;
    HAL_PWR_ConfigPVD(&pvd_handle);

    HAL_NVIC_SetPriority(PVD_IRQn, 3, 3);       /* ��ռ���ȼ�3�������ȼ�3 */
    HAL_NVIC_EnableIRQ(PVD_IRQn);
    HAL_PWR_EnablePVD();
}


/* PVD�жϷ��� */
void PVD_IRQHandler(void)
{
    HAL_PWR_PVD_IRQHandler();
}

/* PVD/AVD�жϷ���ص����� */
void HAL_PWR_PVDCallback(void)
{
    if (__HAL_PWR_GET_FLAG(PWR_FLAG_PVDO))   /* ��ѹ��PLS��ѡ��ѹ���� */
    {
        lcd_show_string(30, 130, 200, 16, 16, "PVD Low Voltage!", RED); /* LCD��ʾ��ѹ�� */
        LED1(0);    /* �����̵�, ������ѹ���� */
    }
    else
    {
        lcd_show_string(30, 130, 200, 16, 16, "PVD Voltage OK! ", BLUE);/* LCD��ʾ��ѹ���� */
        LED1(1);    /* ����̵� */
    }    
}

