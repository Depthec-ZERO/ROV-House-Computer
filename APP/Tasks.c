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
#include "Timer3.h"
#include "Tasks.h"
#include "protocol.h"

uint8_t Bsp_Int_Ok = 0;

/******************************************************************************
函数原型：	void Nvic_Init(void)
功    能：	NVIC初始化
*******************************************************************************/ 
void Nvic_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	//NVIC_PriorityGroup 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//优先级分组
    //Timer3
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;//先占优先级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;//从占优先级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
	//串口1中断
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	
}


/******************************************************************************
函数原型：	void BSP_Int(void)
功    能：	硬件驱动初始化
*******************************************************************************/ 
void BSP_Int(void)
{
	
	Nvic_Init();//中断优先级初始化	
	delay_init();
	uart_init(115200);//串口1初始化：波特率115200，8位数据，1位停止位，禁用奇偶校验
	Timer3_Init(1000);//Timer3中断100HZ
	LCD_Init();			    //初始化液晶 												    
 	mem_init();				//初始化内存池	    
 	exfuns_init();			//为fatfs相关变量申请内存  
    f_mount(fs[0],"0:",1); 	//挂载SD卡 
 	f_mount(fs[1],"1:",1); 	//挂载FLASH.
	font_init();
	 
    PS2_Init();			 //驱动端口初始化
	PS2_SetInit();		 //配配置初始化,配置“红绿灯模式”，并选择是否可以修改
	                     //开启震动模式

	
	
	Bsp_Int_Ok = 1;
	
}

u8 receive_flag;
/******************************************************************************
函数原型：	void Task_10HZ(void)
功    能：	主循环中运行频率为10HZ任务
*******************************************************************************/ 
void Task_10HZ(void)
{
	
	
//	   pitch=3114;roll=3114;yaw=3114;测试用
	   //ROV数据显示 
	   POINT_COLOR=BLACK;       
	   Show_Str(82,35,200,24,"海参捕捞机器人",24,0);//82				    	 
//	   Show_Str(82,35,200,24,"星鳐水下观测机器人",16,0);				    	 
//	   Show_Str(10,70,200,16,"ROV姿态：",16,0);
	
       Show_Str(10,100,260,24,"俯仰角：    °",24,0);   //上下间距没留够，左右宽度260
	   LCD_ShowxNum(90,100,pitch/100,3,24,0); 
	   Show_Str(126,100,260,24,".",24,0);     
	   LCD_ShowxNum(131,100,pitch%100,2,24,0);
	   
	   Show_Str(10,125,260,24,"左右倾：    °",24,0);  
       LCD_ShowxNum(90,125,roll/100,  3,24,0); 
	   Show_Str(126,125,260,24,".",24,0);      
	   LCD_ShowxNum(131,125,roll%100,  2,24,0);
	   
       Show_Str(10,150,260,24,"航向角：    °",24,0);  
       LCD_ShowxNum(90,150,yaw/100,  3,24,0); 
	   Show_Str(126,150,260,24,".",24,0);     
	   LCD_ShowxNum(131,150,yaw%100,  2,24,0);
	
//	   POINT_COLOR=BLACK; 
	   Show_Str(10,65,260,24,"深度：    cm",24,0); 
	   LCD_ShowxNum(67,65,depth,  5,24,0);
	   
	   
//       LCD_ShowxNum(67,65,depth/100,  3,24,0);
//       Show_Str(104,65,200,24,".",24,0);
//	   if((depth%100)<10)
//		  LCD_ShowxNum(105,65,0,2,24,0);	   
//       LCD_ShowxNum(117,65,depth%100,  2,24,0);

	   
//	   POINT_COLOR=BLACK; 
      
//	   Show_Str(10,160,200,16,"电池电量：  %",16,0); 
//	   LCD_ShowxNum(78,160,battery,3,16,0);    
			   
       Send_Command();//发送ROV控制命令
	   Status_Get(); //得到ROV状态
	  receive_flag++;
	if(receive_flag>=10) 
	{		
		POINT_COLOR=RED; 
		Show_Str(70,190,200,24,"通讯中断！！！",24,0);
	    POINT_COLOR=BLACK; 
	}else{
	   
		Show_Str(70,190,200,24,"              ",24,0);

	    }
	
	
	
}













