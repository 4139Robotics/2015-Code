#include "WPILib.h"
#include "gyro.cpp"
#include "BuiltInAccelerometer.h"
#include <DigitalInput.h>

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
    GyroSensor* gyro;
    Accelerometer *accel;
    DigitalInput *UpperLift;
    DigitalInput *LowerLift;
    
public:
    Sensors() {
        gyro = new GyroSensor();
        accel = new BuiltInAccelerometer(Accelerometer:kRange_4G);
        UpperLift = new DigitalInput(uint32_t 9999);
        LowerLift = new DigitalInput(uint32_t 9999);
        
    }
    Sensor_Output Run(Sensor_Input input) {
        Sensors_Output out;
        
        out.returnGyroAngle = gyro->GetAngle();
        out.returnAccelX = accel->GetX();
        out.returnAccelY = accel->GetY();
        out.returnAccelZ = accel->GetZ();
        out.returnUpperLiftSwitch = UpperLift->Get();
        out.returnLowerLiftSwitch = LowerLift ->Get();
        return out;
    }
    
    
}