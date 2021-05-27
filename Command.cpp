#include "Command.h"
#include "malloc.h"

#include "bytecode.h"
#include "c_com.h"

Command::Command()
	: Command(DIRECT_COMMAND_NO_REPLY, 1, 0,0)
{
}

Command::Command(uint8_t type, uint16_t msg_id, uint8_t cnt_globals, uint8_t cnt_loc)
	: type(type),
	  msg_id(msg_id)
{
	data.push_back(0xff); // size
	data.push_back(0xff); // size

	data.push_back(msg_id & 0xff); // sequence
	data.push_back(msg_id >> 8);   // sequence

	data.push_back(type); // type

	data.push_back(cnt_globals); // global vars
	data.push_back(cnt_loc << 2); // local vars
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

void Command::stopMotor(uint8_t port)
{
	addOpCode(opOUTPUT_STOP);
	addParameter((uint8_t)0);
	addParameter(port);
	addParameter((uint8_t)0);
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
	data.push_back(PRIMPAR_LONG | PRIMPAR_4_BYTES);
	data.push_back((uint8_t)(param & 0xff));
	data.push_back((uint8_t)((param >> 8) & 0xff));
	data.push_back((uint8_t)((param >> 16) & 0xff));
	data.push_back((uint8_t)((param >> 24) & 0xff));
}

void Command::addGlobalVar(uint8_t id)
{
	data.push_back((uint8_t)GV0(id)); // destination where to store return
}

void Command::addLocalVar(uint8_t id)
{
	data.push_back((uint8_t)LV0(id));
}

void Command::addHandle(uint16_t id)
{
	//addLocalVar((uint8_t)id);
	data.push_back((uint8_t)(PRIMPAR_LONG | PRIMPAR_VARIABEL | PRIMPAR_LOCAL | PRIMPAR_HANDLE | PRIMPAR_2_BYTES));
	data.push_back((uint8_t)(id & 0xff));
	data.push_back((uint8_t)((id >> 8) & 0xff));
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

void Command::readSensor(uint8_t port)
{
	addOpCode(opINPUT_DEVICE);
	addParameter((uint8_t)GET_RAW);
	addParameter((uint8_t)0);
	addParameter(port);
	addGlobalVar(0);
}

void Command::arrayCreate8(uint8_t localind,uint32_t length)
{
	addOpCode(opARRAY);
	addParameter((uint8_t)CREATE8);
	addParameter(length);
	addLocalVar(localind);
}

void Command::arrayWrite(uint8_t arr, uint32_t index, uint8_t val)
{
	addOpCode(opARRAY_WRITE);
	addLocalVar(arr);
	addParameter(index);
	addParameter(val);
}

void Command::arrayRead(uint8_t arr, uint32_t index, uint8_t gv_ind)
{
	addOpCode(opARRAY_READ);
	addHandle(arr);
	addParameter(index);
	addGlobalVar(gv_ind);
}

void Command::arrayMultiRead(uint8_t arr, uint32_t index, uint8_t length)
{
	for(int cnt = 0;cnt < length; cnt++){
		arrayRead(arr,index+cnt,cnt);
	}
}

void Command::inputDeviceSetup(uint8_t port, uint8_t repeat, uint16_t time, uint8_t write_size, uint8_t writearr, uint8_t readsize, uint8_t readarr)
{
	addOpCode(opINPUT_DEVICE);
	addParameter((uint8_t)SETUP);
	addParameter((uint8_t)0);
	addParameter(port);
	addParameter(repeat);
	addParameter(time);
	addParameter(write_size);
	addLocalVar(writearr);
	addParameter(readsize);
	addGlobalVar(readarr);
}

int Command::responseReadSensor(CBuffer &data)
{
	if (data[4] != DIRECT_REPLY)
		return -1;
	return data[5];
}

CBuffer Command::responseArrayMultiRead(CBuffer &data, uint8_t length)
{
	if (data[4] != DIRECT_REPLY || (data[0] - 3) != length)
		return CBuffer();
	CBuffer ret(length);
	for(uint8_t cnt=0;cnt < length;cnt++){
		ret[cnt] = data[5+cnt];
	}
	return ret;
}

uint16_t Command::responseArrayCreate(CBuffer &data)
{
	uint16_t val = 0;
	val = data[5];
	val |= data[6] >> 8;
	return val;
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