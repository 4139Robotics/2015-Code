/*
 * Sensors.cpp
        Sends various data from the sensors
 *
 *  FRC Team 4139 - Easy as Pi
 *      Author(s): Rhea Bae & Jeffrey Chen
 */

#include "WPILib.h"


struct Sensors_In
{
    
};

struct Sensors_Out
{
    float returnGyroAngle;
    float returnAccelX, returnAccelY, returnAccelZ;
    float returnDistance;
    bool returnUpperLiftSwitch, returnLowerLiftSwitch;
    
    
};

class Sensors
{
private:
    GyroSensor *gyro;
    Accelerometer *accel;
    DigitalInput *UpperLift;
    DigitalInput *LowerLift;
    Ultrasonic *Sanic;
    
public:
    Sensors() {
        gyro = new GyroSensor();
        accel = new BuiltInAccelerometer(Accelerometer:kRange_4G);
        UpperLift = new DigitalInput(uint32_t 9999);
        LowerLift = new DigitalInput(uint32_t 9999);
        Sanic = new Ultrasonic(ULTRASONIC_ECHO_PULSE_OUTPUT,ULTRASONIC_TRIGGER_PULSE_INPUT);
    }
    Sensor_Output Run(Sensor_Input input) {
        Sensors_Output out;
        
        out.returnGyroAngle = gyro->GetAngle();
        out.returnAccelX = accel->GetX();
        out.returnAccelY = accel->GetY();
        out.returnAccelZ = accel->GetZ();
        out.returnUpperLiftSwitch = UpperLift->Get();
        out.returnLowerLiftSwitch = LowerLift ->Get();
        out.returnDistance = Sanic -> GetRangeInches();
        return out;
    }
    
    
}
