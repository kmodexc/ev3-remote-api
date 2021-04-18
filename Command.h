#pragma once
#include <vector>
#include <stdint.h>
#include "types.h"

#include "bytecode.h"
#include "c_com.h"

#define BUBYTE unsigned char

class Command{
	CBuffer data;
	uint16_t msg_id;
	uint8_t type;

protected:

	void addOpCode(uint8_t code);
	void addParameter(bool b);
	void addParameter(uint8_t b);
	void addParameter(int8_t b) { addParameter((uint8_t)b); }
	void addParameter(uint32_t b);
	void addParameter(int32_t b) { addParameter((uint32_t)b); }

	Command();
public:
	Command(uint8_t type, uint16_t msg_id);
	~Command();
	void startMotor(uint8_t port);
	void turnMotorAtPowerForTime(uint8_t ports, int8_t power, uint32_t msRampUp, uint32_t msConstant, uint32_t msRampDown, bool brake);
	void turnMotorAtSpeedForAngle(uint8_t ports, int8_t speed, uint32_t stepRampUp, uint32_t stepConstant, uint32_t stepRampDown, bool brake);
	void startMotorPower(uint8_t port, int8_t power);
	CBuffer& toBytes();
};