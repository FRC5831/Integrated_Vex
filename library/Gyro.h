long nNumbOfADCConversionCycles = 0; // Performed by special debugging hook in firmware

long nCycles = 0;
long nElapsedTime;

long nFilteredRawValueSum = 0;

long nGyroValue;
volatile long nFilteredRawValue;
long nNonJitterCycles = 0;

typedef enum TCountsIndices
{
  biasMinus6orLess,
  biasMinus5,
  biasMinus4,
  biasMinus3,
  biasMinus2,
  biasMinus1,
  bias,
  biasPlus1,
  biasPlus2,
  biasPlus3,
  biasPlus4,
  biasPlus5,
  biasPlus6orMore,
} TCountsIndices;

long nGyroRawAnalogValue;
long nGyroBias;
long nSensorSmallBias; // Performed by special debugging hook in firmware
long nGyroSensorScale;
long nGyroFullCount;
long nCounts[(TCountsIndices) 13];
short nMaxValueCurr10Seconds;
short nMinValueCurr10Seconds;
short nPrev10SecondTime = -1;
short nCurr10SecondTime;
const int kHistogramSize = 600;
short nMaxValues[kHistogramSize];
short nMinValues[kHistogramSize];
long nLoopStartTime;
long nPrevTime;
long nCurrTime;

const int kJitterIgnoreRange = 4;

task Task_Gyro()
{
	// Firmware retains sensor type setting between invocations of program. Explicitly setting to 'sensorNone' and
  // then back to 'sensorGyro' will explicitly force the firmware driver to recalculate the biase settings. Which
  // you may want to do via the Debugger's "STOP" and "START" buttons.

  SensorType[gyro] = sensorNone;
  SensorType[gyro] = sensorGyro;

  memset(&nCounts[0], 0, sizeof(nCounts));
  memset(&nMaxValues, 0, sizeof(nMaxValues));
  memset(&nMinValues, 0, sizeof(nMinValues));
  nNumbOfADCConversionCycles = 0;
  nFilteredRawValueSum = 0;
  while (SensorBias[gyro] == 0)
  {}
  SensorValue[gyro] = 0;

  nGyroBias           = SensorBias[gyro];
  nSensorSmallBias    = SensorSmallBias[gyro];
  nGyroSensorScale    = SensorScale[gyro];
  nGyroFullCount      = SensorFullCount[gyro];

  nLoopStartTime = nPgmTime;
  while (true)
  {
    short nDifference;
    ++nCycles;
		nGyroValue          = SensorValue[gyro];
    nGyroRawAnalogValue = getSensorRawADValue(gyro);

    nDifference         = nGyroRawAnalogValue - nGyroBias;
    if ((nDifference < -kJitterIgnoreRange) || (nDifference > +kJitterIgnoreRange))
    {
      nFilteredRawValueSum += nDifference;
      ++nNonJitterCycles;
	    if ((nNonJitterCycles % 1024) == 0)
	      nFilteredRawValueSum -= nSensorSmallBias;
	  }
	  if (nDifference < -6)
	    nDifference = -6;
	  else if (nDifference > +6)
	    nDifference = +6;
	  ++nCounts[bias + nDifference];

    nFilteredRawValue   = nFilteredRawValueSum / nGyroSensorScale;

    // Calculate statistics and value histogram

		nCurrTime = nPgmTime;
		nElapsedTime        = nCurrTime - nLoopStartTime;
		nCurr10SecondTime		= nElapsedTime / 10000;
		if (nCurr10SecondTime != nPrev10SecondTime)
		{
			if (nPrev10SecondTime >= 0)
			{
				nMaxValues[nPrev10SecondTime] = nMaxValueCurr10Seconds;
				nMinValues[nPrev10SecondTime] = nMinValueCurr10Seconds;
			}
			nMaxValueCurr10Seconds = nGyroValue;
			nMinValueCurr10Seconds = nGyroValue;
		}
		if (nGyroValue > nMaxValueCurr10Seconds)
			nMaxValueCurr10Seconds = nGyroValue;
		else if (nGyroValue < nMinValueCurr10Seconds)
			nMinValueCurr10Seconds = nGyroValue;
		nPrev10SecondTime = nCurr10SecondTime;

		while (nCurrTime == nPrevTime)
		{
		  nCurrTime = nPgmTime;
		}
		nPrevTime = nCurrTime;
    //wait1Msec(1);
  }
}
