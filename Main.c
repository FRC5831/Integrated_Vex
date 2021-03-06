#pragma config(Sensor, in1,    x,              sensorAccelerometer)
#pragma config(Sensor, in2,    y,              sensorAccelerometer)
#pragma config(Sensor, in3,    z,              sensorAccelerometer)
#pragma config(Sensor, in8,    gyro,           sensorGyro)
#pragma config(Sensor, dgtl1,  left,           sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  right,          sensorQuadEncoder)
#pragma config(Motor,  port1,           L1,            tmotorVex393HighSpeed_HBridge, openLoop, reversed, driveLeft)
#pragma config(Motor,  port2,           L2,            tmotorVex393HighSpeed_MC29, openLoop, driveLeft)
#pragma config(Motor,  port3,           L3,            tmotorVex393HighSpeed_MC29, openLoop, reversed, driveLeft)
#pragma config(Motor,  port4,           R1,            tmotorVex393HighSpeed_MC29, openLoop, driveRight)
#pragma config(Motor,  port5,           R2,            tmotorVex393HighSpeed_MC29, openLoop, reversed, driveRight)
#pragma config(Motor,  port10,          R3,            tmotorVex393HighSpeed_HBridge, openLoop, driveRight)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include"library/Config.c"
#include"library/Acceleration.h"
#include"library/ArcadeDrive.h"
#include"library/Gyro.h"

task main()
{
	startTask(Task_AccelSensor);
	startTask(Task_Gyro);
	startTask(Task_ArcadeControl);
}
