/***************************************************************
��������:
	ʵ��LED������
	ʵ��LED����˸����

***************************************************************/

#include "tb_rcc.h"		//
#include "tb_gpio.h"
#include "tb_delay.h"

/*-------------------------------------------------------------------------------------------------------
*  ���������ִ��				
*  ����������� ���ʱ������ ʹ���ⲿ������ΪSTM32������ʱ�� ����Ƶ��72M����ִ������
-------------------------------------------------------------------------------------------------------*/

int main(void) {	
	tb_rcc_init();			//rcc ʼ������ 
	tb_gpio_init();			//io�ڳ�ʼ�� ��Ҫ�ǹر�JTAG �� SWJ�˿ڹ���
	nled_init();			//��ʼ��LED��
	beep_init();
	
	
	while(1) {			
		nled_on();
		beep_on();
		tb_delay_ms(500);
		
		beep_off();
		nled_off();
		tb_delay_ms(500);
	}
}



