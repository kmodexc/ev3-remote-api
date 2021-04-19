#include "Brick.h"

// sleep
#include <unistd.h>

#include <chrono>
#include <iostream>

#include <thread>

using std::cout;
using std::endl;

using std::chrono::duration_cast;
using std::chrono::microseconds;
using std::chrono::nanoseconds;
using std::chrono::steady_clock;

using namespace std::this_thread;

void stopMotor(Brick &brick)
{
	for (int trys = 0; trys < 2; trys++)
	{
		brick.setMotorPower(Output::A, 0);
		int val = 0;
		for (int cnt = 0; cnt < 1000; cnt++)
		{
			int cnt2 = 0;
			for (; cnt2 < 10; cnt2++)
			{
				sleep_for(microseconds(100));
				int nval = brick.getSensorVal(Input::PortA);
				if (val != nval)
				{
					val = nval;
					break;
				}
			}
			if (cnt2 >= 9)
				return;
		}
		cout << "could not stop motor try" << trys << endl;
	}
	cout << "could not stop motor failed" << endl;
}

void startMotor(Brick &brick)
{
	for (int trys = 0; trys < 2; trys++)
	{
		brick.setMotorPower(Output::A, 99);

		sleep_for(microseconds(1000));

		int val = brick.getSensorVal(Input::PortA);
		for (int cnt = 0; cnt < 1000; cnt++)
		{
			//sleep_for(microseconds(1000));
			int nval = brick.getSensorVal(Input::PortA);
			if (val != nval)
				return;
		}
		cout << "could not start motor try" << trys << endl;
	}
	cout << "could not start motor failed" << endl;
}

int main(int argc, char **argv)
{
	Brick brick(false);
	int val = 0;

	if (!brick.Initialize())
		return 1;

	steady_clock::time_point begin = steady_clock::now();


	startMotor(brick);

	val = brick.getSensorVal(Input::Port1);

	steady_clock::time_point end = steady_clock::now();

	cout << "val is " << val << endl;

	cout << "Time difference = " << duration_cast<microseconds>(end - begin).count() << "[µs]" << endl;
	cout << "Time difference = " << duration_cast<nanoseconds>(end - begin).count() << "[ns]" << endl;

	sleep(1);

	stopMotor(brick);

	return 0;
}