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
	bool rotate;

	// Forklift
	int state;
};

struct Output_Out
{
	// nothing
};

class Output
{
private:
	Wheels* wheels;

public:
	Output()
	{
		wheels = new Wheels();
	}

	Output_Out Run(Output_In input)
	{
		Output_Out output;

		Wheels_In wIn;
		Wheels_Out wOut;

		wIn.xMovement = input.xMovement;
		wIn.yMovement = input.yMovement;
		wIn.rotation = input.rotation;
		wIn.gyroAngle = input.gyroAngle;

		wOut = wheels->Run(wIn);

		return output;
	}
};
