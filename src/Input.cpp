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
	bool returnRotate;

	// Sensors
	float returnGyroAngle;
	float returnAccelX, returnAccelY, returnAccelZ;
	float returnDistance;
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
		X360Controller_In xbin;
		X360Controller_Out xbout;
		Sensors_In sensin;
		Sensors_Out sensout;

		//Running to obtain necessary information
		sensout = sensors->Run(sensin);
		xbout = controller->Run(xbin);


		//Receiving information from the controller and sensor and returning a struct populated with this info
		output.returnGyroAngle = sensout.returnGyroAngle;//Sensor info
		output.returnAccelX = sensout.returnAccelX;
		output.returnAccelY = sensout.returnAccelY;
		output.returnAccelZ = sensout.returnAccelZ;
		output.returnDistance = sensout.returnDistance;
		output.returnX = xbout.returnX;//Xbox controller info
		output.returnY = xbout.returnY;
		output.returnRotation = xbout.returnRotation;
		output.returnRotate = xbout.returnRotate;

		return output;
	}
};
