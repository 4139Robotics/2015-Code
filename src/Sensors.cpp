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
    Gyro *gyro;
    Accelerometer *accel;
    DigitalInput *UpperLift;
    DigitalInput *LowerLift;
    Ultrasonic *Sanic;
    
public:
    Sensors()
	{
        gyro = new Gyro(999);
        accel = new BuiltInAccelerometer(Accelerometer::kRange_4G);
        UpperLift = new DigitalInput(998);
        LowerLift = new DigitalInput(997);
        Sanic = new Ultrasonic(999,999);
    }

    Sensors_Out Run(Sensors_In input)
    {
        Sensors_Out out;
        
        out.returnGyroAngle = gyro->GetAngle();
        out.returnAccelX = accel->GetX();
        out.returnAccelY = accel->GetY();
        out.returnAccelZ = accel->GetZ();
        out.returnUpperLiftSwitch = UpperLift->Get();
        out.returnLowerLiftSwitch = LowerLift ->Get();
        out.returnDistance = Sanic -> GetRangeInches();

        return out;
    }
};
