#include <stdio.h>
#include <sensor.h>

void rt_accel_test_thread_entry(void* parameter);
void rt_gyro_test_thread_entry(void* parameter);

rt_err_t appSensorInit(void){
	rt_err_t status = RT_EOK;
	rt_thread_t init_thread;

	init_thread = rt_thread_create("accel_test",
																 rt_accel_test_thread_entry, RT_NULL,
																 2048, 8, 20);
	if (init_thread != RT_NULL)
		rt_thread_startup(init_thread);
	else
		status = RT_ERROR;		

	init_thread = rt_thread_create("gyro_test",
																 rt_gyro_test_thread_entry, RT_NULL,
																 2048, 8, 20);
	if (init_thread != RT_NULL)
		rt_thread_startup(init_thread);
	else
		status = RT_ERROR;		
	
	
	return status;
		
}

void rt_accel_test_thread_entry(void* parameter)
{
    rt_sensor_t sensor;
    sensors_event_t event;
    char line[64];
	
		
    sensor = rt_sensor_get_default(SENSOR_TYPE_ACCELEROMETER);
    if (sensor != RT_NULL)
    {
        int index;
        SensorConfig config = {SENSOR_MODE_NORMAL, SENSOR_DATARATE_400HZ, SENSOR_ACCEL_RANGE_2G};

        rt_sensor_activate(sensor, 1);
        rt_sensor_configure(sensor, &config);

        index = 0;
        index = index;

        while (1) 
        // for (index = 0; index < 10; index ++)
        {
            rt_sensor_poll(sensor, &event);

            sprintf(line, "type: %d, x:%f, y:%f, z:%f", 
                event.type, 
                event.acceleration.x, 
                event.acceleration.y,
                event.acceleration.z);
            rt_kprintf("%s\n", line);
						rt_thread_delay( RT_TICK_PER_SECOND/100 );
        }
    }    
}

void rt_gyro_test_thread_entry(void* parameter)
{
    rt_sensor_t sensor;
    sensors_event_t event;
    char line[64];
	
//		initMPU6050Object();

    sensor = rt_sensor_get_default(SENSOR_TYPE_GYROSCOPE);
    if (sensor != RT_NULL)
    {
        int index;
        SensorConfig config = {SENSOR_MODE_NORMAL, SENSOR_DATARATE_100HZ, SENSOR_GYRO_RANGE_250DPS};

        rt_sensor_activate(sensor, 1);
        rt_sensor_configure(sensor, &config);

        index = 0;
        index = index;

        while (1) 
        // for (index = 0; index < 10; index ++)
        {
            rt_sensor_poll(sensor, &event);

            sprintf(line, "type: %d, x:%f, y:%f, z:%f", 
                event.type, 
                event.gyro.x, 
                event.gyro.y,
                event.gyro.z);
            rt_kprintf("%s\n", line);
						rt_thread_delay( RT_TICK_PER_SECOND/100 );
        }
    }    
}
