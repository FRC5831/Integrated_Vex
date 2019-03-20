float motor_rpm[Encoder_Num];

task Task_Encoder(){
	while(true){
		for(int i=0;i<=Encoder_Num-1;i++){
			int first = SensorValue[EncoderPort[i]];
			wait1Msec(waitTime_RPM);
			motor_rpm[i] = (SensorValue[EncoderPort[i]]-first)*gearRatio*1000*60/360;//if encoder set up outside, gearRatio no need
		}
	}
}
