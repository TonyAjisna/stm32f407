#include <REGX52.H>
#include <INTRINS.H>
#include "Delay.h"	//??Delay???
#include "Nixie.h"	//????????

void main()
{
	while(1)
	{
		Nixie(1,1);	//??????1????1
		Nixie(2,2);	//??????2????2
		Nixie(3,3);	//??????3????3
		Nixie(4,4);	//??????4????4
		Nixie(5,5);	//??????5????5
		Nixie(6,6);	//??????6????6
	}
}


/* -------------------------------------------
//??????
unsigned char NixieTable[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};

//????????
void Nixie(unsigned char Location,Number)
{
	switch(Location)		//????
	{
		case 1:P2_4=1;P2_3=1;P2_2=1;break;
		case 2:P2_4=1;P2_3=1;P2_2=0;break;
		case 3:P2_4=1;P2_3=0;P2_2=1;break;
		case 4:P2_4=1;P2_3=0;P2_2=0;break;
		case 5:P2_4=0;P2_3=1;P2_2=1;break;
		case 6:P2_4=0;P2_3=1;P2_2=0;break;
		case 7:P2_4=0;P2_3=0;P2_2=1;break;
		case 8:P2_4=0;P2_3=0;P2_2=0;break;
	}
	P0=NixieTable[Number];	//????
}

void main()
{
	Nixie(2,3);	//??????2????3
	while(1)
	{
		
	}
}
*/


/*--------------------------------
void Delay(unsigned int xms);

unsigned char LEDNum;

void main()
{
	P2=~0x01;				//????LED1??
	while(1)
	{
		if(P3_1==0)			//??K1????
		{
			Delay(20);
			while(P3_1==0);
			Delay(20);
			
			LEDNum++;		//LEDNum??
			if(LEDNum>=8)	//??LEDNum????
				LEDNum=0;
			P2=~(0x01<<LEDNum);	//LED??LEDNum???
		}
		if(P3_0==0)			//??K2????
		{
			Delay(20);
			while(P3_0==0);
			Delay(20);
			
			if(LEDNum==0)	//LEDNum??0???7
				LEDNum=7;
			else			//LEDNum???0,??
				LEDNum--;
			P2=~(0x01<<LEDNum);	//LED??LEDNum???
		}
	}
}

void Delay(unsigned int xms)
{
	unsigned char i, j;
	while(xms--)
	{
		i = 2;
		j = 199;
		do
		{
			while (--j);
		} while (--i);
	}
}
*/

/* -------------------------------------------
void Delay(unsigned int xms)
{
	unsigned char i, j;
	while(xms)
	{
		i = 2;
		j = 199;
		do
		{
			while (--j);
		} while (--i);
		xms--;
	}
}

void main()
{
	while(1)
	{
		if(P3_1==0)			//??K1????
		{
			Delay(20);		//????
			while(P3_1==0);	//????
			Delay(20);		//????
			
			P2_0=~P2_0;		//LED1??
		}
	}
}
*/

//--------------------------------
/*
void main()
{
	

	
	while(1){
		
		if(P3_1==0||P3_0==0){
		P2_0=0;  
				
		}
		else{
			P2_0=1;
		
		
	
      }
		
		}

}
*/


/*LED-----------------------------------*/
/*
void Delay1ms(unsigned int msNum);

void main()
{

	unsigned int msNum1=50;
	
	while(1){
		P2=0xFE; //1111 1110
		Delay1ms(msNum1);
		P2=0xFD; //1111 1101
		Delay1ms(msNum1);
		P2=0xFB; //1111 1011
		Delay1ms(msNum1);
		P2=0xF7; //1111 0111
		Delay1ms(msNum1);
		P2=0xEF; //1110 1111
		Delay1ms(msNum1);
		P2=0xDF; //1101 1111
		Delay1ms(msNum1);
		P2=0xBF; //1011 1111
		Delay1ms(msNum1);
		P2=0x7F; //0111 1111
		Delay1ms(msNum1);
	}

}



void Delay1ms(unsigned int msNum)		//@11.0592MHz
{
	unsigned char i, j;
	
	while(msNum){
		
		_nop_();
	i = 2;
	j = 199;
	do
	{
		while (--j);
	} while (--i);
	
	msNum--;

		
	}

}
*/

