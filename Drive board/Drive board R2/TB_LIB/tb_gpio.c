#include "tb_gpio.h"
#include "tb_delay.h"

void tb_gpio_init(void) {
	 /**********************
	 1.ִ�ж˿���ӳ��ʱ,���ù���ʱ�ӵ�ʹ��:RCC_APB2Periph_AFIO
	 
	 2.  &1.GPIO_Remap_SWJ_Disable: !< Full SWJ Disabled (JTAG-DP + SW-DP)
		  ��ʱPA13|PA14|PA15|PB3|PB4������Ϊ��ͨIO����
		Ϊ�˱���ĳЩ���Զ˿�,GPIO_Remap_SWJ_DisableҲ��ѡ��Ϊ��������ģʽ��
	  
		 &2.GPIO_Remap_SWJ_JTAGDisable: !< JTAG-DP Disabled and SW-DP Enabled
		 ��ʱPA15|PB3|PB4����Ϊ��ͨIO����
	  
		 &3.GPIO_Remap_SWJ_NoJTRST: !< Full SWJ Enabled (JTAG-DP + SW-DP) but without JTRST
		 ��ʱֻ��PB4����Ϊ��ͨIO���� 
	 **********************/
	
		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE); 		//ʹ�� PA �˿�ʱ��
	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);  //ʹ�ܽ�ֹJTAG
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);  //ʹ�ܽ�ֹJTAG

	
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
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //ʹ�� PB �˿�ʱ��
	
	//nled
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14; //���� PB3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //IO ��ת 50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);		
}

void beep_init(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE); //ʹ�� PB �˿�ʱ��
	
	//beep
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13; //���� PB4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //IO ��ת 50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}


void mkey_init(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //ʹ�� PA �˿�ʱ��
	
	//nled
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; //���� pin10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //�������
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void dj_io_init(void) {
	GPIO_InitTypeDef GPIO_InitStructure;	

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);	
}

void dj_io_set(u8 index, u8 level) {
	switch(index) {
		case 0:gpioB_pin_set(3, level);break; // PB0
		case 1:gpioA_pin_set(8, level);break; // PA0
		case 2:gpioB_pin_set(4, level);break; // PB1
		case 3:gpioB_pin_set(5, level);break; // PB6
		case 4:gpioB_pin_set(12, level);break; // PB7
		case 5:gpioA_pin_set(15, level);break; // PA1
		default:break;
	}
}



