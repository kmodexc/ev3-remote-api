#pragma once

#include "BrickDefs.h"
#include "HIDCon.h"
#include "Command.h"

class Brick
{
	HIDCon con;
	uint16_t msg_cnt;
	bool debug;
	bool initialized;

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
								con(debug),
								initialized(false)
	{
	}
	~Brick() {}
	bool Initialize();

	// motors
	void setMotorSpeed(Output motor, int8_t speed);
	void runMotorForAngle(Output motor, int8_t speed, int32_t angle, bool brake);
	void runMotorForTime(Output motor, int8_t speed, uint32_t time, bool brake);
	void brakeMotor(Output motor);
	int32_t getTachoCount(Output motor);
	void resetTachoCount(Output motor);
	
	// sensors 
	int getSensorVal(Port port);
	CBuffer getLineReaderValues(Port port);
};

extern Brick gBrick;