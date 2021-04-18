#pragma once

#include "BrickDefs.h"
#include "HIDCon.h"
#include "Command.h"

class Brick
{
	HIDCon con;
	uint16_t msg_cnt;
	bool debug;

protected:
	int sendCommand(Command &com);

public:
	Brick(bool debug = false) : msg_cnt(0),
								debug(debug),
								con(debug)
	{
	}
	~Brick() {}
	bool Initialize() { return con.Initialize(); }
	void setMotorPower(Output motor, int8_t power);
	int getSensorVal(Input port);
};