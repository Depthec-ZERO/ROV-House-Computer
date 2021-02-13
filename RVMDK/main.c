#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "lcd.h"
#include "malloc.h"  
#include "MMC_SD.h" 
#include "ff.h"  
#include "exfuns.h"
#include "fontupd.h"
#include "text.h"	
#include "pstwo.h"
#include "Tasks.h"
#include "Timer3.h"



int main(void)
{
	
	BSP_Int();	//µ×²ãÇı¶¯³õÊ¼»¯

	while(1)
	{
		
		
		if(Count_100ms>=100)
		{	
			Count_100ms = 0;
			Task_10HZ();
		}
		
				
		
 	
		
		

		
	}
	
		
}
