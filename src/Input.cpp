/*
 *  Input.cpp
 *  	Sends out various inputs from the controller and sensors..
 *
 *  FRC Team 4139 - Easy as Pi
 *  	Author(s):
 */

#include "WPILib.h"
#include "X360Controller.cpp"
#include "Sensors.cpp"
#include "Input.h"

static Input_Out Input::Run(const Input_In& input)
{
    Input_Out output;


    //Receiving information from the controller and sensor and returning a struct populated with this info
    output.returnGyroAngle = input.sensout.returnGyroAngle;//Sensor info
    output.returnAccelX = input.sensout.returnAccelX;
    output.returnAccelY = input.sensout.returnAccelY;
    output.returnAccelZ = input.sensout.returnAccelZ;
    output.returnDistance = input.sensout.returnDistance;
    output.returnX = input.xbout.returnX;//Xbox controller info
    output.returnY = input.xbout.returnY;
    output.returnRotation = input.xbout.returnRotation;
    output.returnRotate = input.xbout.returnRotate;

    return output;
}
