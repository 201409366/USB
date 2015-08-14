#include "nRF24L01.h"

static char send_buffer[64];

void rt_appNRF24L01_thread_entry(void* parameter);

rt_err_t appNRF24L01Init(void){
	rt_err_t status;
	rt_thread_t init_thread;
	
	//status = nRF24L01_init(spi_device_name);
	status = RF24L01_Check();
	if(status == RT_EOK) {
		init_thread = rt_thread_create("appNRF24L01",
															 rt_appNRF24L01_thread_entry, RT_NULL,
															 2048, 8, 20);
		if (init_thread != RT_NULL)
			rt_thread_startup(init_thread);
		else
			status = RT_ERROR;
	}else
		status = RT_ERROR;
	
	return status;
}

void rt_appNRF24L01_thread_entry(void* parameter) {
	u8 status;	//用于判断接收/发送状态
	u8 txbuf[TX_PLOAD_WIDTH]="01234567890123456789012345678901";	 //发送缓冲
	rt_err_t result = RT_EOK;

	while(1) {
		
//		result = rt_mq_recv(sendData_mq, &send_buffer, 32, RT_WAITING_FOREVER);
//		if(result != RT_EOK) {
//			rt_kprintf("recv mq error !");
//			return;
//		}
//			
//		
//		RF24L01_TX_Mode();
//		/*开始发送数据*/	
//		status = RF24L01_Tx_Dat(txbuf);
//		
//		/*判断发送状态*/
//		switch(status)
//		{
//			case MAX_RT:
//				rt_kprintf("success \r\n");
//				//rt_thread_delay( RT_TICK_PER_SECOND*5);
//				break;
//			case ERROR:
//				rt_kprintf("error \r\n");
//				//rt_thread_delay( RT_TICK_PER_SECOND*15);
//				break;
//			case TX_DS:
//				rt_kprintf("fail \r\n");	 		
//				//rt_thread_delay(RT_TICK_PER_SECOND);
//				break;  								
//		}			  

		rt_thread_delay(RT_TICK_PER_SECOND);
	}	
}
