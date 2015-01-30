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
	Joystick* Stick;
	X360Controller_Out Output;
	float leftAnalogX,
		  leftAnalogY,
		  rightAnalogX,
		  rightAnalogY;



public:

	X360Controller()
	{
		Stick = new Joystick(1);
		leftAnalogX = Stick->GetRawAxis(0);
		leftAnalogY = Stick->GetRawAxis(1);
		rightAnalogX= Stick->GetRawAxis(4);
		rightAnalogY= Stick->GetRawAxis(5);
	}
	X360Controller_Out Run(X360Controller_In input)
	{


		return Output;
	}

};
