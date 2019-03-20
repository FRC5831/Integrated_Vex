#define PIDControl_Debug

#include"PIDController.c"

PIDController pid_speed[2];
PIDController pid_position[2];

#ifdef PIDControl_Debug
task Task_DrawGraph_PID{
	datalogClear();
	while(true){
		datalogDataGroupStart();
		datalogAddValue(0,pid_speed.Input);
		datalogAddValue(1,pid_position.Input);
		datalogDataGroupEnd();
	}
}
#endif

task Task_PIDControl{
#ifdef PIDControl_Debug
	startTask(Task_DrawGraph_PID);
#endif
	InitPIDController(pid_speed,Kp_RPM,Ki_RPM,Td_RPM,Tolerance_RPM,2);
	InitPIDController(pid_position,Kp_Position,Ki_Position,Td_Position,Tolerance_Position,2);
	SetLimitOutput(pid_position,MaxOutput_PWM,MinOutput_PWM,2);
}
