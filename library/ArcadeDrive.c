void ArcadeDrive(TVexJoysticks verticalJoystick,TVexJoysticks horizontalJoystick,short threshold);

void ArcadeDrive(TVexJoysticks verticalJoystick,TVexJoysticks horizontalJoystick,short threshold){
	short nRightSideSpeed = 0;
	short nLeftSideSpeed = 0;
	if(abs(vexRT[verticalJoystick]) <= abs(threshold) && abs(vexRT[horizontalJoystick]) <= abs(threshold))
	{
		nRightSideSpeed = 0;
		nLeftSideSpeed = 0;
	}
	else
	{
		nRightSideSpeed = ((getJoystickValue(verticalJoystick) - getJoystickValue(horizontalJoystick)) / 2);
		nLeftSideSpeed = ((getJoystickValue(verticalJoystick) + getJoystickValue(horizontalJoystick)) / 2);
		if (nGlobalJoyScaledValue != nMaxJoyScaleValue)
		{
			nRightSideSpeed = nRightSideSpeed * (nGlobalJoyScaledValue / nMaxJoyScaleValue);
			nLeftSideSpeed = nLeftSideSpeed * (nGlobalJoyScaledValue / nMaxJoyScaleValue);
		}
	}
	setMotorSpeeds(PIDOutput(pid_speed[0],motor_rpm[0],Target_RPM[0]*nRightSideSpeed),PIDOutput(pid_speed[1],motor_rpm[1],Target_RPM[1]*nLeftSideSpeed));
}
