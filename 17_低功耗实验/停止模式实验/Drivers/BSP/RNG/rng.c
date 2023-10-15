#include "./BSP/RNG/rng.h"
#include "./SYSTEM/delay/delay.h"

RNG_HandleTypeDef g_rng_handle;     /* RNG��� */

/* ��ʼ��RNG��0�ɹ���1ʧ�� */
uint8_t rng_init(void)
{
    uint16_t retry = 0;

    g_rng_handle.Instance = RNG;
    HAL_RNG_DeInit(&g_rng_handle);
    HAL_RNG_Init(&g_rng_handle);    /* ��ʼ��RNG */

    while (__HAL_RNG_GET_FLAG(&g_rng_handle, RNG_FLAG_DRDY) == RESET && retry < 10000)      /* �ȴ�RNG׼������ */
    {
        retry++;
        delay_us(10);
    }
    
    if (retry >= 10000)
    {
        return 1;       /* ��������������������� */
    }
    return 0;
}

/* 
    RNG�ײ�������ʱ��Դ���ú�ʹ��
    �˺����ᱻHAL_RNG_Init()����
*/
void HAL_RNG_MspInit(RNG_HandleTypeDef *hrng)
{
    __HAL_RCC_RNG_CLK_ENABLE();     /* ʹ��ʱ�� */
}

/* �õ������ */
uint32_t rng_get_random_num(void)
{
    uint32_t randomnum;
    HAL_RNG_GenerateRandomNumber(&g_rng_handle, &randomnum);
    return randomnum;
}

/* �õ�ĳ����Χ�ڵ������ */
int rng_get_random_range(int min, int max)
{
    uint32_t randomnum;
    HAL_RNG_GenerateRandomNumber(&g_rng_handle, &randomnum);
    return randomnum%(max-min+1)+min;
}

