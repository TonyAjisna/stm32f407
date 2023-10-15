#ifndef __RNG_H
#define __RNG_H

#include "./SYSTEM/sys/sys.h"


uint8_t rng_init(void);         /* RNG初始化 */
uint32_t rng_get_random_num(void);  /* 得到随机数 */
int rng_get_random_range(int min, int max);  /* 得到属于某个范围内的随机数 */


#endif
