/*
 *  Forklift.cpp
 *  	Manages the forklift.
 *
 *  FRC Team 4139 - Easy as Pi
 *  	Author(s): Elliot Yoon
 */

#include "WPILib.h"

struct Forklift_In
{
	float liftAmount;
	bool liftTurbo, liftManualControl;
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
	//Talon* liftTwo; // lift no longer has 2 talons
	MotorSafetyHelper* safetyOne;
	//MotorSafetyHelper* safetyTwo;
	float accel;
	Timer* timer;

public:
	Forklift()
	{
		liftOne = new Talon(1);
		//liftTwo = new Talon(5);
		liftOne->SetExpiration(0.1);
		//liftTwo->SetExpiration(0.1);
		liftOne->SetSafetyEnabled(true);
		//liftTwo->SetSafetyEnabled(true);
		safetyOne = new MotorSafetyHelper(liftOne);
		//safetyTwo = new MotorSafetyHelper(liftTwo);
		accel = 0.0;
		timer = new Timer();
	}

	Forklift_Out Run(Forklift_In input)
	{
		Forklift_Out output;

		safetyOne->Feed(); // feeding motor safety
		//safetyTwo->Feed();

		/******* removed acceleration curve, does not seem to function
		float move = 0.0;

		if(input.liftManualControl)
		{
			timer->Stop();
			timer->Reset();
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
		}
		else
		{
			timer->Start();
			if(input.liftState == 1)
			{
				move = 0.25;
				if(timer->HasPeriodPassed(0.1))
				{
					move = 0.0;
					timer->Stop();
					timer->Reset();
				}
			}
			else if(input.liftState == 2)
			{
				move = 0.25;
				if(timer->HasPeriodPassed(0.4))
				{
					move = 0.0;
					timer->Stop();
					timer->Reset();
				}
			}
			else if(input.liftState == 3)
			{
				move = 0.25;
				if(timer->HasPeriodPassed(0.6))
				{
					move = 0.0;
					timer->Stop();
					timer->Reset();
				}
			}
			else if(input.liftState == 4)
			{
				move = 0.25;
				if(timer->HasPeriodPassed(0.8))
				{
					move = 0.0;
					timer->Stop();
					timer->Reset();
				}
			}
		}

		liftOne->Set(move);
		//liftTwo->Set(move);

		 *******************/

		// lift runs at half speed unless turbo is activated
		liftOne->Set(-(input.liftAmount / (input.liftTurbo ? 1 : 2)));

		return output;
	}
};
