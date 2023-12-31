#ifndef __MOTOR1_H  
#define __MOTOR1_H  
  
  
#include "stm32f10x.h"  
#include "stm32f10x_gpio.h" 


#define High    1  
#define Low     0  
  
#define IN1(a) if (a)  \
    GPIO_SetBits(GPIOF,GPIO_Pin_0);\
else  \
    GPIO_ResetBits(GPIOF,GPIO_Pin_0)  
  
#define IN2(a) if (a)  \
    GPIO_SetBits(GPIOF,GPIO_Pin_1);\
else  \
    GPIO_ResetBits(GPIOF,GPIO_Pin_1)  
  
#define IN3(a) if (a)  \
    GPIO_SetBits(GPIOF,GPIO_Pin_2);\
else  \
    GPIO_ResetBits(GPIOF,GPIO_Pin_2)  
  
#define IN4(a) if (a)  \
    GPIO_SetBits(GPIOF,GPIO_Pin_3);\
else  \
    GPIO_ResetBits(GPIOF,GPIO_Pin_3)  
#define IN5(a) if (a)  \
    GPIO_SetBits(GPIOF,GPIO_Pin_4);\
else  \
    GPIO_ResetBits(GPIOF,GPIO_Pin_4)  
  
#define IN6(a) if (a)  \
    GPIO_SetBits(GPIOF,GPIO_Pin_5);\
else  \
    GPIO_ResetBits(GPIOF,GPIO_Pin_5)  
  
#define IN7(a) if (a)  \
    GPIO_SetBits(GPIOF,GPIO_Pin_6);\
else  \
    GPIO_ResetBits(GPIOF,GPIO_Pin_6)  
  
#define IN8(a) if (a)  \
    GPIO_SetBits(GPIOF,GPIO_Pin_7);\
else  \
    GPIO_ResetBits(GPIOF,GPIO_Pin_7)  


void Motor_12_Config(void);
void Motor_1_STOP(void);  
void Motor_1_PRun(void);  
void Motor_1_NRun(void);  
  
void Motor_2_STOP(void);  
void Motor_2_PRun(void);  
void Motor_2_NRun(void);  

void Motor_3_STOP(void);  
void Motor_3_PRun(void);  
void Motor_3_NRun(void);  
  
void Motor_4_STOP(void);  
void Motor_4_PRun(void);  
void Motor_4_NRun(void); 

void Motor_left(void);
void Motor_right(void);
void Motor_go(void);
  void Motor_back(void);
	void  Motor_stop(void);
#endif 



