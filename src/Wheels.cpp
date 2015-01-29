/*
 *  Wheels.cpp
 *  	Drives the robot.
 *
 *  FRC Team 4139 - Easy as Pi
 *  	Author(s):
 */

#include "WPILib.h"

struct Wheels_In
{
	float xMovement, yMovement, rotation, gyroAngle;
	// Forward/Backward, Left/Right, Rotating, Robot's Current Rotation
	bool rotate;
//	bool spinleft;
//	bool spinright;
};

struct Wheels_Out
{
	//
};

class Wheels
{

private:

	RobotDrive *drive;
	int state; // State 1: Normal  State 2: Turning  State 3: 180 Spin Left  State 4: 180 Spin Right


public:

	Wheels()
	{
		drive = new RobotDrive(0,2,1,3) //frontLeft, rearLeft, frontRight, rearRight
		state = 1;

	}


	Wheel_Out Wheels::Run(Wheel_In input)
	{
		float xmove = 0;
		float ymove = 0;
		float rotationspeed = 0;

		if(rotate)
		{
			state = 2;
		}
		/*
		if(spinleft)
		{
			state = 3;
		}
		if(spinright)
		{
			state = 4;
		}
		*/

		if(state == 1)
		{
			if(input.xMovement > 1)
			{
				input.xMovement == 1;
			}
			else if(input.xMovement < -1)
			{
				input.xMovement == -1;
			}

			if(input.yMovement > 1)
			{
				input.yMovement == 1;
			}
			else if(input.yMovement < -1)
			{
				input.yMovement == -1;
			}

			xmove = input.xMovement;
			ymove = input.yMovement;

		}
		else if(state == 2)
		{
			if(input.xMovement > 1)
			{
				input.xMovement == 1;
			}
			else if(input.xMovement < -1)
			{
				input.xMovement == -1;
			}

			if(input.yMovement > 1)
			{
				input.yMovement == 1;
			}
			else if(input.yMovement < -1)
			{
				input.yMovement == -1;
			}

			if(input.rotation > 1)
			{
				input.rotation == 1;
			}
			else if(input.rotation < -1)
			{
				input.rotation == -1;
			}

			xmove = input.xMovement;
			ymove = input.yMovement;
			rotationspeed = input.rotation;
		}
		/*
		else if(state == 3)
		{
			input.xMovement = 0;
			input.yMovement = 0;
			input.rotation = -0.5;

			xmove = input.xMovement;
			ymove = input.yMovement;
			rotationspeed = input.rotation;
			input.gyroAngle = input.gyroAngle + 180;
		}
		else if(state == 4)
		{
			input.xMovement = 0;
			input.yMovement = 0;
			input.rotation = 0.5;

			xmove = input.xMovement;
			ymove = input.yMovement;
			rotationspeed = input.rotation;
			input.gyroAngle = input.gyroAngle - 180;
		}
		*/

		drive->MecanumDrive_Cartesian(xmove, ymove, rotationspeed, input.gyroAngle);
		return WheelOutput();
	}
};
