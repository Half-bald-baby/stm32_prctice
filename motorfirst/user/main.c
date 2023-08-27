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
#define FTIR   1                               //�½��ش���
#define RTIR   2                               //�����ش���
void EXTIX_Init(void);
void process(void);                             
void Timerx_Init(u16 arr,u16 psc);            //��ʱ����ʼ������  
void MY_NVIC_SetVectorTable(u32 NVIC_VectTab, u32 Offset);//����ƫ�Ƶ�ַ
void MY_NVIC_PriorityGroupConfig(u8 NVIC_Group);          //����NVIC����
void MY_NVIC_Init(u8 NVIC_PreemptionPriority,u8 NVIC_SubPriority,u8 NVIC_Channel,u8 NVIC_Group);//�����ж�
void Ex_NVIC_Config(u8 GPIOx,u8 BITx,u8 TRIM);            //�ⲿ�ж����ú���(ֻ��GPIOA~G)  


int main(void)  
{  
	u8 key;
 	u8 *str=0;
    Motor_12_Config(); //298???????  
    delay_init();  //???????  

	delay_init();	    	 //��ʱ������ʼ��	  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
  	
	Remote_Init();			//������ճ�ʼ��	
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
				case 98:                   //ǰ��
					{
				     Motor_go();
				  };break;	    
				case 2:
				  {
				     Motor_stop();
				  };break;		 
					  
				case 194:                  //��ת
          {
	           Motor_right();
						delay_ms(167);
						Motor_go();
          };break;	   
				case 34:                   //��ת
				  {
				     Motor_left();
						delay_ms(167);
						Motor_go();
				  };break;		  
					  
				case 168:                  //����
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
//���ٴ������###
 void process(void)                             //����������ӵ��ٶ�
{
 left_speed  = (left_numb/20)*20.5;
 right_speed = (right_numb/20)*20.5;

 left_numb  = 0;
 right_numb = 0;
                                                 //�ƻ��ڴ˴�ͨ�����ڰ����ݽ��д�ӡ
}
//�ⲿ�ж�0�������
void EXTI0_IRQHandler(void)
{
 delay_ms(1);                   //����
 if(INT2==1)	              
 {
  right_numb++;
 }		 
 EXTI->PR=1<<0;                 //���LINE0�ϵ��жϱ�־λ  
}

//�ⲿ�ж�15~10�������
void EXTI15_10_IRQHandler(void)
{			
 delay_ms(1);                   //����			 
 if(INT0==1)      
 {
  left_numb++;
 }

 EXTI->PR=1<<13;                //���LINE13�ϵ��жϱ�־λ  
 EXTI->PR=1<<15;                //���LINE15�ϵ��жϱ�־λ  
}


//�ⲿ�жϳ�ʼ������
//��ʼ��PA0,PA13,PA15Ϊ�ж�����.
void EXTIX_Init(void)
{
 RCC->APB2ENR|=1<<2;                            //ʹ��PORTAʱ�� 

 GPIOA->CRL&=0XFFFFFFF0;                        //PA0���ó�����	  
 GPIOA->CRL|=0X00000008;   
 GPIOA->CRH&=0X0F0FFFFF;                        //PA13,15���ó�����	  
 GPIOA->CRH|=0X80800000; 				   
 //GPIOA->ODR|=1<<13;	                            //PA13����,PA0Ĭ������
 //GPIOA->ODR|=1<<15;	                            //PA15����

 Ex_NVIC_Config(GPIO_A,0,RTIR);                 //�����ش���
 //Ex_NVIC_Config(GPIO_A,13,FTIR);                //�½��ش���
 Ex_NVIC_Config(GPIO_A,13,RTIR);                //�����ش���
 //Ex_NVIC_Config(GPIO_A,15,FTIR);                //�½��ش���
 Ex_NVIC_Config(GPIO_A,15,RTIR);                //�����ش���

 MY_NVIC_Init(2,2,EXTI0_IRQChannel,2);          //��ռ2�������ȼ�2����2
 MY_NVIC_Init(2,1,EXTI15_10_IRQChannel,2);      //��ռ2�������ȼ�1����2	   
}

//��ʱ��3�жϷ������	 
void TIM3_IRQHandler(void)
{ 		    		  			    
 if(TIM3->SR&0X0001)                          //����ж�
 {
	timer++;
  if(timer == 500)	                          //1S
  {
   timer = 0;
   flag  = 1;
  } 
 }
}