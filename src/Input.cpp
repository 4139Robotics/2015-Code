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

struct Input_In
{
	//
};

struct Input_Out
{
	// X360Controller
	float returnX, returnY, returnRotation;
	bool returnRotate;

	// Sensors
	float returnGyroAngle;
	float returnAccelX, returnAccelY, returnAccelZ;
	float returnDistance;
};

class Input
{


};
