#include "Motor.h"
#include "TouchSensor.h"
#include <iostream>
#include <unistd.h>
using namespace std;

int main(int argc, char **argv)
{
	Motor motora(Port::A);
	Motor motorb(Port::B);
	motora.reset_angle();
	motorb.reset_angle();
	cout << "Motor A angle:" << motora.angle() << endl;
	cout << "Motor B angle:" << motorb.angle() << endl;
	motora.run_target(50,1000);
	motorb.run_target(50,500);
	sleep(3);
	cout << "Motor A angle:" << motora.angle() << endl;
	cout << "Motor B angle:" << motorb.angle() << endl;

	TouchSensor ts(Port::S2);
	cout << "Button is pressed: " << ts.pressed() << endl;

	// Brick brick(true);
	// int val = 0;

	// if (!brick.Initialize())
	// 	return 1;

	// Output port = Output::B;

	// brick.resetTachoCount(port);

	// val = brick.getTachoCount(port);
	// cout << "Motor tacho: " << val << endl;

	// brick.runMotorForAngle(port,50,1000,true);

	// sleep(3);

	// val = brick.getTachoCount(port);
	// cout << "Motor tacho: " << val << endl;

	// cout << "Port2 val: " << brick.getSensorVal(Input::Port2) << endl;

	return 0;
}