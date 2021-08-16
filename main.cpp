#include "Brick.h"
#include <iostream>
#include <unistd.h>
using namespace std;

int main(int argc, char **argv)
{
	Brick brick(true);
	int val = 0;

	if (!brick.Initialize())
		return 1;


	brick.setMotorPower(Output::A,100);
	brick.setMotorPower(Output::B,100);
	sleep(2);
	brick.setMotorPower(Output::A,0);
	brick.setMotorPower(Output::B,0);


	return 0;
}