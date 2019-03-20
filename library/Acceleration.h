#define Kalman_filter//Open the kalman filter or not
#define Limit_Filter//Open the Limit Filter
#define Kalman_Debug//Open the graph drawiing

#include"Acceleration.c"

AccelSensor accelsensor;

#ifdef Kalman_Debug
task Task_DrawGraph_Acceleration{
	datalogClear();
	while(true){
		datalogDataGroupStart();
		datalogAddValue(0,accelsensor.AccelValue[0]);
		datalogAddValue(1,accelsensor.AccelValue[1]);
		datalogAddValue(2,accelsensor.AccelValue[2]);
		datalogDataGroupEnd();
	}
}
#endif

task Task_AccelSensor{
#ifdef Kalman_Debug
	startTask(Task_DrawGraph_Acceleration);
#endif
	InitAccelSensor(accelsensor,AccelSensorPort);
	SetHitLimit(accelsensor,hitlimit);
	while(true){
		GetAccelValue(accelsensor);
	}
}
