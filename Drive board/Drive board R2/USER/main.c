/***************************************************************
功能描述:
	实现LED灯亮灭 
	实现LED灯闪烁功能
	
	实现蜂鸣器鸣叫
	模拟按键开启关闭蜂鸣器和LED
	
	实现模拟按键控制0号舵机来回旋转
	
	实现多个舵机同时控制，做一些简单的组合动作

***************************************************************/

#include "tb_rcc.h"
#include "tb_gpio.h"
#include "tb_delay.h"
#include "tb_global.h"
#include "tb_timer.h"
#include "motor.h"


int i = 0, j;

/*-------------------------------------------------------------------------------------------------------
*  程序从这里执行				
*  这个启动代码 完成时钟配置 使用外部晶振作为STM32的运行时钟 并倍频到72M最快的执行速率
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
	//舵机 定时器初始化
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




