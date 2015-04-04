/*
 * Sensors.cpp
        Sends various data from the sensors
 *
 *  FRC Team 4139 - Easy as Pi
 *      Author(s): Rhea Bae, Jeffrey Chen
 */

#include "WPILib.h"

struct Sensors_In
{
	bool resetGyro;
};

struct Sensors_Out
{
	float returnGyroAngle;
	float returnAccelX, returnAccelY, returnAccelZ;
	float returnDistance;
	bool returnUpperLiftSwitch, returnLowerLiftSwitch;
};

class Sensors
{
private:
	//Gyro *gyro;
	Accelerometer *accel;
	//DigitalInput *upperLift;
	//DigitalInput *lowerLift;
	//Ultrasonic *sonic;

	/*
	IMAQdxSession session;
	Image *frame;
	IMAQdxError imaqError;
	AxisCamera *camera;
	*/

public:
	Sensors()
	{
		//gyro = new Gyro(3);
		accel = new BuiltInAccelerometer(Accelerometer::kRange_4G); // built in roboRIO accelerometer
		//upperLift = new DigitalInput(999);
		//lowerLift = new DigitalInput(999);
		//sonic = new Ultrasonic(8,9);
		//gyro->Reset();

		//frame = imaqCreateImage(IMAQ_IMAGE_RGB, 0);
		//camera = new AxisCamera("10.41.93.11");
	}

	Sensors_Out Run(Sensors_In input)
	{
		Sensors_Out out;

		//if(input.resetGyro)
		//{
		//	gyro->Reset();
		//}

		//out.returnGyroAngle = gyro->GetAngle();
		out.returnAccelX = accel->GetX();
		out.returnAccelY = accel->GetY();
		out.returnAccelZ = accel->GetZ();
		//out.returnUpperLiftSwitch = upperLift->Get();
		//out.returnLowerLiftSwitch = lowerLift ->Get();
		//out.returnDistance = sonic->GetRangeInches();

		//camera->GetImage(frame);
		//CameraServer::GetInstance()->SetImage(frame);

		return out;
	}
};
