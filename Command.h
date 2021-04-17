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
public:
	Command();
	Command(uint8_t type, uint16_t msg_id);
	~Command();
	void addOpCode(OP code);
	void addParameter(uint8_t b);
	void startMotor(uint8_t port);
	std::vector<uint8_t>& toBytes();
};