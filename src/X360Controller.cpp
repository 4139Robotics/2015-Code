/*
 *  X360Controller.cpp
 *  	Takes in various user inputs and sends them out.
 *
 *  FRC Team 4139 - Easy as Pi
 *  	Author(s): Duncan Klug, LeDaniel Leung
 */

#include "WPILib.h"
#include "math.h"

struct X360Controller_In
{
	//empty piece of trash
};

struct X360Controller_Out
{
public:
	float returnX,
		  returnY,
		  returnRotation,
		  returnLift;
	bool returnRotate;

	//left and right analog sticks
	float leftAnalogX, //controls movement
		  leftAnalogY,
		  rightAnalogX, //controls lift
		  rightAnalogY,
		  CCWRotation, //left throttle
		  CWRotation; //right throttle

	//buttons
	bool buttonA, //possible lift heights
	     buttonB,
		 buttonX,
		 buttonY,
		 Turbo, //left bumper
		 Lift, //right bumper
		 GyroReset, //back
		 start;
};

class X360Controller
{
private:
	Joystick* stick;
	X360Controller_Out Output;
	bool yesMoto,
		 noMoto;



public:

	const float DZ = .15;

	X360Controller()
	{
		stick = new Joystick(1);
		Output.returnRotation=0.0; //do some math in run
		Output.returnRotate=false;
		Output.Turbo=false;
		Output.Lift=false;
		yesMoto = false; //what the hell is this
		noMoto = false;
	}
	X360Controller_Out Run(X360Controller_In input)
	{
		//receiving movement && throttle values and setting
		Output.leftAnalogX   = stick->GetRawAxis(0);
		Output.leftAnalogY   = stick->GetRawAxis(1);
		Output.CCWRotation   = stick->GetRawAxis(2);
		Output.CWRotation 	 = stick->GetRawAxis(3);
		Output.rightAnalogX  = stick->GetRawAxis(4);
		Output.rightAnalogY  = stick->GetRawAxis(5);

		//setting buttons to general functions
		Output.buttonA	    = stick->GetRawButton(0);
		Output.buttonB	    = stick->GetRawButton(1);
		Output.buttonX	    = stick->GetRawButton(2);
		Output.buttonY	    = stick->GetRawButton(3);
		Output.Turbo 	    = stick->GetRawButton(4);
		Output.Lift 		= stick->GetRawButton(5);
		Output.GyroReset	= stick->GetRawButton(6);
		Output.start		= stick->GetRawButton(7);

		/*
		the following (commented out) code is based Etan's preferences for driver control
		Output.returnX = Output.rightThrottle*100-Output.leftThrottle*100;
		Output.returnY = Output.leftAnalogY*100;
		*/



		//doing math for final return values
		Output.returnX =  ApplyDZ(Output.leftAnalogX / (Output.Turbo ? 1 : 2), DZ) / (Output.Lift ? 2 : 1);
		Output.returnY = -ApplyDZ(Output.leftAnalogY / (Output.Turbo ? 1 : 2), DZ) / (Output.Lift ? 2 : 1);
		Output.returnRotation = stick->GetZ() / (Output.Lift ? 4 : 2);//ApplyDZ(stick->GetZ()/2, DZ);


		if(Output.CCWRotation>0){
			Output.returnRotate = true;
			Output.CCWRotation = .5;
		}
		if(Output.CWRotation>0){
			Output.returnRotate = true;
			Output.CCWRotation = -.5;
		}
		if(Output.buttonA){
			Output.returnLift = 0;
		}
		if(Output.buttonB){
			Output.returnLift = .25;
		}
		if(Output.buttonX){
			Output.returnLift = .5;
		}
		if(Output.buttonY){
			Output.returnLift = .75;
		}

		Output.returnX *= 100;
		Output.returnY *= 100;


		/*
		if (Output.returnX || Output.returnY)
		{
			if (yesMoto)
			{
			yesMoto = false;
			noMoto = true;
			}
			else if (!noMoto)
				yesMoto = true;
		}
			else
				noMoto = false;

		if (yesMoto && !noMoto)
		{
			if (Output.returnX < 0)
				Output.returnX = -100;
			if (Output.returnX > 0)
				Output.returnX = 100;

			if (Output.returnY < 0)
				Output.returnY = -100;
			if (Output.returnY > 0)
				Output.returnY = 100;
		}*/

		return Output;
	}


	//signfinder, used for deadzone
	float findSign(float num)
	{
		if (num > 0)
			return 1;
		else if (num < 0)
			return -1;
		else
			return 0;
	}


	//Deadzone due to bad controllers

	float ApplyDZ(float axis, float deadzone)
	{
		return fabs(axis) < deadzone ? 0 : (fabs(axis) - deadzone) / (1	- deadzone) * findSign(axis);
	}

};
