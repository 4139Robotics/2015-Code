/*
 *  Input.cpp
 *  	Sends out various inputs from the controller and sensors..
 *
 *  FRC Team 4139 - Easy as Pi
 *  	Author(s): Derek Ta
 */

#include "WPILib.h"
#include "X360Controller.cpp"
#include "Sensors.cpp"

struct Input_In
{

};

struct Input_Out
{
	// X360Controller
	float returnX, returnY, returnRotation;
	bool returnTurboMode;
	float returnLiftAmount;
	float returnLiftActive, returnLiftManualControl;
	int returnLiftState;

	// Sensors
    float returnGyroAngle;
    float returnAccelX, returnAccelY, returnAccelZ;
    float returnDistance;
    bool returnUpperLiftSwitch, returnLowerLiftSwitch;
};

class Input
{
private:
	X360Controller* controller;
	Sensors* sensors;

public:
	Input()
	{
		controller = new X360Controller();
		sensors = new Sensors();
	}

	Input_Out Run(Input_In input)
	{
		//Declaring all necessary structs
		Input_Out output;

		X360Controller_In xbIn;
		X360Controller_Out xbOut;
		Sensors_In sensIn;
		Sensors_Out sensOut;

		sensIn.resetGyro = xbOut.returnResetGyro;

		//Running to obtain necessary information
		sensOut = sensors->Run(sensIn);
		xbOut = controller->Run(xbIn);

		// Controller info
		output.returnX = xbOut.returnX;
		output.returnY = xbOut.returnY;
		output.returnRotation = xbOut.returnRotation;
		output.returnTurboMode = xbOut.returnTurboMode;
		output.returnLiftAmount = xbOut.returnLiftAmount;
		output.returnLiftActive = xbOut.returnLiftActive;
		output.returnLiftManualControl = xbOut.returnLiftManualControl;
		output.returnLiftState = xbOut.returnLiftState;

		//Sensor info
		output.returnGyroAngle = sensOut.returnGyroAngle;
		output.returnAccelX = sensOut.returnAccelX;
		output.returnAccelY = sensOut.returnAccelY;
		output.returnAccelZ = sensOut.returnAccelZ;
		output.returnDistance = sensOut.returnDistance;
		output.returnUpperLiftSwitch = sensOut.returnUpperLiftSwitch;
		output.returnLowerLiftSwitch = sensOut.returnLowerLiftSwitch;

		return output;
	}
};
