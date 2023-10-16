#ifndef ROCKIT_LAUNCH_DETECTOR_H
#define ROCKIT_LAUNCH_DETECTOR_H

class LaunchDetector {
private:
    unsigned int accelerationThreshold;
    unsigned int altitudeThreshold;
    bool launched;
    bool checkAccelerationCondition(float acceleration);
    bool checkAltitudeCondition(float altitudeDelta);
public:
    void begin(const unsigned int accelerationThreshold, const unsigned int altitudeThreshold);
    bool launchDetected(const float acceleration, const float altitudeDelta);
};

#endif // ROCKIT_LAUNCH_DETECTOR_H
