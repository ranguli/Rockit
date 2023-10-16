#ifndef ROCKIT_KALMAN_FILTER_H
#define ROCKIT_KALMAN_FILTER_H

// Kalman Variables

extern const float R;
extern const float Q;

float kalmanFilter(float Z);

#endif  // ROCKIT_KALMAN_FILTER_H
