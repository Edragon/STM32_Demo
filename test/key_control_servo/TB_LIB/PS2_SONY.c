#include "PS2_SONY.h"
#include "tb_delay.h"

/*
	PS2_DAT PC14		IN
	PS2_CMD PA13		OUT
	PS2_ATT PA12		OUT
	PS2_CLK PA11 		OUT
*/
void psx_io_config(void) {
	GPIO_InitTypeDef GPIO_InitStructure, GPIO_InitStructure2;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE); 		//ʹ�� PA �˿�ʱ��
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);  //ʹ�ܽ�ֹJTAG
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13; 					//���� pin0-3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 			//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 			//IO ��ת 50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);  					//
	
	
	GPIO_InitStructure2.GPIO_Pin =GPIO_Pin_14;
	GPIO_InitStructure2.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(GPIOA, &GPIO_InitStructure2);	
}

void PSX_init(void) {
	psx_io_config();
	PS2_ATT(1);
	PS2_CMD(1);
	PS2_CLK(1);
	//PS2_DAT = 0;
	//PS2_ACK = 1;
}

unsigned char psx_transfer(unsigned char dat) {
	unsigned char rd_data ,wt_data, i;
	wt_data = dat;
	rd_data = 0;
	//PS2_CLK(1);
	//tb_delay_us(10);
	for(i = 0;i < 8;i++){
		PS2_CMD((wt_data & (0x01 << i)));
		PS2_CLK(1);
		tb_delay_us(10);
		PS2_CLK(0);
		tb_delay_us(10);
		PS2_CLK(1);
		//tb_delay_us(15);
		if(PS2_DAT) {
			rd_data |= 0x01<<i;
		}
	}
	return rd_data;
}

void psx_write_read(unsigned char *get_buf) {
	PS2_ATT(0);
	get_buf[0] = psx_transfer(START_CMD);
	get_buf[1] = psx_transfer(ASK_DAT_CMD);
	get_buf[2] = psx_transfer(get_buf[0]);
	get_buf[3] = psx_transfer(get_buf[0]);
	get_buf[4] = psx_transfer(get_buf[0]);
	get_buf[5] = psx_transfer(get_buf[0]);
	get_buf[6] = psx_transfer(get_buf[0]);
	get_buf[7] = psx_transfer(get_buf[0]);
	get_buf[8] = psx_transfer(get_buf[0]);	
	PS2_ATT(1);
	
	return;
}