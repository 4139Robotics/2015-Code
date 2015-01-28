/*
 *  Output.cpp
 *  	Takes in various inputs and sends them to the appropriate outputs.
 *
 *  FRC Team 4139 - Easy As Pi
 *  	Author(s):
 */

#include "WPILib.h"
#include "Wheels.cpp"

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
	//
};

class Output
{

};
