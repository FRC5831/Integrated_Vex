struct PIDController{
	float Input;
	//Setting
	float Kp;
	float Ki;
	float Td;
	float Target;
	float Max;
	float Min;
	float Tolerance;
	//Display
	bool OnTarget;
	//loop value
	float Error;
	float LastError;
	float Error_Integral;
};

void InitPIDController(PIDController *pidcontroller,void *kp,void *ki,void *td,void *tolerance,int size);
float PIDOutput(PIDController pidcontroller,float current,float target);
void SetLimitOutput(PIDController *pidcontroller,void *max,void *min,int size);
void ResetPIDController(PIDController pidcontroller);

void InitPIDController(PIDController *pidcontroller,void *kp,void *ki,void *td,void *tolerance,int size){
	for(int i=0;i<=size-1;i++){
		pidcontroller[i].Kp = (float)kp[i];
		pidcontroller[i].Ki = (float)ki[i];
		pidcontroller[i].Td = (float)td[i];
		pidcontroller[i].Tolerance = (float)tolerance[i];
	}
}

float PIDOutput(PIDController pidcontroller,float current,float target){
	pidcontroller.Input = current;
	pidcontroller.Target = target;
	pidcontroller.Error = pidcontroller.Target - current;
	float Output = (pidcontroller.Kp*(pidcontroller.Error+pidcontroller.Ki*pidcontroller.Error_Integral+pidcontroller.Td*(pidcontroller.Error-pidcontroller.LastError)))/pidcontroller.Target;
	pidcontroller.LastError = pidcontroller.Error;
	pidcontroller.Error_Integral += pidcontroller.Error;
	pidcontroller.OnTarget = pidcontroller.Tolerance>=abs(pidcontroller.Error);
	if(Output<pidcontroller.Min)Output = 0;
	else if(Output>pidcontroller.Max)Output = pidcontroller.Max;
	return Output;
}

void SetLimitOutput(PIDController *pidcontroller,void *max,void *min,int size){
	for(int i=0;i<=size-1;i++){
		pidcontroller[i].Max = (float)max[i];
		pidcontroller[i].Min = (float)min[i];
	}
}

void ResetPIDController(PIDController pidcontroller){
	pidcontroller.Error_Integral = 0;
}
