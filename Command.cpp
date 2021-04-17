#include "Command.h"
#include "malloc.h"

Command::Command()
	: Command(DIRECT_COMMAND_NO_REPLY, 1)
{
}

Command::Command(uint8_t type, uint16_t msg_id)
	: type(type),
	  msg_id(msg_id)
{
	data.push_back(0xff); // size
	data.push_back(0xff); // size

	data.push_back(msg_id & 0xff); // sequence
	data.push_back(msg_id >> 8);   // sequence

	data.push_back(type); // type

	data.push_back(0x0); // global vars
	data.push_back(0x0); // local vars
}

Command::~Command()
{
}

void Command::startMotor(uint8_t port)
{
	addOpCode(opOUTPUT_START);
	addParameter(0);
	addParameter(port);
}

void Command::addOpCode(OP code)
{
	this->data.push_back(code);
}

void Command::addParameter(uint8_t param)
{
	data.push_back(sizeof(param));
	data.push_back(param);
}

void Command::addParameter(int8_t param)
{
	data.push_back(sizeof(param));
	data.push_back((uint8_t)param);
}

void Command::addParameter(uint32_t param)
{
	data.push_back(sizeof(param));
	data.push_back(param);
}

void Command::addParameter(int32_t param)
{
	data.push_back(sizeof(param));
	data.push_back((uint32_t)param);
}

void Command::turnMotorAtPowerForTime(uint8_t ports, int8_t power, uint32_t msRampUp, uint32_t msConstant, uint32_t msRampDown, bool brake)
{
	addOpCode(opOUTPUT_TIME_POWER);
	addParameter((uint8_t)0);
	addParameter(ports);
	addParameter(power);
	addParameter(msRampUp);
	addParameter(msConstant);
	addParameter(msRampDown);
	addParameter((uint8_t)(brake ? 0x01 : 0x00));
}

void Command::turnMotorAtPowerForTime(uint8_t ports, int8_t power, uint32_t msConstant)
{
	turnMotorAtPowerForTime(ports, power, 0, msConstant, 0, false);
}

std::vector<uint8_t> &Command::toBytes()
{
	COMCMD *cmd = (COMCMD *)data.data();

	cmd->CmdSize = data.size() - 2;
	//cmd->Cmd = type;
	//cmd->MsgCnt = msg_id;

	// DIRCMD* dcmd = (DIRCMD*)cmd->PayLoad;

	// dcmd->Locals = 0;
	// dcmd->Globals = 0;

	return data;
}