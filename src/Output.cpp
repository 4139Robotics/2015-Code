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
	private X360Controller.X360Controller_Out[] data;
	private X360Controller
	{
		
	}
	public void ImportData(X360Controller)
	{
		this.data = X360Controller.ExportData();
	}
};
