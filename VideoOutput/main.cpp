#include "mbed.h"
#include "9DOF.h"

//establish I2C connections
I2C i2c( p9, p10 );

//establish serial communications with computer via usb
Serial pc(USBTX, USBRX); //tx, rx

//arrays to store data from 9DOF
int accelerometer_data[3];
int gyro_data[3];
int magnetometer_data[3];

int main() {

	//initialize each IC
	init_adxl345(i2c);
	init_itg3200(i2c);
	init_hmc5883(i2c);
    
    while(1) {        
        //read from each IC
        read_adxl345(i2c, accelerometer_data);
        pc.printf("ACCEL: %i\t%i\t%i", accelerometer_data[0], accelerometer_data[1], accelerometer_data[2]);
        read_itg3200(i2c, gyro_data);
        pc.printf("GYRO: %i\t%i\t%i", gyro_data[0], gyro_data[1], gyro_data[2]);
        read_hmc5883(i2c, magnetometer_data);
        pc.printf("Magnet: %i\t%i\t%i", magnetometer_data[0], magnetometer_data[1], magnetometer_data[2]);
    }
}