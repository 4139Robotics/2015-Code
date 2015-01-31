#ifndef INPUT_H
#define INPUT_H
struct Input_In
{
    public:
	X360Controller_Out xbout;
	Sensors_Out sensout;
};

struct Input_Out
{
    public:
	// X360Controller
	float returnX, returnY, returnRotation;
	bool returnRotate;

	// Sensors
	float returnGyroAngle;
	float returnAccelX, returnAccelY, returnAccelZ;
	float returnDistance;
};

class Input
{
    public:
        static Input_Out Run(Input_In in);

};

#endif
