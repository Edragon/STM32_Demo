#include "tb_gpio.h"
#include "tb_delay.h"

void tb_gpio_init(void) {
	 /**********************
	 1.执行端口重映射时,复用功能时钟得使能:RCC_APB2Periph_AFIO
	 
	 2.  &1.GPIO_Remap_SWJ_Disable: !< Full SWJ Disabled (JTAG-DP + SW-DP)
		  此时PA13|PA14|PA15|PB3|PB4都可作为普通IO用了
		为了保存某些调试端口,GPIO_Remap_SWJ_Disable也可选择为下面两种模式：
	  
		 &2.GPIO_Remap_SWJ_JTAGDisable: !< JTAG-DP Disabled and SW-DP Enabled
		 此时PA15|PB3|PB4可作为普通IO用了
	  
		 &3.GPIO_Remap_SWJ_NoJTRST: !< Full SWJ Enabled (JTAG-DP + SW-DP) but without JTRST
		 此时只有PB4可作为普通IO用了 
	 **********************/
	
		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE); 		//使能 PA 端口时钟
	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);  //使能禁止JTAG
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);  //使能禁止JTAG

	
	return;	
}

void gpioA_pin_set(unsigned char pin, unsigned char level) {
	if(level) {
		GPIO_SetBits(GPIOA,1 << pin);
	} else {
		GPIO_ResetBits(GPIOA,1 << pin);
	}
}

void gpioB_pin_set(unsigned char pin, unsigned char level) {
	if(level) {
		GPIO_SetBits(GPIOB,1 << pin);
	} else {
		GPIO_ResetBits(GPIOB,1 << pin);
	}
}


void gpioC_pin_set(unsigned char pin, unsigned char level) {
	if(level) {
		GPIO_SetBits(GPIOC,1 << pin);
	} else {
		GPIO_ResetBits(GPIOC,1 << pin);
	}
}

void nled_init() {
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //使能 PB 端口时钟
	
	//nled
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; //配置 PB3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //IO 翻转 50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);		
}

void beep_init(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE); //使能 PB 端口时钟
	
	//beep
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4; //配置 PB4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //IO 翻转 50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}


void mkey_init(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //使能 PA 端口时钟
	
	//nled
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; //配置 pin10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //推挽输出
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void dj_io_init(void) {
	GPIO_InitTypeDef GPIO_InitStructure;	

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0|GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);	
}

void dj_io_set(u8 index, u8 level) {
	switch(index) {
		case 0:gpioB_pin_set(0, level);break; // PB0
		case 1:gpioA_pin_set(0, level);break; // PA0
		case 2:gpioB_pin_set(1, level);break; // PB1
		case 3:gpioB_pin_set(6, level);break; // PB6
		case 4:gpioB_pin_set(7, level);break; // PB7
		case 5:gpioA_pin_set(1, level);break; // PA1
		default:break;
	}
}



