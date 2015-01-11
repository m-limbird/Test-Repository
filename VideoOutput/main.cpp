#include "mbed.h"

//Accelerometer
#define ADXL345_ADDRESS_W (0xA6)
#define ADXL345_ADDRESS_R (0xA7)
#define ADXL345_REGISTER_XLSB (0x32)
#define ADXL_REGISTER_PWRCTL (0x2D)
#define ADXL_PWRCTL_MEASURE (0x01 << 3)

//Gyroscope
#define ITG3200_ADDRESS_W (0xD0)
#define ITG3200_ADDRESS_R (0xD1)
#define ITG3200_REGISTER_XMSB (0x1D)
#define ITG3200_REGISTER_DLPF_FS (0x16)
#define ITG3200_FULLSCALE (0x03 << 3)
#define ITG3200_42HZ (0x03)

//3-Axis Digital Compass IC
#define HMC5843_ADDRESS (0x3C >> 1)
#define HMC5843_REGISTER_XMSB (0x03)
#define HMC5843_REGISTER_MEASMODE (0x02)
#define HMC5843_MEASMODE_CONT (0x00)

I2C	i2c( p9, p10 );	// sda, scl

void init_adxl345();
void read_adxl345();
void init_itg3200();
void read_itg3200();
//void init_hmc5843();

Serial pc(USBTX, USBRX); //tx, rx

int accelerometer_data[3];
int gyro_data[3];
//int magnetometer_data[3];

PwmOut led(LED1);

float brightness = 0.0;

int main() {

	init_adxl345();
	//init_hmc5843();
	init_itg3200();
    
    //pc.printf("Press 'u' to turn LED1 brightness up, 'd' to turn it down.\n");
    
    while(1) {        
        /*
        char c = pc.getc();
        if((c == 'u') && (brightness < 0.5)) {
        	brightness += 0.01;
        	led = brightness;
        }
        if((c == 'd') && (brightness > 0.0)) {
        	brightness -= 0.01;
        	led = brightness;
        }
        */
        //read_adxl345();
        read_itg3200();
        
    }
}

void init_adxl345() {
	char data[2];
	data[0] = ADXL_REGISTER_PWRCTL;
	data[1] = ADXL_PWRCTL_MEASURE;

	i2c.write(ADXL345_ADDRESS_W, data, 2); // first part of data is the register
	
	wait(0.5);

	i2c.write(ADXL345_ADDRESS_W, data, 1);
	i2c.read(ADXL345_ADDRESS_R, data, 2);
	pc.printf("%i\n",(unsigned int)data);
}

void read_adxl345() {
	char bytes[6];
	memset(bytes,0,6);
	bytes[0] = ADXL345_REGISTER_XLSB;
	
	i2c.write(ADXL345_ADDRESS_W, bytes, 1);
	i2c.read(ADXL345_ADDRESS_R, bytes, 6);

	for (int i=0;i<3;++i) {
		accelerometer_data[i] = (int)bytes[2*i] + (((int)bytes[2*i + 1]) << 8);
 	}
 	
 	pc.printf("ACCEL: %i\t%i\t%i", accelerometer_data[0], accelerometer_data[1], accelerometer_data[2]);
}


void init_itg3200() {
	char data[2];
	data[0] = ITG3200_REGISTER_DLPF_FS;
	data[1] = ITG3200_FULLSCALE | ITG3200_42HZ;

	i2c.write(ITG3200_ADDRESS_W, data,2);

	i2c.read(ITG3200_ADDRESS_R, data, 1);

	pc.printf("%i\n",(unsigned int)data);
}

void read_itg3200() {
	char bytes[6];
	memset(bytes,0,6);
	bytes[0] = ITG3200_REGISTER_XMSB;

	i2c.write(ITG3200_ADDRESS_W, bytes, 1);
	i2c.read(ITG3200_ADDRESS_R, bytes, 6);
	
	for (int i=0;i<3;++i) {
		gyro_data[i] = (int)bytes[2*i + 1] + (((int)bytes[2*i]) << 8);
	}
	
	pc.printf("GYRO: %i\t%i\t%i", gyro_data[0], gyro_data[1], gyro_data[2]);
}
/*
void init_hmc5843() {
	bytes data = 0;
  
	i2c_write(HMC5843_ADDRESS, HMC5843_REGISTER_MEASMODE, HMC5843_MEASMODE_CONT);

	i2c_read(HMC5843_ADDRESS, HMC5843_REGISTER_MEASMODE, 1, &data);
	Serial.println((unsigned int)data);
}

void read_hmc5843() {
	bytes bytes[6];
	memset(bytes,0,6);

	i2c_read(HMC5843_ADDRESS, HMC5843_REGISTER_XMSB, 6, bytes);

	for (int i=0;i<3;++i) {
		magnetometer_data[i] = (int)bytes[2*i + 1] + (((int)bytes[2*i]) << 8);
	}
}
*/