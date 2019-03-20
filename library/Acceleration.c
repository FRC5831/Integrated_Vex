/*This file combine the acceleration calculate*/
#include"Kalman_filter.c"
/*--------public---------*/
struct AccelSensor{
	float AccelValue[3];
	//hit setting
	float AccelVary[3];
	bool Ishitting[3];
	float *Hitlimit;
	float HitRate[3];
	//init setting
	float Bias[3];
	tSensors *Port;
	//loop value
	float LastAccel[3];
	float LastVary[3];
	//kalman
#ifdef Kalman_filter
	Kalman kalman[3];
#endif
};
void InitAccelSensor(AccelSensor accelsensor,tSensors *AccelSensorPort);
void GetAccelValue(AccelSensor accelsensor);
void SetHitLimit(AccelSensor accelsensor,void *hitlimit);

/*--------define---------*/
void InitAccelSensor(AccelSensor accelsensor,tSensors *AccelSensorPort){
	accelsensor.Port = AccelSensorPort;
	for(int i=0;i<=2;i++){
		accelsensor.Bias[i] = SensorValue[accelsensor.Port[i]];
#ifdef Kalman_filter
		SetFilter(accelsensor.kalman[i],Estimate_error[i],Sensor_error[i]);
#endif
	}
}

void SetHitLimit(AccelSensor accelsensor,void *hitlimit){
	accelsensor.Hitlimit = (float*)hitlimit;
}

void GetAccelValue(AccelSensor accelsensor){
	for(int i=0;i<=2;i++){
		accelsensor.AccelValue[i] = SensorValue[accelsensor.Port[i]]-accelsensor.Bias[i];
#ifdef Kalman_filter
		Filter_function(accelsensor.kalman[i],accelsensor.AccelValue[i]);
		accelsensor.AccelValue[i] = accelsensor.kalman[i].Filter_value;
#endif
		accelsensor.AccelVary[i] = accelsensor.AccelValue[i]-accelsensor.LastAccel[i];
		accelsensor.HitRate[i] = accelsensor.AccelVary[i]-accelsensor.LastVary[i];
		accelsensor.Ishitting[i] = abs(accelsensor.HitRate[i])>accelsensor.Hitlimit[i];
		accelsensor.LastAccel[i] = accelsensor.AccelValue[i];
		accelsensor.LastVary[i] = accelsensor.AccelVary[i];
	}
	wait1Msec(waitTime_Accel);
}
