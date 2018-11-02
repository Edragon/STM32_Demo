/***************************************************************
功能描述:
	实现LED灯亮灭
	实现LED灯闪烁功能

***************************************************************/

#include "tb_rcc.h"		//
#include "tb_gpio.h"
#include "tb_delay.h"

/*-------------------------------------------------------------------------------------------------------
*  程序从这里执行				
*  这个启动代码 完成时钟配置 使用外部晶振作为STM32的运行时钟 并倍频到72M最快的执行速率
-------------------------------------------------------------------------------------------------------*/

int main(void) {	
	tb_rcc_init();			//rcc 始终设置 
	tb_gpio_init();			//io口初始化 主要是关闭JTAG 和 SWJ端口功能
	nled_init();			//初始化LED灯
	while(1) {			
		nled_on();
		tb_delay_ms(500);
		nled_off();
		tb_delay_ms(500);
	}
}




