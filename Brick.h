#pragma once

#include "BrickDefs.h"
#include "HIDCon.h"
#include "Command.h"

class Brick
{
	HIDCon con;
	uint16_t msg_cnt;
	bool debug;

	uint16_t h_arr_i2c_setup;
	uint16_t h_arr_i2c_read;
	uint16_t h_arr_i2c_reply;

public:
	CBuffer sendCommand(Command &com);
	// uint16_t createArray(uint8_t length);
	// void writeArray(uint16_t handle, uint32_t index, uint8_t value);
	// CBuffer readArray(uint16_t handle, uint32_t index, uint8_t length);

public:
	Brick(bool debug = false) : msg_cnt(0),
								debug(debug),
								con(debug)
	{
	}
	~Brick() {}
	bool Initialize();
	void setMotorPower(Output motor, int8_t power);
	int getSensorVal(Input port);
	CBuffer getLineReaderValues(Input port);
};