#ifndef INPUT_H
#define INPUT_H

#include "WPILib.h"
#include "X360Controller.cpp"
#include "Sensors.cpp"

struct Input_In
{
};

struct Input_Out
{
	// X360Controller
	float returnX, returnY, returnRotation;
	bool returnRotate;

	// Sensors
	float returnGyroAngle;
	float returnAccelX, returnAccelY, returnAccelZ;
	float returnDistance;
};

class Input
{
public:
	Input();
	~Input();
	Input_Out Run(Input_In in);

private:
	X360Controller* controller;
	Sensors* sensors;
};

#endif
