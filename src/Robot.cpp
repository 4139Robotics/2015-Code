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
#include "VisionProcessing.cpp"

class PiBot2015: public IterativeRobot
{
public:
	//

private:
	LiveWindow *lw;
	Output* output;
	Input* input;
	VisionProcessing* vision;
	Timer* timer;
	Timer* visionTimer;
	bool isTote;
	double distanceToTote;
	int autoRotation;
	//int autonomousStage;

	void RobotInit()
	{
		lw = LiveWindow::GetInstance();
		output = new Output();
		input = new Input();
		vision = new VisionProcessing();
		timer = new Timer();
		visionTimer = new Timer();
	}

	void AutonomousInit()
	{
		timer->Stop();
		timer->Reset();
		visionTimer->Stop();
		visionTimer->Reset();
		autoRotation = 0;
		//autonomousStage = 0;
	}

	void AutonomousPeriodic()
	{

		// structs
		Input_In aInputIn;
		Input_Out aInputOut;
		Output_In aOutputIn;
		Output_Out aOutputOut;
		// vision processing structs
		Vision_In aVisionIn;
		Vision_Out aVisionOut;

		// getting sensor/input data
		aInputOut = input->Run(aInputIn);

		// running vision code
		visionTimer->Start();
		// vision processing only runs every 0.1 seconds, resource intensive
		if(visionTimer->HasPeriodPassed(0.1))
		{
			aVisionIn.shouldProcess = true;
			aVisionOut = vision->Run(aVisionIn);
			isTote = aVisionOut.returnIsTote;
			distanceToTote = aVisionOut.returnDistanceToTote;
			visionTimer->Reset();
		}

		// determing what to do based on vision data
		timer->Start();
		if(isTote)
		{
			if(distanceToTote > 24)
			{
				aOutputIn.yMovement = 0.5;
			}
			else if(distanceToTote < 24 && distanceToTote > 8)
			{
				aOutputIn.yMovement = 0.1;
			}
			else if(distanceToTote <= 8)
			{
				aOutputIn.yMovement = 0.0;
				aOutputIn.liftState = 1;
				aOutputIn.liftManualControl = false;
			}
		}
		else // if no tote, rotates left then
		{
			if(autoRotation == 0) // rotate left
			{
				aOutputIn.rotation = -0.2;
				if(timer->HasPeriodPassed(0.25))
				{
					autoRotation = 1;
					timer->Stop();
					timer->Reset();
				}
			}
			else if(autoRotation == 1) // rotate right
			{
				aOutputIn.rotation = 0.2;
				if(timer->HasPeriodPassed(0.45))
				{
					autoRotation = 0;
					timer->Stop();
					timer->Reset();
				}
			}
		}

		aOutputOut = output->Run(aOutputIn);

		/* old manual timer based autonomous code
		switch(autonomousStage)
		{
		case 0: // initial autonomous stuff
			timer->Start();
			autonomousStage++;
			break;
		case 1: // move forward a little bit
			aOutputIn.yMovement = 0.5;
			if(timer->HasPeriodPassed(0.1))
			{
				autonomousStage++;
				aOutputIn.yMovement = 0.0;
			}
			break;
		case 2: // lift box
			aOutputIn.liftAmount = 0.5;
			if(timer->HasPeriodPassed(0.2))
			{
				autonomousStage++;
				aOutputIn.liftAmount = 0.0;
			}
			break;
		case 3: // keep moving forward
			aOutputIn.yMovement = 0.25;
			if(timer->HasPeriodPassed(2.0))
			{
				autonomousStage++;
				aOutputIn.yMovement = 0.0;
			}
			break;
		case 4: // finished
			break;
		}

		aOutputOut = output->Run(aOutputIn);
		*/
	}

	void TeleopInit()
	{
		timer->Stop();
		timer->Reset();
	}

	void TeleopPeriodic()
	{
		// structs
		Input_In inputIn;
		Input_Out inputOut;
		Output_In outputIn;
		Output_Out outputOut;

		// getting sensor/input data
		inputOut = input->Run(inputIn);

		// passing in the input data to the outputs
		// this is drive stuff
		outputIn.xMovement = inputOut.returnX;
		outputIn.yMovement = inputOut.returnY;
		outputIn.turboMode = inputOut.returnTurboMode;
		outputIn.rotation = inputOut.returnRotation;
		outputIn.gyroAngle = inputOut.returnGyroAngle;
		// this is lift stuff
		outputIn.liftActive = inputOut.returnLiftActive;
		outputIn.liftAmount = inputOut.returnLiftAmount;
		outputIn.liftManualControl = inputOut.returnLiftManualControl;
		outputIn.liftState = inputOut.returnLiftState;

		// run outputs with passed in input stuff
		outputOut = output->Run(outputIn);
	}

	void TestPeriodic()
	{
		lw->Run(); // no idea tbh xD
	}
};

START_ROBOT_CLASS(PiBot2015);
