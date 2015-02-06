/*
 *  X360Controller.cpp
 *  	Takes in various user inputs and sends them out.
 *
 *  FRC Team 4139 - Easy as Pi
 *  	Author(s): Duncan Klug, LeDaniel Leung
 */

// NOTE: Good job, but way too much stuff. I feel like lots of this will be cut out soon.
// We also need clearer variables; renaming will come soon.

#include "WPILib.h"
#include "math.h"

struct X360Controller_In
{
	//empty piece of trash
};

public struct X360Controller_Out
{
	//final return values
	float returnX,
		returnY,
		returnRotation;
	bool returnRotate;

	//left and right analog sticks
	float leftAnalogX,
		leftAnalogY,
		rightAnalogX,
		rightAnalogY,
		leftThrottle,
		rightThrottle;

	//POV hat
	int center,
		up,
		upRight,
		right,
		downRight,
		down,
		downLeft,
		left,
		upLeft;

	//buttons
	bool buttonA,
		buttonB,
		buttonX,
		buttonY,
		leftTrigger,
		rightTrigger,
		back,
		start;

	//currently arbitrary functions
	bool turbo;
};
private X360Controller_Out[] data;
public X360Controller_Out[] ExportData()
{
	return data;
}

class X360Controller
{
private:
	Joystick* stick;
	X360Controller_Out output;

public:

	const float DZ = .15;

	X360Controller()
	{
		stick = new Joystick(1);
		output.returnX = 0.0; //do some math in run
		output.returnY = 0.0; //do some math in run
		output.returnRotation = 0.0; //do some math in run
		output.returnRotate = false;
		output.turbo = false;

	}

	X360Controller_Out Run(X360Controller_In input)
	{
		//receiving movement && throttle values and setting
		output.leftAnalogX   = stick->GetRawAxis(0);
		output.leftAnalogY   = stick->GetRawAxis(1);
		output.leftThrottle  = stick->GetRawAxis(2);
		output.rightThrottle = stick->GetRawAxis(3);
		output.rightAnalogX  = stick->GetRawAxis(4);
		output.rightAnalogY  = stick->GetRawAxis(5);

		//setting states to POV values
		output.center	 = stick->GetPOV(-1);
		output.up 		 = stick->GetPOV(0);
		output.upRight   = stick->GetPOV(45);
		output.right 	 = stick->GetPOV(90);
		output.downRight = stick->GetPOV(135);
		output.down 	 = stick->GetPOV(180);
		output.downLeft  = stick->GetPOV(225);
		output.left 	 = stick->GetPOV(270);
		output.upLeft 	 = stick->GetPOV(315);

		//setting buttons to general functions
		output.buttonA	    = stick->GetRawButton(0);
		output.buttonB	    = stick->GetRawButton(1);
		output.buttonX	    = stick->GetRawButton(2);
		output.buttonY	    = stick->GetRawButton(3);
		output.leftTrigger  = stick->GetRawButton(4);
		output.rightTrigger = stick->GetRawButton(5);
		output.back			= stick->GetRawButton(6);
		output.start		= stick->GetRawButton(7);

		//doing math for final return values
		output.returnX =  ApplyDZ(stick->GetRawAxis(1) / (output.turbo ? 1 : 2), DZ);
		output.returnY = -ApplyDZ(stick->GetRawAxis(2) / (output.turbo ? 1 : 2), DZ);
		output.returnRotation = stick->GetZ();

		return output;
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
		return fabs(axis) < deadzone ? 0 : (fabs(axis) - deadzone) / (1	- deadzone) * findSign(axis);
	}

};
