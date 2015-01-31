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
// Forward/Backward, Left/Right, Rotating, Robot's Current Rotation
//	bool rotate; (how would this determine whether we you want to rotate left or right?)
	bool rotateleft; // Drivestate: 3 (CCW Turn)
	bool rotateright; // Drivestate: 4 (CW Turn)
};

struct Wheels_Out
{
	//
};

class Wheels
{

private:

	RobotDrive *drive;
	int drivestate; // State 1: Normal  State 2: TurboMode  State 3: CCW Turn  State 4: CW Turn

public:

	Wheels()
	{
		drive = new RobotDrive(0,2,1,3); //frontLeft, rearLeft, frontRight, rearRight
		drivestate = 1;
		drive->SetInvertedMotor(RobotDrive::kFrontLeftMotor, true); // 0 is front left wheel
		drive->SetInvertedMotor(RobotDrive::kRearLeftMotor, true); // 2 is back left wheel
	}

	Wheels_Out Run(Wheels_In input)
	{
		Wheels_Out output;

		float xmove = 0;
		float ymove = 0;
		float rotationspeed = 0;
		float gyroAng = 0;
		const float finalAccel = 0.335; //The Acceleration Constant

		if(input.rotateleft)
		{
			drivestate = 3;
		}
		if(input.rotateright)
		{
			drivestate = 4;
		}

		if(drivestate == 1 || drivestate == 2)
		{
			if(input.xMovement > 1)
			{
				input.xMovement = 1;
			}
			else if(input.xMovement < -1)
			{
				input.xMovement = -1;
			}
			if(input.yMovement > 1)
			{
				input.yMovement = 1;
			}
			else if(input.yMovement < -1)
			{
				input.yMovement = -1;
			}
			if(input.rotation > 1)
			{
				input.rotation = 1;
			}
			else if(input.rotation < -1)
			{
				input.rotation = -1;
			}

			if(drivestate == 1)
			{
				xmove = input.xMovement/2;
				ymove = input.yMovement/2;
				rotationspeed = input.rotation;
				//hopefully the struct float is determining whether the rotation is CW/CCW
				gyroAng = input.gyroAngle;
			}
			else if(drivestate == 2)
			{
				input.xMovement += (input.xMovement * finalAccel);
				input.yMovement += (input.yMovement * finalAccel);

				xmove = input.xMovement;
				ymove = input.yMovement;
				rotationspeed = input.rotation;
				//hopefully the struct float is determining whether the rotation is CW/CCW
				gyroAng = input.gyroAngle;
			}
		}
		else if(drivestate == 3 || drivestate == 4)
		{
			if(input.xMovement > 1)
			{
				input.xMovement = 1;
			}
			else if(input.xMovement < -1)
			{
				input.xMovement = -1;
			}
			if(input.yMovement > 1)
			{
				input.yMovement = 1;
			}
			else if(input.yMovement < -1)
			{
				input.yMovement = -1;
			}
			if(input.rotation > 1)
			{
				input.rotation = 1;
			}
			else if(input.rotation < -1)
			{
				input.rotation = -1;
			}

			if(drivestate == 3)
			{
				input.gyroAngle += 180;
			}
			else if(drivestate == 4)
			{
				input.gyroAngle -= 180;
			}

			xmove = input.xMovement;
			ymove = input.yMovement;
			rotationspeed = input.rotation;
			gyroAng = input.gyroAngle;
		}

		drive->MecanumDrive_Cartesian(xmove, ymove, rotationspeed, gyroAng);
		return output;
	}
};
