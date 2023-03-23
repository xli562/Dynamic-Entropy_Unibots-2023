#include <Adafruit_LSM6DS3TRC.h>  // The IMU library
#include <Unit_Sonic.h>           // The sonic sensor library
#define PCA_ADDR 0x70             // Address of the multiplexer


Adafruit_LSM6DS3TRC lsm6ds3trc;   // The IMU instance
SONIC_I2C sonic;                  // The sonic sensor instance


void setup(void) {
  Serial.begin(115200);
  // Wait for serial communication to open
  while (!Serial){delay(10);}
  delay(1000);
  sonic.begin();
  setupIMU();
}

void loop() {
  readIMU(true);
  Serial.print(", ");
  Serial.print(sonicValue(4));
  Serial.print(", ");
  Serial.println(sonicValue(7));
  delay(100);
}

void pca_select(uint8_t i) {
  if (i <= 7) {
    Wire.beginTransmission(PCA_ADDR);
    // The number one shifted left i times, i.e. 1*2^i. Shifting left is faster than performing the n^i operation.
    Wire.write(1 << i);           
    Wire.endTransmission();
  }
}

void setupIMU() {       // Specifying the port every time is convenient, but might slightly slow down the function. Consider moving the pca_select() out if calling repeatedly.
  if (!lsm6ds3trc.begin_I2C()) {
    Serial.println("Failed to find LSM6DS3TR-C chip");
    while (1) {
      delay(100);
    }
  }

  Serial.println("LSM6DS3TR-C Found!");
  for(int i = 0; i < 1; i ++) {
    // lsm6ds3trc.setAccelRange(LSM6DS_ACCEL_RANGE_2_G);
    Serial.print("Accelerometer range set to: ");
    switch (lsm6ds3trc.getAccelRange()) {
    case LSM6DS_ACCEL_RANGE_2_G:
      Serial.println("+-2G");
      break;
    case LSM6DS_ACCEL_RANGE_4_G:
      Serial.println("+-4G");
      break;
    case LSM6DS_ACCEL_RANGE_8_G:
      Serial.println("+-8G");
      break;
    case LSM6DS_ACCEL_RANGE_16_G:
      Serial.println("+-16G");
      break;
    }

    // lsm6ds3trc.setGyroRange(LSM6DS_GYRO_RANGE_250_DPS);
    Serial.print("Gyro range set to: ");
    switch (lsm6ds3trc.getGyroRange()) {
    case LSM6DS_GYRO_RANGE_125_DPS:
      Serial.println("125 degrees/s");
      break;
    case LSM6DS_GYRO_RANGE_250_DPS:
      Serial.println("250 degrees/s");
      break;
    case LSM6DS_GYRO_RANGE_500_DPS:
      Serial.println("500 degrees/s");
      break;
    case LSM6DS_GYRO_RANGE_1000_DPS:
      Serial.println("1000 degrees/s");
      break;
    case LSM6DS_GYRO_RANGE_2000_DPS:
      Serial.println("2000 degrees/s");
      break;
    case ISM330DHCX_GYRO_RANGE_4000_DPS:
      break; // unsupported range for the DS33
    }

    // lsm6ds3trc.setAccelDataRate(LSM6DS_RATE_12_5_HZ);
    Serial.print("Accelerometer data rate set to: ");
    switch (lsm6ds3trc.getAccelDataRate()) {
    case LSM6DS_RATE_SHUTDOWN:
      Serial.println("0 Hz");
      break;
    case LSM6DS_RATE_12_5_HZ:
      Serial.println("12.5 Hz");
      break;
    case LSM6DS_RATE_26_HZ:
      Serial.println("26 Hz");
      break;
    case LSM6DS_RATE_52_HZ:
      Serial.println("52 Hz");
      break;
    case LSM6DS_RATE_104_HZ:
      Serial.println("104 Hz");
      break;
    case LSM6DS_RATE_208_HZ:
      Serial.println("208 Hz");
      break;
    case LSM6DS_RATE_416_HZ:
      Serial.println("416 Hz");
      break;
    case LSM6DS_RATE_833_HZ:
      Serial.println("833 Hz");
      break;
    case LSM6DS_RATE_1_66K_HZ:
      Serial.println("1.66 KHz");
      break;
    case LSM6DS_RATE_3_33K_HZ:
      Serial.println("3.33 KHz");
      break;
    case LSM6DS_RATE_6_66K_HZ:
      Serial.println("6.66 KHz");
      break;
    }

    // lsm6ds3trc.setGyroDataRate(LSM6DS_RATE_12_5_HZ);
    Serial.print("Gyro data rate set to: ");
    switch (lsm6ds3trc.getGyroDataRate()) {
    case LSM6DS_RATE_SHUTDOWN:
      Serial.println("0 Hz");
      break;
    case LSM6DS_RATE_12_5_HZ:
      Serial.println("12.5 Hz");
      break;
    case LSM6DS_RATE_26_HZ:
      Serial.println("26 Hz");
      break;
    case LSM6DS_RATE_52_HZ:
      Serial.println("52 Hz");
      break;
    case LSM6DS_RATE_104_HZ:
      Serial.println("104 Hz");
      break;
    case LSM6DS_RATE_208_HZ:
      Serial.println("208 Hz");
      break;
    case LSM6DS_RATE_416_HZ:
      Serial.println("416 Hz");
      break;
    case LSM6DS_RATE_833_HZ:
      Serial.println("833 Hz");
      break;
    case LSM6DS_RATE_1_66K_HZ:
      Serial.println("1.66 KHz");
      break;
    case LSM6DS_RATE_3_33K_HZ:
      Serial.println("3.33 KHz");
      break;
    case LSM6DS_RATE_6_66K_HZ:
      Serial.println("6.66 KHz");
      break;
    }

  }
  lsm6ds3trc.configInt1(false, false, true); // accelerometer DRDY on INT1
  lsm6ds3trc.configInt2(false, true, false); // gyro DRDY on INT2
}

void readIMU(bool useSerialPlotter) {   // if useSerialPlotter == true, returns a format 
  // Get a new normalized sensor event
  sensors_event_t accel;
  sensors_event_t gyro;
  sensors_event_t temp;
  lsm6ds3trc.getEvent(&accel, &gyro, &temp);

  // if not using the serial plotter to visulise data
  if (useSerialPlotter == false) {
    Serial.print("\t\tTemperature ");
    Serial.print(temp.temperature);
    Serial.println(" deg C");

    /* Display the results (acceleration is measured in m/s^2) */
    Serial.print("\t\tAccel X: ");
    Serial.print(accel.acceleration.x);
    Serial.print(" \tY: ");
    Serial.print(accel.acceleration.y);
    Serial.print(" \tZ: ");
    Serial.print(accel.acceleration.z);
    Serial.println(" m/s^2 ");

    /* Display the results (rotation is measured in rad/s) */
    Serial.print("\t\tGyro X: ");
    Serial.print(gyro.gyro.x);
    Serial.print(" \tY: ");
    Serial.print(gyro.gyro.y);
    Serial.print(" \tZ: ");
    Serial.print(gyro.gyro.z);
    Serial.println(" radians/s ");
    Serial.println();
  }
  else {
    //=serial plotter friendly format

    Serial.print(temp.temperature);
    Serial.print(",");

    Serial.print(accel.acceleration.x);
    Serial.print(","); Serial.print(accel.acceleration.y);
    Serial.print(","); Serial.print(accel.acceleration.z);
    Serial.print(",");

   Serial.print(gyro.gyro.x);
   Serial.print(","); Serial.print(gyro.gyro.y);
   Serial.print(","); Serial.print(gyro.gyro.z);
  }
}

float sonicValue(uint8_t port) {
  pca_select(port);
  return sonic.reading();
}