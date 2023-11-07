#include <Wire.h>
#define MPU_ADDR 0x68
#define A 0.962
#define dt 0.020

int x, y;

long accel_x, accel_y, accel_z;
long gyro_x, gyro_y, gyro_z;

double calc_accx, calc_accy, calc_accz;
double calc_gyx, calc_gyy, calc_gyz;

float roll_angle, pitch_angle;
float roll,pitch,yaw;

void setup() {
  Wire.begin();
  Serial.begin(115200);

  connectMPU();
  calibrate();
}

void loop() {  
  readRawAccel();
  readRawGyro();
  calcLSB();

  roll_angle = atan2(accel_x, accel_z) * 180 / PI; // FORMULA DPT DI INET
  pitch_angle = atan2(accel_x, sqrt(accel_y * accel_y + accel_z * accel_z)) * 180 / PI;

  // FILTER COMPLEMENTARY
  roll = A * (roll + gyro_x * dt) + (1 - A) * roll_angle;
  pitch = A * (pitch + gyro_y * dt) + (1 - A) * pitch_angle;
  yaw = gyro_z;

  printData();
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

  // AKSES REGISTER ACCEL_CONFIG
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x1C);
  Wire.write(0b00000000);

  // AKSES REGISTER GYRO_CONFIG
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
    if (x == 2000) accel_x -= calc_accx;
    accel_y = Wire.read() << 8 | Wire.read();
    if (x == 2000) accel_y -= calc_accy;
    accel_z = Wire.read() << 8 | Wire.read();
    if (x == 2000) accel_z -= calc_accz;
//  }
}

void calcLSB() {
  accel_x = accel_x / 16384;
  accel_y = accel_x / 16384;
  accel_z = accel_x / 16384;

  gyro_x = gyro_x / 131;
  gyro_y = gyro_y / 131;
  gyro_z = gyro_z / 131;
}

void readRawGyro() {
  bacaByte(MPU_ADDR, 0x3B, 6);
//  Wire.beginTransmission(MPU_ADDR);
//  Wire.write(0x3B); // mulai pembacaan accel
//  Wire.endTransmission();
//  while (Wire.available() < 6) {
//    Wire.requestFrom(MPU_ADDR, 6);
    gyro_x = Wire.read() << 8 | Wire.read();
    if (y == 2000) gyro_x -= calc_gyx;
    gyro_y = Wire.read() << 8 | Wire.read();
    if (y == 2000) gyro_y -= calc_gyy;
    gyro_z = Wire.read() << 8 | Wire.read();
    if (y == 2000) gyro_z -= calc_gyz;
//  }
}

void calibrate() {
  Serial.println("Calibrating Accelerometer");
  for (x = 0; x < 2000; x++) {
    readRawAccel();
    calc_accx += accel_x;
    calc_accy += accel_y;
    calc_accz += accel_z;
  }
  Serial.println("Calibrating Gyrometer");
  for (y = 0; y < 2000; y++) {
    readRawGyro();
    calc_gyx += gyro_x;
    calc_gyy += gyro_y;
    calc_gyz += gyro_z;
  }
  Serial.println("Calibrating Done");

  calc_accx /= 2000;
  calc_accy /= 2000;
  calc_accz /= 2000;

  calc_gyx /= 2000;
  calc_gyy /= 2000;
  calc_gyz /= 2000;
}

void printData() {
  Serial.print(" Roll = ");
  Serial.print(roll);
  Serial.print(" angle");
  Serial.print("    Pitch = ");
  Serial.print(pitch);
  Serial.print(" angle");
  Serial.print("    Yaw = ");
  Serial.print(yaw);
  Serial.println(" deg/s");
}
