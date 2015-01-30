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
	//rotation variables
	float returnRotation;
	bool returnRotate;

	//left and right analog sticks
	float leftAnalogX,
		  leftAnalogY,
		  rightAnalogX,
		  rightAnalogY;
	//buttons
	bool buttonA,
	     buttonB,
		 buttonX,
		 buttonY,
		 leftTrigger,
		 rightTrigger;
};

class X360Controller
{
private:
	Joystick* stick;
	X360Controller_Out Output;



public:

	X360Controller()
	{
		stick = new Joystick(1);
		//Output.returnX=0.0 //do some math in run
		//Output.returnY=0.0 //do some math in run
		//Output.returnRotation=0.0 //do some math in run
		Output.returnRotate=false;

	}
	X360Controller_Out Run(X360Controller_In input)
	{

		//setting sticks to general values
		Output.leftAnalogX = stick->GetRawAxis(0);
		Output.leftAnalogY = stick->GetRawAxis(1);
		Output.rightAnalogX= stick->GetRawAxis(4);
		Output.rightAnalogY= stick->GetRawAxis(5);

		//setting buttons to general functions
		Output.buttonA	   =stick->GetRawButton(0);
		Output.buttonB	   =stick->GetRawButton(1);
		Output.buttonX	   =stick->GetRawButton(2);
		Output.buttonY	   =stick->GetRawButton(3);
		Output.leftTrigger =stick->GetRawButton(4);
		Output.rightTrigger=stick->GetRawButton(5);

		return Output;
	}

};
