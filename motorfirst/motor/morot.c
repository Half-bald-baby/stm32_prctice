#include "stm32f10x.h"  //����STM32�ٷ���  
#include "stm32f10x_rcc.h"  //����STM32��RCCʱ�ӿ�  
#include "delay.h"       //��ʱ��  
#include "motor.h"  
void Motor_12_Config(void)  //�����ʼ������  
{  
    GPIO_InitTypeDef GPIO_InitStructure;   //����GPIO_InitTypeDef�ṹ��  
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOF, ENABLE);  //��������ʱ��  
      
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7; //����IN����  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //ͨ���������  
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  //�����������  
    GPIO_Init(GPIOF, &GPIO_InitStructure);  //��ʼ��GPIOA�����Ų���,д��  
      
    GPIO_ResetBits(GPIOF,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7); //������������  
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
 
 
