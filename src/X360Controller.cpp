/*
 *  X360Controller.cpp
 *  	Takes in various user inputs and sends them out.
 *
 *  FRC Team 4139 - Easy as Pi
 *  	Author(s): Duncan Klug, LeDaniel Leung
 */

#include "WPILib.h"
#include "math.h"

struct X360Controller_In
{
	//
};

struct X360Controller_Out
{
	// Wheels
	float returnX, returnY, returnRotation;
	bool returnTurboMode;

	// Forklift
	float returnLiftAmount;
	float returnLiftActive, returnLiftManualControl;
	int returnLiftState;

	bool returnResetGyro;
};

class X360Controller
{
private:
	Joystick* stick;

public:
	const float DZ = .15;

	X360Controller()
	{
		stick = new Joystick(0);
	}

	X360Controller_Out Run(X360Controller_In input)
	{
		X360Controller_Out output;

		output.returnX = ApplyDZ(stick->GetRawAxis(0), DZ);
		output.returnY = -ApplyDZ(stick->GetRawAxis(1), DZ);
		if(stick->GetRawAxis(2) != 0)
		{
			output.returnRotation = -stick->GetRawAxis(2);
		}
		else if(stick->GetRawAxis(3) != 0)
		{
			output.returnRotation = stick->GetRawAxis(3);
		}
		output.returnTurboMode = stick->GetRawButton(5);

		output.returnLiftAmount = stick->GetRawAxis(5);
		if(stick->GetRawAxis(5) != 0)
		{
			output.returnLiftActive = true;
			output.returnLiftManualControl = true;
		}
		else
		{
			output.returnLiftActive = false;
			output.returnLiftManualControl = false;
		}

		output.returnResetGyro = stick->GetRawButton(7);

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
