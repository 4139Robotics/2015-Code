/*
 *  X360Controller.cpp
 *  	Takes in various user inputs and sends them out.
 *
 *  FRC Team 4139 - Easy as Pi
 *  	Author(s):
 */

#include "WPILib.h"
#include "math.h"

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


	//signfinder, used for deadzone
	float findSign(float num)
	{
			if (num > 0)
				return 1;
			else if (num < 0)
				return -1;
			else
				return 0;
		}

		//Deadzone due to bad controllers
		float ApplyDZ(float axis, float deadzone)
		{
			return fabs(axis) < deadzone ? 0 : (fabs(axis) - deadzone) / (1
					- deadzone) * findSign(axis);
		}

};
