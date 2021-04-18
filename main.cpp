#include "Brick.h"

// sleep
#include <unistd.h>

#include <chrono>
#include <iostream>

using std::cout;
using std::endl;

using std::chrono::steady_clock;
using std::chrono::duration_cast;
using std::chrono::microseconds;
using std::chrono::nanoseconds;

void stopMotor(Brick &brick)
{
	brick.setMotorPower(Output::A, 0);
	int val = brick.getSensorVal(Input::PortA);
	for (int cnt = 0; cnt < 100; cnt++)
	{
		int cnt2 = 0;
		for (; cnt2 < 10; cnt2++)
		{
			int nval = brick.getSensorVal(Input::PortA);
			if (val != nval)
				break;
		}
		if (cnt2 >= 9)
			return;
	}
	cout << "could not stop motor" << endl;
}

void startMotor(Brick &brick)
{
	brick.setMotorPower(Output::A, 99);
	int val = brick.getSensorVal(Input::PortA);
	for (int cnt = 0; cnt < 1000; cnt++)
	{
		int nval = brick.getSensorVal(Input::PortA);
		if (val != nval)
			return;
	}
	cout << "could not start motor" << endl;
}

int main(int argc, char **argv)
{
	Brick brick;
	int val = 0;

	if (!brick.Initialize("/dev/hidraw2"))
		return 1;

	stopMotor(brick);
	startMotor(brick);
	stopMotor(brick);	

	steady_clock::time_point begin = steady_clock::now();

	startMotor(brick);

	steady_clock::time_point end = steady_clock::now();

	cout << "Time difference = " << duration_cast<microseconds>(end - begin).count() << "[µs]" << endl;
	cout << "Time difference = " << duration_cast<nanoseconds>(end - begin).count() << "[ns]" << endl;

	stopMotor(brick);

	return 0;
}