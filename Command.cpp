#include "Command.h"
#include "malloc.h"

#include "bytecode.h"
#include "c_com.h"

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
	addParameter((uint8_t)0);
	addParameter(port);
}

void Command::addOpCode(uint8_t code)
{
	this->data.push_back(code);
}

void Command::addParameter(uint8_t param)
{
	data.push_back(0x81);
	data.push_back(param);
}

void Command::addParameter(uint32_t param)
{
	data.push_back(0x83);
	data.push_back((uint8_t)(param & 0xff));
	data.push_back((uint8_t)((param >> 8) & 0xff));
	data.push_back((uint8_t)((param >> 16) & 0xff));
	data.push_back((uint8_t)((param >> 24) & 0xff));
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

void Command::turnMotorAtSpeedForAngle(uint8_t ports, int8_t speed, uint32_t stepRampUp, uint32_t stepConstant, uint32_t stepRampDown, bool brake)
{
	addOpCode(opOUTPUT_STEP_SPEED);
	addParameter((uint8_t)0);
	addParameter(ports);
	addParameter(speed);
	addParameter(stepRampUp);
	addParameter(stepConstant);
	addParameter(stepRampDown);
	addParameter((uint8_t)(brake ? 0x01 : 0x00));
}

void Command::startMotorPower(uint8_t port, int8_t power)
{
	addOpCode(opOUTPUT_SPEED);
	addParameter((uint8_t)0);
	addParameter(port);
	addParameter(power);
}

void Command::readSensor(uint8_t port){
	addOpCode(opINPUT_DEVICE);
	addParameter((uint8_t)GET_RAW);
	addParameter((uint8_t)0);
	addParameter(port);
	data.push_back((uint8_t)GV0(0));	// destination where to store return
	data[5] += 1;					// state that you want to use a global variable
	responseHandler = responseReadSensor;
}

int Command::responseReadSensor(CBuffer& data)
{
	if(data[4] != DIRECT_REPLY)
		return -1;
	return data[5];
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