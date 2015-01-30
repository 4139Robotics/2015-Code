/*
 *  X360Controller.cpp
 *  	Takes in various user inputs and sends them out.
 *
 *  FRC Team 4139 - Easy as Pi
 *  	Author(s):
 */

#include "WPILib.h"

struct X360Controller_In
{
	//
};

struct X360Controller_Out
{
	float returnX,
		  returnY,
		  returnRotation;
	bool returnRotate;
};

class X360Controller
{
private:
	Joystick* stick;
	X360Controller_Out Output;
	float leftAnalogX,
		  leftAnalogY,
		  rightAnalogX,
		  rightAnalogY;



public:

	X360Controller()
	{
		stick = new Joystick(1);

	}
	X360Controller_Out Run(X360Controller_In input)
	{
		leftAnalogX = stick->GetRawAxis(0);
		leftAnalogY = stick->GetRawAxis(1);
		rightAnalogX= stick->GetRawAxis(4);
		rightAnalogY= stick->GetRawAxis(5);

		return Output;
	}

};
