/*
 *  Output.cpp
 *  	Takes in various inputs and sends them to the appropriate outputs.
 *
 *  FRC Team 4139 - Easy as Pi
 *  	Author(s):
 */

#include "WPILib.h"
#include "Wheels.cpp"
#include "Forklift.cpp"

struct Output_In
{
	// Wheels
	float xMovement, yMovement, rotation, gyroAngle;
	bool turboMode;
	bool liftActive;

	// Forklift
	float liftAmount;
	bool liftManualControl;
	int liftState;
};

struct Output_Out
{
	// nothing
};

class Output
{
private:
	Wheels* wheels;
	Forklift* lift;

public:
	Output()
	{
		wheels = new Wheels();
		lift = new Forklift();
	}

	Output_Out Run(Output_In input)
	{
		Output_Out output;

		Wheels_In wIn;
		Wheels_Out wOut;
		Forklift_In fIn;
		Forklift_Out fOut;

		wIn.xMovement = input.xMovement;
		wIn.yMovement = input.yMovement;
		wIn.rotation = input.rotation;
		wIn.gyroAngle = input.gyroAngle;
		wIn.liftActive = input.liftActive;

		wOut = wheels->Run(wIn);

		fIn.liftAmount = input.liftAmount;
		fIn.liftManualControl = input.liftManualControl;
		fIn.liftState = input.liftState;

		fOut = lift->Run(fIn);

		return output;
	}
};
