/*
 *  Forklift.cpp
 *  	Manages the forklift.
 *
 *  FRC Team 4139 - Easy as Pi
 *  	Author(s):
 */

#include "WPILib.h"

struct Forklift_In
{
	float liftAmount;
	bool liftManualControl;
	int liftState;
};

struct Forklift_Out
{
	//
};

class Forklift
{
private:
	Talon* liftOne;
	Talon* liftTwo;
	MotorSafetyHelper* safetyOne;
	MotorSafetyHelper* safetyTwo;
	float accel;

public:
	Forklift()
	{
		liftOne = new Talon(4);
		liftTwo = new Talon(5);
		liftOne->SetExpiration(0.1);
		liftTwo->SetExpiration(0.1);
		liftOne->SetSafetyEnabled(true);
		liftTwo->SetSafetyEnabled(true);
		safetyOne = new MotorSafetyHelper(liftOne);
		safetyTwo = new MotorSafetyHelper(liftTwo);
		accel = 0.0;
	}

	Forklift_Out Run(Forklift_In input)
	{
		Forklift_Out output;

		safetyOne->Feed();
		safetyTwo->Feed();

		float move = 0.0;

		if(input.liftAmount > 0)
		{
			move = accel;
			if(accel < 1)
			{
				accel+=0.01-move/100;
			}
		}
		else if(input.liftAmount < 0)
		{
			move = accel;
			if(accel > -1)
			{
				accel-=0.01+move/100;
			}
		}
		else if(input.liftAmount == 0)
		{
			move = accel;
			if(accel < 0)
			{
				accel+=0.01;
			}
			else if(accel > 0)
			{
				accel -= 0.01;
			}
		}

		liftOne->Set(move);
		liftTwo->Set(move);

		return output;
	}
};
