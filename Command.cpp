#include "Command.h"
#include "malloc.h"

Command::Command()
	:Command(DIRECT_COMMAND_NO_REPLY,0)
{
}

Command::Command(uint8_t type, uint16_t msg_id)
	: type(type),
	msg_id(msg_id)
{
	data.push_back(0xff);	// size
	data.push_back(0xff);	// size

	data.push_back(msg_id & 0xff);	// sequence
	data.push_back(msg_id >> 8);	// sequence

	data.push_back(type);	// type

	data.push_back(0x0);	// global vars
	data.push_back(0x0);	// local vars
}

Command::~Command(){

}

void Command::startMotor(uint8_t port){
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

std::vector<uint8_t>& Command::toBytes()
{
	COMCMD* cmd = (COMCMD*)data.data();
	
	cmd->CmdSize = data.size()-2;
	//cmd->Cmd = type;
	//cmd->MsgCnt = msg_id;

	// DIRCMD* dcmd = (DIRCMD*)cmd->PayLoad;

	// dcmd->Locals = 0;
	// dcmd->Globals = 0;

	return data;
}