#include "mbed.h"

//Accelerometer
#define  ADXL345_ADDRESS (0xA6 >> 1)
#define ADXL345_REGISTER_XLSB (0x32)
#define ADXL_REGISTER_PWRCTL (0x2D)
#define ADXL_PWRCTL_MEASURE (1 << 3)

//Gyroscope
#define ITG3200_ADDRESS (0xD0 >> 1)
#define ITG3200_REGISTER_XMSB (0x1D)
#define ITG3200_REGISTER_DLPF_FS (0x16)
#define ITG3200_FULLSCALE (0x03 << 3)
#define ITG3200_42HZ (0x03)

//3-Axis Digital Compass IC
#define HMC5843_ADDRESS (0x3C >> 1)
#define HMC5843_REGISTER_XMSB (0x03)
#define HMC5843_REGISTER_MEASMODE (0x02)
#define HMC5843_MEASMODE_CONT (0x00)

//I2C		i2c( p9, p10 );	// sda, scl

//void init_adxl345();
//void init_itg3200();
//void init_hmc5843();

const int addr = 0x90;
Serial pc(USBTX, USBRX); //tx, rx

//int adxl345_Data[3];
//int itg3200_Data[3];
//int hmc5843_Data[3];

PwmOut led(LED1);

float brightness = 0.0;

int main() {
	//char cmd[2];

	//init_adxl345();
	//init_hmc5843();
	//init_itg3200();
    
    pc.printf("Press 'u' to turn LED1 brightness up, 'd' to turn it down.\n");
    
    while(1) {
        //cmd[0] = 0x01;
        //cmd[1] = 0x00;
        //i2c.write(addr, cmd, 2); // i2c.write(address, command, bytes);
        
        char c = pc.getc();
        if((c == 'u') && (brightness < 0.5)) {
        	brightness += 0.01;
        	led = brightness;
        }
        if((c == 'd') && (brightness > 0.0)) {
        	brightness -= 0.01;
        	led = brightness;
        }
        
    }
}


/*
void init_adxl345() {
	char data = 0;

	i2c_write(ADXL345_ADDRESS, ADXL_REGISTER_PWRCTL, ADXL_PWRCTL_MEASURE);

	i2c_read(ADXL345_ADDRESS, ADXL_REGISTER_PWRCTL, 1, &data);
	Serial.println((unsigned int)data);
}

void read_adxl345() {
	bytes bytes[6];
	memset(bytes,0,6);

	i2c_read(ADXL345_ADDRESS, ADXL345_REGISTER_XLSB, 6, bytes);

	for (int i=0;i<3;++i) {
		accelerometer_data[i] = (int)bytes[2*i] + (((int)bytes[2*i + 1]) << 8);
 	}
}

void init_itg3200() {
	byte data = 0;

	i2c_write(ITG3200_ADDRESS, ITG3200_REGISTER_DLPF_FS, ITG3200_FULLSCALE | ITG3200_42HZ);

	i2c_read(ITG3200_ADDRESS, ITG3200_REGISTER_DLPF_FS, 1, &data);

	Serial.println((unsigned int)data);
}

void read_itg3200() {
	bytes bytes[6];
	memset(bytes,0,6);

	i2c_read(ITG3200_ADDRESS, ITG3200_REGISTER_XMSB, 6, bytes);
	for (int i=0;i<3;++i) {
		gyro_data[i] = (int)bytes[2*i + 1] + (((int)bytes[2*i]) << 8);
	}
}

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