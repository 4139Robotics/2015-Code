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
		  returnRotation;
	bool returnRotate;

	//left and right analog sticks
	float leftAnalogX,
		  leftAnalogY,
		  rightAnalogX,
		  rightAnalogY,
		  leftThrottle,
		  rightThrottle;
	//POV hat
	bool POVcenter,
		 POVup,
	     POVupRight,
	 	 POVright,
	 	 POVdownRight,
		 POVdown,
		 POVdownLeft,
		 POVleft,
		 POVupLeft,
	//buttons
		 buttonA,
	     buttonB,
		 buttonX,
		 buttonY,
		 leftTrigger,
		 rightTrigger,
		 back,
		 start;
	//currently arbitrary functions
	bool turbo,
	     grab;
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
		Output.turbo=false;
		Output.grab=false;
		yesMoto = false;
		noMoto = false;
	}
	X360Controller_Out Run(X360Controller_In input)
	{
		//receiving movement && throttle values and setting
		Output.leftAnalogX   = stick->GetRawAxis(0);
		Output.leftAnalogY   = stick->GetRawAxis(1);
		Output.leftThrottle  = stick->GetRawAxis(2);
		Output.rightThrottle = stick->GetRawAxis(3);
		Output.rightAnalogX  = stick->GetRawAxis(4);
		Output.rightAnalogY  = stick->GetRawAxis(5);

		//setting states to POV values
		if(stick->GetPOV()==-1){
			Output.POVcenter=true;
		}
		if(stick->GetPOV()==0){
			Output.POVup=true;
		}
		if(stick->GetPOV()==45){
			Output.POVupRight=true;
		}
		if(stick->GetPOV()==90){
			Output.POVright=true;
		}
		if(stick->GetPOV()==135){
			Output.POVdownRight=true;
		}
		if(stick->GetPOV()==180){
			Output.POVdown=true;
		}
		if(stick->GetPOV()==225){
			Output.POVdownLeft=true;
		}
		if(stick->GetPOV()==270){
			Output.POVleft=true;
		}
		if(stick->GetPOV()==315){
			Output.POVupLeft=true;
		}


		//setting buttons to general functions
		Output.buttonA	    = stick->GetRawButton(0);
		Output.buttonB	    = stick->GetRawButton(1);
		Output.buttonX	    = stick->GetRawButton(2);
		Output.buttonY	    = stick->GetRawButton(3);
		Output.leftTrigger  = stick->GetRawButton(4);
		Output.rightTrigger = stick->GetRawButton(5);
		Output.back			= stick->GetRawButton(6);
		Output.start		= stick->GetRawButton(7);

		//the following (commented out) code is based Etan's preferences for driver control
		Output.returnX = Output.rightThrottle*100-Output.leftThrottle*100;
		Output.returnY = Output.leftAnalogX;




		//doing math for final return values
		Output.returnX =  ApplyDZ(stick->GetRawAxis(1) / (Output.turbo ? 1 : 2), DZ) / (Output.grab ? 2 : 1);
		Output.returnY = -ApplyDZ(stick->GetRawAxis(2) / (Output.turbo ? 1 : 2), DZ) / (Output.grab ? 2 : 1);
		Output.returnRotation = stick->GetZ() / (Output.grab ? 4 : 2);//ApplyDZ(stick->GetZ()/2, DZ);

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
		}

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
