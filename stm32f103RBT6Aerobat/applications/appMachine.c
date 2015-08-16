#include <rtthread.h>
#include "machine.h"

void rt_appMachine_thread_entry(void* parameter);

rt_err_t appMachineInit(void){
	rt_err_t status = RT_EOK;
	rt_thread_t init_thread;
	
	rt_hw_machine_init();
	
	init_thread = rt_thread_create("appMachine",
													 rt_appMachine_thread_entry, RT_NULL,
													 2048, 8, 20);
	
	if (init_thread != RT_NULL)
		rt_thread_startup(init_thread);
	
	return status;
}

void rt_appMachine_thread_entry(void* parameter) {
	while(1) {
		rt_thread_delay(RT_TICK_PER_SECOND * 100);
	}
}
