/*This file conbine all the config value*/

//Acceleration
tSensors AccelSensorPort[3] = {x,y,z};//The port
const int waitTime_Accel = 25;

//Kalman,which small which side
const float Estimate_error[3] = {0.07,0.07,0.07};
const float Sensor_error[3] = {0.8,0.8,0.8};

//Transfer to Actual Accel
const float Gravitational_Acceleration_Virtual[3] = {135,135,135};
const float Gravitational_Acceleration_Real[3] = {9.8,9.8,9.8};

//if the vary more than the hitlimit, ishitting return true
float hitlimit[3] = {0.1,10,0.1};//A Limit of Hitting

//ArcadeDrive
const short thresold_drive = 10;

//Gear
short gearRatio = 5;

//PID
#define PIDControl

const float MaxVoltage = sqrt(2)/2;
const float Target_RPM[2] = {150,150};
const float Tolerance_RPM[2] = {2,2};
const float Kp_RPM[2] = {33,33};
const float Ki_RPM[2] = {45,45};
const float Td_RPM[2] = {60,60};

const float Target_Position[4] = {150,150,150,150};
const float Tolerance_Position[4] = {2,2,2,2};
const float MaxOutput_PWM[4] = {MaxVoltage,MaxVoltage,MaxVoltage,MaxVoltage};
const float MinOutput_PWM[4] = {0.1,0.1,0.1,0.1};
const float Kp_Position[4] = {5,5,5,5};
const float Ki_Position[4] = {0,0,0,0};
const float Td_Position[4] = {0,0,0,0};

//Encoder
#define Encoder_Num 2
tSensors EncoderPort[Encoder_Num] = {left,right};
const int waitTime_RPM = 10;
