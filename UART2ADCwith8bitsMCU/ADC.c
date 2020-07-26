//___________________________________________________________________
//___________________________________________________________________
// Description: Analog input (10bit)
//  Copyright@: 2019 BY Louis Huang / https://github.com/louisopen/
//   File Name: ADC.c
//Targer Board: MK8002D
//    MCU Body: HT66F317 HT66F318-28ssop
//      Author: Louis Huang
//        Date: 2019/05/18
//     Version: V00 on Hardware V10
//     History:
//___________________________________________________________________
//___________________________________________________________________
#include "common.h"

//___________________________________________________________________
//Function: ADC get by channel
//   INPUT: U8 channel
//  OUTPUT: U16 data
//	  NOTE:   
//___________________________________________________________________
u16 Get_ADC(u8 adc_channel)
{
	__16_type	adc_rdata;
	_ade = 0;				//Disable ADC interrupt
	_sadc0 = 0B00110111;	//enable & format& channel selection
	if(adc_channel==8)
	{
		_sadc1 = 0B01000011;//AVDD/2 for input & clock source selection
	}
	else
	{
		_sadc1 = 0B00000011;//AN0~AN7 & clock source selection
	}
	_sadc2 = 0B00000000;	//ENOPA .. reference voltage selection
	
	//_acerl = 0x00;		//Not used binding IO
	_acerl = 0B00000001;	//binding IO  pb0,pb1,pb2,pa4,pa5,pa6,pa7,pb3 see you.
	switch(adc_channel)
	{
		case 0:  _sadc0 &= 0xF8;  break;	//_acerl=0b00000001; pb0 an0
		case 1:  _sadc0 &= 0xF9;  break;	//_acerl=0b00000010; pb1 an1
		case 2:  _sadc0 &= 0xFa;  break;	//_acerl=0b00000100; pb2 an2
		case 3:  _sadc0 &= 0xFb;  break;	//_acerl=0b00001000; pa4 an3	
		case 4:  _sadc0 &= 0xFc;  break;	//_acerl=0b00010000; pa5 an4
		case 5:  _sadc0 &= 0xFd;  break;	//_acerl=0b00100000; pa6 an5	
		case 6:  _sadc0 &= 0xFe;  break;	//_acerl=0b01000000; pa7 an6			
		case 7:  _sadc0 &= 0xFf;  break;	//_acerl=0b10000000; pb3 an7		
	}
	_enadc = 1;			//ADC enable convert
	
	GCC_DELAY(20);
	_start = 0;			//_sadc0.7 start convert
	_start = 1;			//_sadc0.7 start convert
	_start = 0;			//_sadc0.7 start convert
	//_ade=1;			//Interrupt enable
	while(_adbz != 0)	//_sadc0.6 polling bit
	{} 
	adc_rdata.byte.byte0 = _sadol;
	adc_rdata.byte.byte1 = _sadoh;
	//_start = 0;		//_sadc0.7  _start=0
	//_start = 0;		//_sadc0.7	_start=0	
	return adc_rdata.u16;
}
//___________________________________________________________________
//Function: Disable ADC
//   INPUT: 
//  OUTPUT: 
//	  NOTE:   
//___________________________________________________________________
void Disable_ADC()
{
	_enadc = 0;		//_sadc0.5 disable adc
}
//___________________________________________________________________
//Function: Test the ADC function with uart send
//   INPUT: Get adc value
//  OUTPUT: Uart port
//	  NOTE:   
//___________________________________________________________________
//#include "uart.h"
void TEST_ADC()
{
	__16_type	adc_rdata_buff;
	while(1)
	{
		GCC_CLRWDT();
		adc_rdata_buff.u16 = Get_ADC(AN0);

		adc_rdata_buff.u16++;
		
//		Uart_TXD_Send(adc_rdata_buff.u16);			
//		GCC_DELAY(60000);		
//		GCC_DELAY(60000);			
	}
}
