#include <board.h>
#include <rtthread.h>
#include "24cxx.h"

void rt_app24C02_thread_entry(void* parameter);

rt_err_t app24C02Init(void)
{
	rt_thread_t init_thread;
		
	init_thread = rt_thread_create("app24C02",
														 rt_app24C02_thread_entry, RT_NULL,
														 2048, 8, 10);
	if (init_thread != RT_NULL) {
		rt_thread_startup(init_thread);
		return RT_EOK;
	}	else
		return RT_ERROR;
}

void rt_app24C02_thread_entry(void* parameter) {
	AT24CXX_Init();	
	
	while (1)
	{
		if(AT24CXX_Check() == 0)
		{
			rt_kprintf("24C02 test pass !\r\n");
		}else
		{
			rt_kprintf("24C02 test fail !\r\n");
		}		
		rt_thread_delay(RT_TICK_PER_SECOND*10); /* sleep 0.5 second and switch to other thread */
	}
}
