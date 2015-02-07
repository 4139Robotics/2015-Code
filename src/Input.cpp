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
	bool returnRotateCCW, returnRotateCW;
	bool returnTurboMode;

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


	/*
	Input::~Input()
	{
    	delete controller;
    	delete sensors;
	}
	 */

	Input_Out Run(Input_In input)
	{
		//Declaring all necessary structs
		Input_Out output;
		X360Controller_In xbIn;
		X360Controller_Out xbOut;
		Sensors_In sensIn;
		Sensors_Out sensOut;

		//Running to obtain necessary information
		sensOut = sensors->Run(sensIn);
		xbOut = controller->Run(xbIn);

		//Receiving information from the controller and sensor and returning a struct populated with this info
		output.returnX = xbOut.returnX;
		output.returnY = xbOut.returnY;
		output.returnRotation = xbOut.returnRotation;
		output.returnRotateCCW = xbOut.returnRotateCCW;
		output.returnRotateCW = xbOut.returnRotateCW;
		output.returnTurboMode = xbOut.returnTurboMode;

		output.returnGyroAngle = sensOut.returnGyroAngle; //Sensor info
		output.returnAccelX = sensOut.returnAccelX;
		output.returnAccelY = sensOut.returnAccelY;
		output.returnAccelZ = sensOut.returnAccelZ;
		output.returnDistance = sensOut.returnDistance;
		output.returnUpperLiftSwitch = sensOut.returnUpperLiftSwitch;
		output.returnLowerLiftSwitch = sensOut.returnLowerLiftSwitch;

		return output;
	}
};
