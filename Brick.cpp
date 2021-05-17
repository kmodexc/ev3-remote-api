#include "Brick.h"

// uint16_t Brick::createArray(uint8_t length)
// {
// 	CBuffer buffer;
// 	Command c1(DIRECT_COMMAND_REPLY, msg_cnt++, 1);
// 	c1.arrayCreate8(length);
// 	buffer = sendCommand(c1);
// 	return Command::responseArrayCreate(buffer);
// }

// void Brick::writeArray(uint16_t handle, uint32_t index, uint8_t value)
// {
// 	Command c1(DIRECT_COMMAND_NO_REPLY, msg_cnt++, 0);
// 	c1.arrayWrite(handle,index,value);
// 	sendCommand(c1);
// }

// CBuffer Brick::readArray(uint16_t handle, uint32_t index, uint8_t length)
// {
// 	Command c1(DIRECT_COMMAND_REPLY, msg_cnt++, 0);
// 	c1.arrayMultiRead(handle,index,length);
// 	CBuffer reply = sendCommand(c1);
// 	return Command::responseArrayMultiRead(reply,length);
// }

bool Brick::Initialize()
{
	if (!con.Initialize())
		return false;

	//h_arr_i2c_setup = createArray(3);
	//h_arr_i2c_read = createArray(3);
	//h_arr_i2c_reply = createArray(9);

	return true;
}

CBuffer Brick::sendCommand(Command &com)
{
	CBuffer reply;
	if (com.getType() == DIRECT_COMMAND_REPLY)
	{
		if(!con.Send(com.toBytes(), &reply))
			printf("could not send command\n");
	}else if(!con.Send(com.toBytes())){
		printf("could not send command\n");
	}
	return reply;
}

void Brick::setMotorPower(Output motor, int8_t power)
{
	if (power == 0)
	{
		Command c1(DIRECT_COMMAND_NO_REPLY, msg_cnt++, 0, 0);
		c1.stopMotor((uint8_t)motor);
		sendCommand(c1);
	}
	else
	{
		Command c1(DIRECT_COMMAND_NO_REPLY, msg_cnt++, 0, 0);
		c1.startMotorPower((uint8_t)motor, power);
		c1.startMotor((uint8_t)motor);
		sendCommand(c1);
	}
}

int Brick::getSensorVal(Input port)
{
	Command c1(DIRECT_COMMAND_REPLY, msg_cnt++, 1, 0);
	c1.readSensor((uint8_t)port);
	CBuffer reply = sendCommand(c1);
	return Command::responseReadSensor(reply);
}

CBuffer Brick::getLineReaderValues(Input port)
{
	//Command c1(DIRECT_COMMAND_REPLY, msg_cnt++, 1);
	return CBuffer();
}