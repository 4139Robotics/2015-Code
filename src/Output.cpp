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

};
