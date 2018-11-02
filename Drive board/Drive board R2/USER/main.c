/***************************************************************
��������:
	ʵ��LED������ 
	ʵ��LED����˸����
	
	ʵ�ַ���������
	ģ�ⰴ�������رշ�������LED
	
	ʵ��ģ�ⰴ������0�Ŷ��������ת
	
	ʵ�ֶ�����ͬʱ���ƣ���һЩ�򵥵���϶���

***************************************************************/

#include "tb_rcc.h"
#include "tb_gpio.h"
#include "tb_delay.h"
#include "tb_global.h"
#include "tb_timer.h"
#include "motor.h"


int i = 0, j;

/*-------------------------------------------------------------------------------------------------------
*  ���������ִ��				
*  ����������� ���ʱ������ ʹ���ⲿ������ΪSTM32������ʱ�� ����Ƶ��72M����ִ������
-------------------------------------------------------------------------------------------------------*/

int main(void) {	
	tb_rcc_init();
	tb_gpio_init();
	tb_global_init();
	nled_init();
	beep_init();
	beep_off();
	//mkey_init();
	dj_io_init();
	//��� ��ʱ����ʼ��
	TIM2_Int_Init(20000, 71);
	Motor_Init(7199, 0);
	
	
	while(1) {	
		
		nled_on();beep_on();
		tb_delay_ms(5000);
		nled_off();beep_off();
		MotorDriver_L_Turn_Reverse();
		tb_delay_ms(5000);
		MotorDriver_L_Turn_Forward();
		
		
	
		
		for(j=500; j<2500; j+=10) {
			for(i=0; i<6; i++) {
				duoji_doing[i].cur = j;
			}
			mdelay(10);
		}
		
		for(j=2500; j>500; j-=100) {
			for(i=0; i<6; i++) {
				duoji_doing[i].cur = j;
			}
			mdelay(100);
		}
		
	}
}




