/*
 *  Output.cpp
 *  	Takes in various inputs and sends them to the appropriate outputs.
 *
 *  FRC Team 4139 - Easy as Pi
 *  	Author(s):
 */

#include "WPILib.h"
#include "Wheels.cpp"
#include "X360Controller.cpp"

struct Output_In
{
	// Wheels
	float xMovement, yMovement, rotation, gyroAngle;
	bool rotate;

	// Forklift
	int state;
};

class Output
{
public:
	Output_Out Run(Output_Input in)
	{
		Output_Out output;
		float returnX = xMovement;
		float returnY = yMovement;
		float returnRotation = rotation;
		bool returnRotate = rotate;
	}
};
