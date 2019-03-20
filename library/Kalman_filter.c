#ifdef Kalman_filter
struct Kalman{
	float Filter_value;
	float Gaussian_error;
	float Estimate_error;
	float Sensor_error;
	float Last_error;
	float Last_value;
	float Kg;
};

void SetFilter(Kalman kalman,float estimate_error,float sensor_error){
	kalman.Estimate_error = estimate_error;
	kalman.Sensor_error = sensor_error;
}

void Filter_function(Kalman kalman,float Sensor_value){
	kalman.Gaussian_error = sqrt(pow(kalman.Last_error,2)+pow(kalman.Estimate_error,2));
  kalman.Kg = sqrt(pow(kalman.Gaussian_error,2)/(pow(kalman.Gaussian_error,2)+pow(kalman.Sensor_error,2)));
  kalman.Filter_value = kalman.Last_value+kalman.Kg*(Sensor_value-kalman.Last_value);
  kalman.Last_error = sqrt((1-kalman.Kg)*pow(kalman.Gaussian_error,2));
  kalman.Last_value = kalman.Filter_value;
}
#endif
