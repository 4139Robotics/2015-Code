/*
 *  Robot.cpp
 *  	The main robot code. Manages Input/Output and takes appropriate action based on what is sent/received.
 *
 *  FRC Team 4139 - Easy as Pi
 *  	Author(s): Elliot Yoon
 */

#include "WPILib.h"
#include "Input.cpp"
#include "Output.cpp"

class PiBot2015: public IterativeRobot
{
public:

private:
	LiveWindow *lw;
	Output* output;
	Input* input;

	void RobotInit()
	{
		lw = LiveWindow::GetInstance();
		output = new Output();
		input = new Input();
	}

	void AutonomousInit()
	{

	}

	void AutonomousPeriodic()
	{

	}

	void TeleopInit()
	{

	}

	void TeleopPeriodic()
	{
		Input_In inputIn;
		Input_Out inputOut;
		Output_In outputIn;
		Output_Out outputOut;

		inputOut = input->Run(inputIn);

		inputOut.returnX = outputIn.xMovement;
		inputOut.returnY = outputIn.yMovement;
		inputOut.returnRotation = outputIn.rotation;
		inputOut.returnTurboMode = outputIn.turboMode;
		inputOut.returnGyroAngle = outputIn.gyroAngle;
		inputOut.returnAccelX = outputIn.accelX;
		inputOut.returnAccelY = outputIn.accelY;
		inputOut.returnAccelZ = outputIn.accelZ;
		inputOut.returnDistance = outputIn.distance;
		inputOut.returnUpperLiftSwitch = outputIn.upperLiftSwitch;
		inputOut.returnLowerLiftSwitch = outputIn.lowerLiftSwitch;

		outputOut = output->Run(outputIn);
	}

	void TestPeriodic()
	{
		lw->Run();
	}
};

START_ROBOT_CLASS(PiBot2015);
