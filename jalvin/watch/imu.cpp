/// Module for display IMU data
/// Author: Alvin Lin (alvin@omgimanerd.tech)

#include <Adafruit_LSM9DS0.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_SSD1306.h>

#include "imu.h"

void displayIMU(Adafruit_SSD1306 display, Adafruit_LSM9DS0 lsm) {
  display.setTextSize(1);
  display.setCursor(0, 20);
  display.print("Accel: ");
  display.drawLine(0, 30, 45, 30, WHITE);
  display.setCursor(0, 35);
  display.print("X: "); display.print((int) lsm.accelData.x);
  display.setCursor(0, 45);
  display.print("Y: "); display.print((int) lsm.accelData.y);
  display.setCursor(0, 55);
  display.print("Z: "); display.print((int) lsm.accelData.z);
  display.setCursor(64, 20);
  display.print("Gyro: ");
  display.setCursor(64, 35);
  display.drawLine(64, 30, 109, 30, WHITE);
  display.print("X: "); display.print((int) lsm.gyroData.x);
  display.setCursor(64, 45);
  display.print("Y: "); display.print((int) lsm.gyroData.y);
  display.setCursor(64, 55);
  display.print("Z: "); display.print((int) lsm.gyroData.z);
  /*
  float heading = atan2(lsm.magData.y, lsm.magData.x);
  if(heading < 0)
  heading += 2*PI;
  if(heading > 2*PI)
    heading -= 2*PI;
  float headingDegrees = heading * 180/M_PI;

  display.setCursor(0,0);
  display.print(headingDegrees);
  */
  /*
  display.drawCircle(64, 32, 4, WHITE);
  display.fillCircle(((-(int)lsm.accelData.y)+1023)/16,((-(int)lsm.accelData.x)+1023)/32 * 2, 2, WHITE);
  */
  /*
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,20);
  display.print("Accel X: "); display.print(((int)lsm.accelData.y+1023)/16); display.print(" ");
  display.print("Y: "); display.print(((int)lsm.accelData.x+1023)/32);       display.print(" ");
  */
}
