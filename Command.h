#pragma once
#include "bytecode.h"
#include "c_com.h"
#include <vector>
#include <stdint.h>

#define BUBYTE unsigned char

class Command{
	std::vector<uint8_t> data;
	uint16_t msg_id;
	uint8_t type;

protected:

	void addOpCode(OP code);
	void addParameter(bool b);
	void addParameter(uint8_t b);
	void addParameter(int8_t b);
	void addParameter(uint32_t b);
	void addParameter(int32_t b);

	Command();
public:
	Command(uint8_t type, uint16_t msg_id);
	~Command();
	void startMotor(uint8_t port);
	void turnMotorAtPowerForTime(uint8_t ports, int8_t power, uint32_t msRampUp, uint32_t msConstant, uint32_t msRampDown, bool brake);
	void turnMotorAtPowerForTime(uint8_t ports, int8_t power, uint32_t msConstant);
	std::vector<uint8_t>& toBytes();
};