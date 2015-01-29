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
	float returnX, returnY, returnRotation;
	bool returnRotate;
};

class X360Controller
{
private:
	Joystick* UDLR;
	X360Controller_Out Output;
	float rightAnalogX,
		  leftAnalogX,
		  rightAnalogY,
		  leftAnalogY;



public:

	X360Controller::X360Controller()
	{
		UDLR = new Joystick(1);
		leftAnalogX=UDLR->GetRawAxis(0);
		leftAnalogY=UDLR->GetRawAxis(1);
		rightAnalogX=UDLR->GetRawAxis(4);
		rightAnalogY=UDLR->GetRawAxis(5);
	}
	X360Controller_Out X360Controller::Run(X360Controller_In input)
	{


		return Output;
	}

};
