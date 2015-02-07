/*
 *  Wheels.cpp
 *  	Drives the robot.
 *
 *  FRC Team 4139 - Easy as Pi
 *  	Author(s): Michael Yee and Anthony Nguyen
 */

#include "WPILib.h"

//TODO - NormalSpeed = HalfSpeed - TurboMode - FullSpeed - AccelerationCurve(Only in TurboMode)
//COMP - NormalSpeed[X]  TurboMode[X]  180CCW[X]  180CW[X]

struct Wheels_In
{
	float xMovement, yMovement, rotation, gyroAngle;
	bool turboMode;
	bool rotateCCW; // Drivestate: 3 (CCW Turn)
	bool rotateCW; // Drivestate: 4 (CW Turn)
};

struct Wheels_Out
{
	//
};

class Wheels
{

private:
	RobotDrive *drive;
	//int driveState; // State 1: Normal  State 2: TurboMode  State 3: CCW Turn  State 4: CW Turn

public:
	Wheels()
	{
		drive = new RobotDrive(0,2,1,3); //frontLeft, rearLeft, frontRight, rearRight
		drive->SetInvertedMotor(RobotDrive::kFrontLeftMotor, true); // 0 is front left wheel
		drive->SetInvertedMotor(RobotDrive::kRearLeftMotor, true); // 2 is back left wheel
	}

	Wheels_Out Run(Wheels_In input)
	{
		Wheels_Out output;

		float xMove = 0;
		float yMove = 0;
		float rotationSpeed = 0;

		// normal
		if(!input.turboMode)
		{
			xMove = input.xMovement/2;
			yMove = input.yMovement/2;

			rotationSpeed = input.rotation;
		}
		// turbo
		else
		{
			xMove = input.xMovement;
			yMove = input.yMovement;

			rotationSpeed = input.rotation;
		}

		// rotation
		if(input.rotateCCW)
		{
			rotationSpeed = -0.5;
		}
		if(input.rotateCW)
		{
			rotationSpeed = 0.5;
		}

		drive->MecanumDrive_Cartesian(xMove, yMove, rotationSpeed, input.gyroAngle);
		return output;
	}
};
