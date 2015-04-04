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
	//VisionProcessing* vision;
	Timer* timer;
	//Timer* visionTimer;
	//bool isTote;
	//double distanceToTote;
	double autoRotation;
	//bool autoHasTote;
	int autonomousStage;
	int autonomousMethod;

	void RobotInit()
	{
		lw = LiveWindow::GetInstance();
		output = new Output();
		input = new Input();
		//vision = new VisionProcessing();
		timer = new Timer();
		//visionTimer = new Timer();
	}

	void AutonomousInit()
	{
		timer->Stop();
		timer->Reset();
		//visionTimer->Stop();
		//visionTimer->Reset();
		autoRotation = 0.0;
		//autoHasTote = false;
		autonomousStage = 0;
		autonomousMethod = 1; // 1 is timer based, 2 is vision based, 0 is moves forward
	}

	void AutonomousPeriodic()
	{

		// structs
		Input_In aInputIn;
		Input_Out aInputOut;
		Output_In aOutputIn;
		Output_Out aOutputOut;
		// vision processing structs
		//Vision_In aVisionIn;
		//Vision_Out aVisionOut;

		// getting sensor/input data
		aInputOut = input->Run(aInputIn);

		// timer based autonomous code
		if(autonomousMethod == 1)
		{
			switch(autonomousStage)
			{
			case 0: // initial autonomous stuff
				timer->Start();
				autonomousStage++;
				autoRotation = 0.0;
				aOutputIn.yMovement = 0.0;
				aOutputIn.rotation = autoRotation;
				aOutputIn.liftAmount = 0.0;
				timer->Reset();
				break;
			case 1: // move forward a little bit
				aOutputIn.yMovement = 0.2;
				aOutputIn.rotation = autoRotation;
				aOutputIn.liftAmount = 0.0;
				if(timer->Get() > 1.5)
				{
					autonomousStage++;
					aOutputIn.yMovement = 0.0;
					timer->Reset();
				}
				break;
			case 2: // lift box
				aOutputIn.liftAmount = 0.5;
				aOutputIn.liftManualControl = true;
				aOutputIn.yMovement = 0.05;
				aOutputIn.rotation = autoRotation;
				if(timer->Get() > 1)
				{
					autonomousStage++;
					aOutputIn.liftAmount = 0.0;
					aOutputIn.yMovement = 0.0;
					timer->Reset();
				}
				break;
			case 3: // move backwards
				aOutputIn.yMovement = -0.2;
				aOutputIn.rotation = autoRotation;
				aOutputIn.liftAmount = 0.0;
				if(timer->Get() > 3)
				{
					autonomousStage++;
					aOutputIn.yMovement = 0.0;
					timer->Reset();
				}
				break;
			case 4: // put tote down
				aOutputIn.liftAmount = -0.5;
				aOutputIn.liftManualControl = true;
				aOutputIn.yMovement = 0.0;
				aOutputIn.rotation = autoRotation;
				if(timer->Get() > 1)
				{
					autonomousStage++;
					aOutputIn.liftAmount = 0.0;
					timer->Reset();
				}
				break;
				/*
			case 5: // rotate clockwise
				autoRotation = 0.1;
				aOutputIn.rotation = autoRotation;
				if(timer->Get() > 3)
				{
					autonomousStage++;
					autoRotation = 0.0;
					aOutputIn.rotation = autoRotation;
					timer->Reset();
				}
				break;
				*/
			default: // after everything is done, all stop
				aOutputIn.yMovement = 0.0;
				aOutputIn.liftAmount = 0.0;
				aOutputIn.rotation = 0.0;
				break;
			}
		}
		else if(autonomousMethod == 2) // vision based, UNTESTED
		{
			/*
			// running vision code
			visionTimer->Start();
			// vision processing only runs every 0.2 seconds, resource intensive
			if(visionTimer->HasPeriodPassed(0.2))
			{
				aVisionIn.shouldProcess = true;
				aVisionOut = vision->Run(aVisionIn);
				isTote = aVisionOut.returnIsTote;
				distanceToTote = aVisionOut.returnDistanceToTote;
				visionTimer->Reset();
			}

			// determining what to do based on vision data
			timer->Start();
			if(!autoHasTote)
			{
				if(distanceToTote > 24)
				{
					aOutputIn.yMovement = 0.15;
				}
				else if(distanceToTote < 24 && distanceToTote > 8)
				{
					aOutputIn.yMovement = 0.05;
					timer->Stop();
					timer->Reset();
				}
				else if(distanceToTote <= 6)
				{
					aOutputIn.yMovement = 0.0;
					aOutputIn.liftManualControl = true;
					aOutputIn.liftAmount = -0.1;
					if(timer->HasPeriodPassed(0.5))
					{
						aOutputIn.liftAmount = 0.0;
						autoHasTote = true;
						timer->Stop();
						timer->Reset();
					}
				}
			}
			else
			{
				//aOutputIn.xMovement = 0.15;
				aOutputIn.yMovement = -0.15;
				if(timer->HasPeriodPassed(1))
				{
					aOutputIn.xMovement = 0.0;
					aOutputIn.yMovement = 0.0;
				}
			}
			 */
		}
		else if(autonomousMethod == 0) // just moves forward
		{
			//aOutputIn.yMovement = 0.0;
			aOutputIn.liftAmount = 0.0;

			timer->Start();
			aOutputIn.yMovement = 0.2;
			aOutputIn.rotation = 0.0;

			if(timer->Get() > 3.5)
			{
				aOutputIn.yMovement = 0.0;
			}
		}

		// printing autonomous data
		SmartDashboard::PutString("DB/String 5", "aStage: " + std::to_string(autonomousStage));
		SmartDashboard::PutString("DB/String 6", "aYMove: "  + std::to_string(aOutputIn.yMovement));
		SmartDashboard::PutString("DB/String 7", "aRotate: " + std::to_string(aOutputIn.rotation));
		SmartDashboard::PutString("DB/String 8", "aLift: " + std::to_string(aOutputIn.liftAmount));

		// manual overrides
		aOutputIn.liftTurbo = true;
		aOutputIn.turboMode = false;
		aOutputIn.xMovement = 0.0;
		//aOutputIn.yMovement = 0.0;
		aOutputIn.rotation = 0.0;
		//aOutputIn.liftAmount = 0.0;

		// running outputs with passed in inputs
		aOutputOut = output->Run(aOutputIn);
	}


	void TeleopInit()
	{
		// stopping and resetting timers
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
		// drive stuff
		outputIn.xMovement = inputOut.returnX;
		outputIn.yMovement = inputOut.returnY;
		outputIn.turboMode = inputOut.returnTurboMode;
		outputIn.rotation = inputOut.returnRotation;
		outputIn.gyroAngle = inputOut.returnGyroAngle;
		// lift stuff
		outputIn.liftActive = inputOut.returnLiftActive;
		outputIn.liftAmount = inputOut.returnLiftAmount;
		outputIn.liftTurbo = inputOut.returnLiftTurbo;
		outputIn.liftManualControl = inputOut.returnLiftManualControl;
		outputIn.liftState = inputOut.returnLiftState;

		// printing values
		SmartDashboard::PutString("DB/String 0", "AccelX: " + std::to_string(inputOut.returnAccelX));
		SmartDashboard::PutString("DB/String 1", "AccelY: " + std::to_string(inputOut.returnAccelY));
		SmartDashboard::PutString("DB/String 2", "AccelZ: " + std::to_string(inputOut.returnAccelZ));
		SmartDashboard::PutString("DB/String 3", "Lift: " + std::to_string(-(outputIn.liftAmount / (outputIn.liftTurbo ? 1 : 2))));

		// run outputs with passed in input stuff
		outputOut = output->Run(outputIn);
	}

	void TestPeriodic()
	{
		lw->Run(); // no idea tbh xD
	}
};

START_ROBOT_CLASS(PiBot2015);
