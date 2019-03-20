#ifdef PIDControl
#include"PIDController.h"
#include"Encoder.h"
#include"ArcadeDrive.c"
#endif

task Task_ArcadeControl{
	while(true){
#ifdef PIDControl
		startTask(Task_Encoder);
		startTask(Task_PIDControl);
		ArcadeDrive(Ch3,Ch1,thresold_drive);
#else
		arcadeControl(Ch3,Ch1,thresold_drive);
#endif
	}
}
