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


	brick.setMotorSpeed(Output::A,100);
	brick.setMotorSpeed(Output::B,100);
	sleep(2);
	brick.setMotorSpeed(Output::A,0);
	brick.setMotorSpeed(Output::B,0);


	return 0;
}