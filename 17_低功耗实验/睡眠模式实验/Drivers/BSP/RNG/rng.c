#include "./BSP/RNG/rng.h"
#include "./SYSTEM/delay/delay.h"

RNG_HandleTypeDef g_rng_handle;     /* RNG句柄 */

/* 初始化RNG，0成功，1失败 */
uint8_t rng_init(void)
{
    uint16_t retry = 0;

    g_rng_handle.Instance = RNG;
    HAL_RNG_DeInit(&g_rng_handle);
    HAL_RNG_Init(&g_rng_handle);    /* 初始化RNG */

    while (__HAL_RNG_GET_FLAG(&g_rng_handle, RNG_FLAG_DRDY) == RESET && retry < 10000)      /* 等待RNG准备就绪 */
    {
        retry++;
        delay_us(10);
    }
    
    if (retry >= 10000)
    {
        return 1;       /* 随机数产生器工作不正常 */
    }
    return 0;
}

/* 
    RNG底层驱动，时钟源设置和使能
    此函数会被HAL_RNG_Init()调用
*/
void HAL_RNG_MspInit(RNG_HandleTypeDef *hrng)
{
    __HAL_RCC_RNG_CLK_ENABLE();     /* 使能时钟 */
}

/* 得到随机数 */
uint32_t rng_get_random_num(void)
{
    uint32_t randomnum;
    HAL_RNG_GenerateRandomNumber(&g_rng_handle, &randomnum);
    return randomnum;
}

/* 得到某个范围内的随机数 */
int rng_get_random_range(int min, int max)
{
    uint32_t randomnum;
    HAL_RNG_GenerateRandomNumber(&g_rng_handle, &randomnum);
    return randomnum%(max-min+1)+min;
}

