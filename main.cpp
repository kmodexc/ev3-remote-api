#include "Brick.h"

// sleep
#include <unistd.h>

int main(int argc, char **argv)
{
	Brick brick;
	
	if(!brick.Initialize("/dev/hidraw0"))
		return 1;

	brick.setMotorPower(Output::A,50);

	sleep(1);

	brick.setMotorPower(Output::A,0);

	sleep(1);

	brick.setMotorPower(Output::A,-50);

	sleep(1);

	brick.setMotorPower(Output::A,0);

	return 0;
}