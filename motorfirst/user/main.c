#include "stm32f10x.h"         //???  
#include "stm32f10x_gpio.h"  
#include "stm32f10x_rcc.h"  
#include "delay.h"  
#include "motor.h"
#include "remote.h"
#include "usart.h"	
#include "sys.h"	
u16 timer;    
u8 flag;
u32 left_numb;
u32 right_numb;
u32 left_speed;
u32 right_speed;

#define INT0 PAin(13)                  //PA13
#define INT1 PAin(15)                  //PA15
#define INT2 PAin(0)	                 //PA0 
#define EXTI0_IRQChannel             ((u8)0x06)  /* EXTI Line0 Interrupt */
#define EXTI15_10_IRQChannel         ((u8)0x28)  /* External Line[15:10] Interrupts */
#define GPIO_A 0
#define FTIR   1                               //下降沿触发
#define RTIR   2                               //上升沿触发
void EXTIX_Init(void);
void process(void);                             
void Timerx_Init(u16 arr,u16 psc);            //定时器初始化函数  
void MY_NVIC_SetVectorTable(u32 NVIC_VectTab, u32 Offset);//设置偏移地址
void MY_NVIC_PriorityGroupConfig(u8 NVIC_Group);          //设置NVIC分组
void MY_NVIC_Init(u8 NVIC_PreemptionPriority,u8 NVIC_SubPriority,u8 NVIC_Channel,u8 NVIC_Group);//设置中断
void Ex_NVIC_Config(u8 GPIOx,u8 BITx,u8 TRIM);            //外部中断配置函数(只对GPIOA~G)  


int main(void)  
{  
	u8 key;
 	u8 *str=0;
    Motor_12_Config(); //298???????  
    delay_init();  //???????  

	delay_init();	    	 //延时函数初始化	  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	uart_init(115200);	 	//串口初始化为115200
  	
	Remote_Init();			//红外接收初始化	
  while(1)
	{
			Motor_go();
	}		
	while(1)
	{
		key=Remote_Scan();
		
		if(key)
		{	 
			 
			switch(key)
			{
				case 0:str="ERROR";break;			   
				case 162:str="POWER";break;	    
				case 98:                   //前进
					{
				     Motor_go();
				  };break;	    
				case 2:
				  {
				     Motor_stop();
				  };break;		 
					  
				case 194:                  //右转
          {
	           Motor_right();
						delay_ms(167);
						Motor_go();
          };break;	   
				case 34:                   //左转
				  {
				     Motor_left();
						delay_ms(167);
						Motor_go();
				  };break;		  
					  
				case 168:                  //后退
          { 
             Motor_back();
          };break;		   
				case 224: 
				{
					Motor_left();
						delay_ms(1000);
						Motor_go();
				};break;  
				case 144:
					{
					  Motor_right();
						delay_ms(1000);
						Motor_go();
				};break;
			}
			
	}
}
}
//测速处理程序###
 void process(void)                             //算出左右轮子的速度
{
 left_speed  = (left_numb/20)*20.5;
 right_speed = (right_numb/20)*20.5;

 left_numb  = 0;
 right_numb = 0;
                                                 //计划在此处通过串口把数据进行打印
}
//外部中断0服务程序
void EXTI0_IRQHandler(void)
{
 delay_ms(1);                   //消抖
 if(INT2==1)	              
 {
  right_numb++;
 }		 
 EXTI->PR=1<<0;                 //清除LINE0上的中断标志位  
}

//外部中断15~10服务程序
void EXTI15_10_IRQHandler(void)
{			
 delay_ms(1);                   //消抖			 
 if(INT0==1)      
 {
  left_numb++;
 }

 EXTI->PR=1<<13;                //清除LINE13上的中断标志位  
 EXTI->PR=1<<15;                //清除LINE15上的中断标志位  
}


//外部中断初始化程序
//初始化PA0,PA13,PA15为中断输入.
void EXTIX_Init(void)
{
 RCC->APB2ENR|=1<<2;                            //使能PORTA时钟 

 GPIOA->CRL&=0XFFFFFFF0;                        //PA0设置成输入	  
 GPIOA->CRL|=0X00000008;   
 GPIOA->CRH&=0X0F0FFFFF;                        //PA13,15设置成输入	  
 GPIOA->CRH|=0X80800000; 				   
 //GPIOA->ODR|=1<<13;	                            //PA13上拉,PA0默认下拉
 //GPIOA->ODR|=1<<15;	                            //PA15上拉

 Ex_NVIC_Config(GPIO_A,0,RTIR);                 //上升沿触发
 //Ex_NVIC_Config(GPIO_A,13,FTIR);                //下降沿触发
 Ex_NVIC_Config(GPIO_A,13,RTIR);                //上升沿触发
 //Ex_NVIC_Config(GPIO_A,15,FTIR);                //下降沿触发
 Ex_NVIC_Config(GPIO_A,15,RTIR);                //上升沿触发

 MY_NVIC_Init(2,2,EXTI0_IRQChannel,2);          //抢占2，子优先级2，组2
 MY_NVIC_Init(2,1,EXTI15_10_IRQChannel,2);      //抢占2，子优先级1，组2	   
}

//定时器3中断服务程序	 
void TIM3_IRQHandler(void)
{ 		    		  			    
 if(TIM3->SR&0X0001)                          //溢出中断
 {
	timer++;
  if(timer == 500)	                          //1S
  {
   timer = 0;
   flag  = 1;
  } 
 }
}