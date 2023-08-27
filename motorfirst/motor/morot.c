#include "stm32f10x.h"  //导入STM32官方库  
#include "stm32f10x_rcc.h"  //导入STM32的RCC时钟库  
#include "delay.h"       //延时库  
#include "motor.h"  
void Motor_12_Config(void)  //定义初始化函数  
{  
    GPIO_InitTypeDef GPIO_InitStructure;   //定义GPIO_InitTypeDef结构体  
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOF, ENABLE);  //开启引脚时钟  
      
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7; //定义IN引脚  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //通用推挽输出  
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  //设置输出功率  
    GPIO_Init(GPIOF, &GPIO_InitStructure);  //初始化GPIOA的引脚参数,写进  
      
    GPIO_ResetBits(GPIOF,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7); //所有引脚拉低  
}  
  
void Motor_1_STOP(void)  
{  
    IN1(High);  
    IN2(High);  
}  
  
void Motor_1_PRun(void)  
{  
    IN1(Low);  
    IN2(High);  
}  
  
void Motor_1_NRun(void)  
{  
    IN1(High);  
    IN2(Low);  
}  
  
void Motor_2_STOP(void)  
{  
    IN3(High);  
    IN4(High);  
}  
  
void Motor_2_PRun(void)  
{  
    IN3(Low);  
    IN4(High);  
}  
  
void Motor_2_NRun(void)  
{  
    IN3(High);  
    IN4(Low);  
}


void Motor_3_STOP(void)  
{  
    IN5(High);  
    IN6(High);  
}  
  
void Motor_3_PRun(void)  
{  
    IN5(Low);  
    IN6(High);  
}  
  
void Motor_3_NRun(void)  
{  
    IN5(High);  
    IN6(Low);  
}
void Motor_4_STOP(void)  
{  
    IN7(High);  
    IN8(High);  
}  
  
void Motor_4_PRun(void)  
{  
    IN7(Low);  
    IN8(High);  
}  
  
void Motor_4_NRun(void)  
{  
    IN7(High);  
    IN8(Low);  
}

void Motor_left(void)
{
IN1(High);  
    IN2(Low);
	 IN5(High);  
    IN6(Low); 
	 IN3(Low);  
    IN4(High); 
	 IN7(Low);  
    IN8(High);
}

void Motor_right(void)
{
	 IN1(Low);  
    IN2(High); 
	 IN5(Low);  
    IN6(High);
	 IN3(High);  
    IN4(Low);  
	 IN7(High);  
    IN8(Low); 
}
void Motor_go(void)
{
	  IN1(Low);  
    IN2(High);  
    IN3(Low);  
    IN4(High); 
	/*	 IN5(Low);  
    IN6(High);
IN7(Low);  
    IN8(High);  */	
}
void Motor_back(void)
{
IN1(High);  
    IN2(Low);
 IN3(High);  
    IN4(Low); 
	 IN5(High);  
    IN6(Low);
	 IN7(High);  
    IN8(Low); 
}


 void Motor_stop(void)
 {
    IN1(High);  
    IN2(High);  
  IN3(High);  
    IN4(High);  
   IN5(High);  
    IN6(High); 
	     IN7(High);  
    IN8(High); 
 }
 
 
