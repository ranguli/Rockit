#include "KalmanFilter.h"

const float R = 0.3;         //R = measurement noise covariance. Larger R means large measurement uncertainty
const float Q = 0.3 * 1e-2;  //Q = process noise covariance. Larger Q means larger estimation uncertainty. Thus increasing Q corrects more

// Performs a Kalman filter of the flight data. It smoothens the data and ignores transitory events.
// Z = measured signal at t = 0
float kalmanFilter(float Z) {

  static double Xe1;        // Xe1 = estimation of X at time t=1 (previous state)
  static double P1;         // P1 = error covariance at t=1

  double Xpe0 = Xe1;                   // Assumption of prediction 1
  double Ppe0 = P1 + Q;                // Update of prior estimation of "error covariance"
  double K = Ppe0 / (Ppe0 + R);        // Measurement update or correction of "Kalman gain"
  double Xe0 = Xpe0 + K * (Z - Xpe0);  // Measurement update or correction of "estimated signal"
  double P0 = (1 - K) * Ppe0;          // Measurement update or correction of "error covariance";

  Xe1 = Xe0;
  P1 = P0;
  
  return Xe0;
}
