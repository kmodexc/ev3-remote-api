#include "Brick.h"
#include <iostream>
using namespace std;

int main(int argc, char **argv)
{
	Brick brick(true);
	int val = 0;

	if (!brick.Initialize())
		return 1;

	Command c1(DIRECT_COMMAND_REPLY, 0, 16, 32);
	c1.arrayCreate8(0, 16);
	c1.arrayCreate8(2, 16);
	c1.arrayCreate8(4, 16);
	
	c1.arrayWrite(0, 0, 2);
	c1.arrayWrite(0, 1, 0x41);
	c1.arrayWrite(0, 2, 'D');
	
	c1.inputDeviceSetup((int)Input::Port1,1,0,3,0,0,2);

	c1.arrayWrite(2, 0, 2);
	c1.arrayWrite(2, 1, 0x49);

	for(int cnt =0;cnt <16;cnt++)
		c1.arrayWrite(4,cnt,0);

	c1.inputDeviceSetup((int)Input::Port1,1,0,2,2,8,4);

	//c1.arrayMultiRead(4, 0, 16);
	CBuffer raw = brick.sendCommand(c1);
	CBuffer data = Command::responseArrayMultiRead(raw, 16);

	if (data.size() > 0)
	{
		for (int cnt = 0; cnt < data.size(); cnt++)
			cout << "data[" << cnt << "]: " << (int)data[cnt] << endl;
	}
	else
		cout << "error no data" << endl;

	return 0;
}