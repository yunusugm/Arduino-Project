#include <Wire.h>
#define MPU_ADDR 0x68

int x, y;

long accel_x, accel_y, accel_z;
long gyro_x, gyro_y, gyro_z;

double calc_accx, calc_accy, calc_accz;
double calc_gyx, calc_gyy, calc_gyz;

void setup() {
  Wire.begin();
  Serial.begin(115200);

  connectMPU();
}

void loop() {  
  readRawAccel();
  calcLSB();
}

 void bacaByte(uint8_t i, uint8_t j,uint8_t k) {
   Wire.beginTransmission(i);
   Wire.write(j);
   Wire.endTransmission();
   while(Wire.available() < k)
   Wire.requestFrom(i,k);
 }


void connectMPU() {
  // MULAI KOMUNIKASI DENGAN MPU
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);
  Wire.write(0b0000000);
  Wire.endTransmission(); 

  // AKSES
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x1C);
  Wire.write(0b00000000);

  // AKSES 
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x1B);
  Wire.write(0b00000000);
}

void readRawAccel() {
  bacaByte(MPU_ADDR, 0x3B, 6);
//  Wire.beginTransmission(MPU_ADDR);
//  Wire.write(0x3B); // mulai pembacaan accel
//  Wire.endTransmission();
//  while (Wire.available() < 6) {
//    Wire.requestFrom(MPU_ADDR, 6);
    accel_x = Wire.read() << 8 | Wire.read();
    accel_y = Wire.read() << 8 | Wire.read();
    accel_z = Wire.read() << 8 | Wire.read();

//  }
}

void calcLSB() {
  accel_x = accel_x / 16384;
  accel_y = accel_x / 16384;
  accel_z = accel_x / 16384;
}
