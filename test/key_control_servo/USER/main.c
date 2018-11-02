/***************************************************************
��������:
	ʵ��LED������ 
	ʵ��LED����˸����
	
	ʵ�ַ���������
	ģ�ⰴ�������رշ�������LED
	
	ʵ��ģ�ⰴ������0�Ŷ��������ת

***************************************************************/

#include "tb_rcc.h"
#include "tb_gpio.h"
#include "tb_delay.h"
#include "tb_global.h"
#include "tb_timer.h"

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
	mkey_init();
	dj_io_init();
	//��� ��ʱ����ʼ��
	TIM2_Int_Init(20000, 71);
	while(1) {		
		if(mkey_read() == 0) {		
			nled_on();beep_on();
			duoji_doing[1].cur = 2400;
		} else {
			nled_off();beep_off();
			duoji_doing[1].cur = 500;
		}
	}
}



