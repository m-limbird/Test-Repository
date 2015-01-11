#ifndef __9DOF_H_
#define __9DOF_H_

#include "mbed.h"

//Accelerometer addresses
#define ADXL345_ADDRESS_W (0xA6)
#define ADXL345_ADDRESS_R (0xA7)
#define ADXL345_REGISTER_XLSB (0x32)
#define ADXL_REGISTER_PWRCTL (0x2D)
#define ADXL_PWRCTL_MEASURE (0x01 << 3)

//Gyroscope addresses
#define ITG3200_ADDRESS_W (0xD0)
#define ITG3200_ADDRESS_R (0xD1)
#define ITG3200_REGISTER_XMSB (0x1D)
#define ITG3200_REGISTER_DLPF_FS (0x16)
#define ITG3200_FULLSCALE (0x03 << 3)
#define ITG3200_42HZ (0x03)

//3-Axis Digital Compass IC addresses
#define HMC5883_ADDRESS_W (0x3C)
#define HMC5883_ADDRESS_R (0x3D)
#define HMC5883_REGISTER_XMSB (0x03)
#define HMC5883_REGISTER_MEASMODE (0x02)
#define HMC5883_MEASMODE_CONT (0x00)

//Declare functions
void init_adxl345(I2C i2c);
void read_adxl345(I2C i2c);
void init_itg3200(I2C i2c);
void read_itg3200(I2C i2c);
void init_hmc5883(I2C i2c);
void read_hmc5883(I2C i2c);

//This function initializes the Digital Accelerometer ADXL345
char* init_adxl345(I2C i2c) {
    char data[2];
    data[0] = ADXL_REGISTER_PWRCTL;
    data[1] = ADXL_PWRCTL_MEASURE;

    i2c.write(ADXL345_ADDRESS_W, data, 2); // first part of data is the register

    i2c.write(ADXL345_ADDRESS_W, data, 1);
    i2c.read(ADXL345_ADDRESS_R, data, 2);
}

void read_adxl345(I2C i2c, int[] data) {
    char bytes[6];
    memset(bytes,0,6);
    bytes[0] = ADXL345_REGISTER_XLSB;
    
    i2c.write(ADXL345_ADDRESS_W, bytes, 1);
    i2c.read(ADXL345_ADDRESS_R, bytes, 6);

    for (int i=0;i<3;++i) {
        data[i] = (int)bytes[2*i] + (((int)bytes[2*i + 1]) << 8);
    }
}


void init_itg3200(I2C i2c) {
    char data[2];
    data[0] = ITG3200_REGISTER_DLPF_FS;
    data[1] = ITG3200_FULLSCALE | ITG3200_42HZ; //bitwise or
    
    i2c.write(ITG3200_ADDRESS_W, data,2);
    
    i2c.write(ITG3200_ADDRESS_W, data,1);
    i2c.read(ITG3200_ADDRESS_R, data, 2);
}

void read_itg3200(I2C i2c, int[] data) {
    char bytes[6];
    memset(bytes,0,6);
    bytes[0] = ITG3200_REGISTER_XMSB;

    i2c.write(ITG3200_ADDRESS_W, bytes, 1);
    i2c.read(ITG3200_ADDRESS_R, bytes, 6);
    
    for (int i=0;i<3;++i) {
        data[i] = (int)bytes[2*i + 1] + (((int)bytes[2*i]) << 8);
    }
}

void init_hmc5883(I2C i2c) {
    char data[2];
    data[0] = HMC5883_REGISTER_MEASMODE;
    data[1] = HMC5883_MEASMODE_CONT;
  
    i2c.write(HMC5883_ADDRESS_W, data, 2);
    i2c.read(HMC5883_ADDRESS_R, data, 1);
}

void read_hmc5883(I2C i2c, int[] data) {
    char bytes[6];
    memset(bytes,0,6);
    bytes[0] = HMC5883_REGISTER_XMSB;

    i2c.write(HMC5883_ADDRESS_W, bytes, 1);
    i2c.read(HMC5883_ADDRESS_R, bytes, 6);

    for (int i=0;i<3;++i) {
        data[i] = (int)bytes[2*i + 1] + (((int)bytes[2*i]) << 8);
    }
}

#endif