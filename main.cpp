#include "Brick.h"

// sleep
#include <unistd.h>

int main(int argc, char **argv)
{
	Brick brick;
	
	if(!brick.Initialize("/dev/hidraw2"))
		return 1;

	for(int cnt=0;cnt<4;cnt++){
		int val = brick.getSensorVal((Input)cnt);
		printf("sensor %d val is %d\n",(int32_t)cnt, (int32_t)val);
	}
	

	// brick.setMotorPower(Output::A,50);

	// sleep(1);

	// brick.setMotorPower(Output::A,0);

	// sleep(1);

	// brick.setMotorPower(Output::A,-50);

	// sleep(1);

	// brick.setMotorPower(Output::A,0);

	return 0;
}