FRC 4139 Robot Instructions
==================
Instructions for the programming team of FRC 4139. This is written in Readme.md, which you can open with Notepad or some other text editor program and read just fine. Please commit/pull/push as needed. Dont forget to write meaningful commit comments, followed with your name. 

Any object you use from the WPILib API should use a pointer, and don't forget to initialize, construct, etc these properly. 
[WPILib Documentation](http://first.wpi.edu/FRC/roborio/release/docs/cpp/)

You should not have to worry about any other class; assume what is sent through the structs is fine. Don't forget to include any files for the classes you will be handling; but I should have added these include statements beforehand.
Talking about structs, please use this naming scheme:
* There should be two structs per file. Basically ClassName_Input (or ClassName_Output). I should have premade these.
* For the Run method (will be described next), the parameter input struct should be named in, the output return struct should be named out.
* When you are using any other struct in the Run method, please use ClassIn (or ClassOut).

The Run method, which should be in every class, will be taking in the respective input struct and returning the respective output struct. Here is an example of what it will look like:
```C++
Class_Output Run(Class_Input in)
{
    Class_Output out; // the output struct of Class
    
    SomeClassINeed_Input SomeClassINeedIn; // creating the structs of SomeClassINeed
    SomeClassINeed_Output SomeClassINeedOut;
    
    SomeClassINeedIn.something = in.something; // passing data in to another class
    out.something = SomeClassINeedOut.something; // passing data out to another class
    
    SomeClassINeed->Run(SomeClassINeedIn); // sending the data to the class and running it
    SomeClassINeedOut = SomeClassINeed->Run(SomeClassINeedIn); // sending data to the class and running it, and then receiving whatever I need
    
    return out; // returning a Class_Output struct
}
```

### Robot.cpp
This is the main robot class. It will handle everything, and process them accordingly. I (Elliot) should be handling this, so don't worry about it too much.

### Input.cpp
This class will manage all the components that receive and send data. So, you will be handling what you recieve from the Sensors and X360Controller class. Just set your out struct to whatever you get and return it.

### Sensors.cpp
This class will receive values from the sensors, set the out struct to these values, and return it. Currently, we will have a gyroscope, the RoboRIO builtin accelerometer, and probably an ultrasonic sensor. We will also have a camera, but I will handle anything vision related.

### X360Controller.cpp
This class will handle the input received from the Xbox 360 controller. Use the Joystick class from the WPILib documentation. Controls are currently undetermined. For now, use the left stick for x and y. The POV hat should each set state to a different value (0 for the center, 1-8 for the outside). You must also set a deadzone; look it up.

### Output.cpp
This class will take in various values, and pass them to the appropriate output classes (currently Wheels and Forklift). Just set the various input structs of the other classes to whatever you are being passed in.

### Wheels.cpp
This class will handle the driving of the robot. We use MecanumDrive_Cartesian. If rotate is true, then the robot should be spinning. Currently, the motor layout is:
* frontLeft: 0
* rearLeft: 2
* frontRight: 1
* rearRight: 3

### Forklift.cpp
This class will handle the lift that lifts the crates. Each state (1-8) will set the forklift to a different height. 

### TBD: Vision 
In progress.