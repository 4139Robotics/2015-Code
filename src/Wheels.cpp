/*
 *  Wheels.cpp
 *  	Drives the robot.
 *
 *  FRC Team 4139 - Easy as Pi
 *  	Author(s): Michael Yee and Anthony Nguyen
 */

#include "WPILib.h"

//TODO - NormalSpeed = HalfSpeed - TurboMode - FullSpeed - AccelerationCurve(Only in TurboMode)


struct Wheels_In
{
	float xMovement, yMovement, rotation, gyroAngle;
	// Forward/Backward, Left/Right, Rotating, Robot's Current Rotation
	float FINALACCEL; //The Acceleration Constant
	bool rotateleft;
	bool rotateright;
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
		float xmove = 0;
		float ymove = 0;
		float rotationspeed = 0;



		if(drivestate == 1 || drivestate == 2)
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

			if(drivestate == 1)
			{
				xmove = input.xMovement/2;
				ymove = input.yMovement/2;
				//rotationspeed = input.rotation;
			}
			else if(drivestate == 2)
			{
				xMovement += (xMovement * FINALACCEL);
				yMovement += (yMovement * FINALACCEL);

				xmove = input.xMovement;
				ymove = input.yMovement;
				//rotationspeed = input.rotation;
			}
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
