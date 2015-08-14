#include <board.h>
#include <rtthread.h>

/* UART接收消息结构*/
struct rx_msg
{
	rt_device_t dev;
	rt_size_t size;
};
struct rx_msg msg;

/* 用于发送数据的消息队列*/
rt_mq_t sendData_mq;

/* 接收线程的接收缓冲区*/
static char uart_rx_buffer[64];

/* 用于等待数据 */
static rt_sem_t sem = RT_NULL;

void rt_appUsart_thread_entry(void* parameter);

/* 数据到达回调函数*/
rt_err_t uart_input(rt_device_t dev, rt_size_t size)
{
	msg.dev = dev;
	msg.size = size;	
		/* 释放一次信号量 */
	rt_sem_release(sem);
	return RT_EOK;
}

rt_err_t appUsartInit(void){
	rt_thread_t init_thread;
		
	init_thread = rt_thread_create("appUsart",
														 rt_appUsart_thread_entry, RT_NULL,
														 2048, 7, 20);
	if (init_thread != RT_NULL) {
		rt_thread_startup(init_thread);
		return RT_EOK;
	}	else
		return RT_ERROR;
}

void rt_appUsart_thread_entry(void* parameter) {
	rt_device_t device;
	rt_err_t result = RT_EOK;
	
		/* 创建一个信号量，初始值是0 */
	sem = rt_sem_create("usartSem", 0, RT_IPC_FLAG_FIFO);
	sendData_mq = rt_mq_create("usartMQ",32,4,RT_IPC_FLAG_FIFO);
	
	/* 查找系统中的串口1设备*/
	device = rt_device_find("uart2");
	if (device!= RT_NULL)
	{
		/* 设置回调函数及打开设备*/
		rt_device_set_rx_indicate(device, uart_input);
		rt_device_open(device, RT_DEVICE_OFLAG_RDWR | RT_DEVICE_FLAG_INT_RX);
	}

	while (1)
	{
		//等待数据
		/* 继续持有信号量，并永远等待直到持有到信号量 */
    result = rt_sem_take(sem, RT_WAITING_FOREVER);
		if (result == -RT_ETIMEOUT)
		{
			/* 接收超时*/
			rt_kprintf("system error !\n\r");
		}
		/* 成功收到消息*/
		if (result == RT_EOK)
		{
			rt_uint32_t rx_length;
			rx_length = (sizeof(uart_rx_buffer) - 1) > msg.size ? msg.size : sizeof(uart_rx_buffer) - 1;
			/* 读取消息*/
			rx_length = rt_device_read(msg.dev, 0, &uart_rx_buffer[0],rx_length);
			uart_rx_buffer[rx_length] = '\0';
			
			/* 发送消息，等待nRF24L01读取*/			
			rt_mq_send(sendData_mq, uart_rx_buffer, rx_length);			
		}
	}
}
