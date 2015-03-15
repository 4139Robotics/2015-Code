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
	Timer* timer;
	int autonomousStage;

	void RobotInit()
	{
		lw = LiveWindow::GetInstance();
		output = new Output();
		input = new Input();
		timer = new Timer();
	}

	void AutonomousInit()
	{
		timer->Stop();
		timer->Reset();
		autonomousStage = 0;
	}

	void AutonomousPeriodic()
	{
		Input_In inputIn;
		Input_Out inputOut;
		Output_In outputIn;
		Output_Out outputOut;

		inputOut = input->Run(inputIn);

		switch(autonomousStage)
		{
		case 0: // initial autonomous stuff
			timer->Start();
			autonomousStage++;
			break;
		case 1: // move forward a little bit
			outputIn.yMovement = 0.5;
			if(timer->HasPeriodPassed(0.1))
			{
				autonomousStage++;
				outputIn.yMovement = 0.0;
			}
			break;
		case 2: // lift box
			outputIn.liftAmount = 0.5;
			if(timer->HasPeriodPassed(0.2))
			{
				autonomousStage++;
				outputIn.liftAmount = 0.0;
			}
			break;
		case 3: // keep moving forward
			outputIn.yMovement = 0.25;
			if(timer->HasPeriodPassed(2.0))
			{
				autonomousStage++;
				outputIn.yMovement = 0.0;
			}
			break;
		case 4: // finished
			break;
		}
		outputOut = output->Run(outputIn);

	}

	void TeleopInit()
	{
		timer->Stop();
		timer->Reset();
	}

	void TeleopPeriodic()
	{
		Input_In inputIn;
		Input_Out inputOut;
		Output_In outputIn;
		Output_Out outputOut;

		inputOut = input->Run(inputIn);

		outputIn.xMovement = inputOut.returnX;
		outputIn.yMovement = inputOut.returnY;
		outputIn.turboMode = inputOut.returnTurboMode;
		outputIn.rotation = inputOut.returnRotation;
		outputIn.gyroAngle = inputOut.returnGyroAngle;

		outputIn.liftActive = inputOut.returnLiftActive;
		outputIn.liftAmount = inputOut.returnLiftAmount;
		outputIn.liftManualControl = inputOut.returnLiftManualControl;
		outputIn.liftState = inputOut.returnLiftState;

		outputOut = output->Run(outputIn);
	}

	void TestPeriodic()
	{
		lw->Run();
	}
};

START_ROBOT_CLASS(PiBot2015);
