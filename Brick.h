#pragma once

#include "BrickDefs.h"
#include "HIDCon.h"
#include "Command.h"

class Brick{
	HIDCon con;
	uint16_t msg_cnt;
	bool debug;
protected:
	int sendCommand(Command& com);
public:
	Brick(bool debug=false);
	~Brick();
	bool Initialize(const char* path);
	bool Initialize() { return Initialize("/dev/hidraw0"); }
	void setMotorPower(Output motor,int8_t power);
	int getSensorVal(Input port);
};