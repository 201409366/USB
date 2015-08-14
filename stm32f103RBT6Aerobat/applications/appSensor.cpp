#include <sensor.h>
#include <mpu6050_sensor.h>

//void initMPU6050Object(void) {
//	static unsigned char isInit = 0;
//	
//	if(!isInit) {
		MPU6050_Accelerometer acc = MPU6050_Accelerometer("i2c1", MPU6050_DEFAULT_ADDRESS);
		MPU6050_Gyroscope gryo = MPU6050_Gyroscope("i2c1", MPU6050_DEFAULT_ADDRESS);
//	}
//}
