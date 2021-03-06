/*
 *  Wheels.cpp
 *  	Drives the robot.
 *
 *  FRC Team 4139 - Easy as Pi
 *  	Author(s): Michael Yee and Anthony Nguyen
 */

#include "WPILib.h"

struct Wheels_In
{
	float xMovement, yMovement, rotation, gyroAngle;
	bool turboMode;
	bool liftActive;
};

struct Wheels_Out
{
	//
};

class Wheels
{

private:
	RobotDrive* drive;
	MotorSafetyHelper* driveSafety;

public:
	Wheels()
	{
		drive = new RobotDrive(0,2,4,3); //frontLeft, rearLeft, frontRight, rearRight
		drive->SetInvertedMotor(RobotDrive::kFrontLeftMotor, true); // 0 is front left wheel
		drive->SetInvertedMotor(RobotDrive::kRearLeftMotor, true); // 2 is back left wheel
		drive->SetExpiration(0.1);
		drive->SetSafetyEnabled(true);
		driveSafety = new MotorSafetyHelper(drive);
	}

	Wheels_Out Run(Wheels_In input)
	{
		Wheels_Out output;

		driveSafety->Feed(); // feeding motor safety

		// X movement inverted for new wheel configuration
		input.liftActive = false; // temporary override

		// motors run at half power unless turbo is activated
		// motors will be halved again if lift is being used
		float xMove = -(input.xMovement / (input.turboMode ?  1 : 2) / (input.liftActive ? 2 : 1));
		float yMove = (input.yMovement / (input.turboMode ?  1 : 2) / (input.liftActive ? 2 : 1));
		float rotationSpeed = input.rotation;

		drive->MecanumDrive_Cartesian(xMove, yMove, rotationSpeed);//, input.gyroAngle); // no gyro anymore
		return output;
	}
};
