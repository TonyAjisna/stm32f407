#include <REGX52.H>
#include "LCD1602.h"	
#include "Delay.h"		

int Result=0;

void main()
{
	LCD_Init();
	//LCD_ShowString(1,3,"Hello");
	
	while(1)
	{
				Result++;					//Result??
		Delay(1000);				//??1?
		LCD_ShowNum(1,1,Result,3);	//?LCD?1?1???Result,???3?

	}
}
