#include "Brick.h"

// global brick variable used by Motor, ColorSensor and TouchSensor
Brick gBrick;

#define MSG_REPEAT 3

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
	if(initialized)
		return true;

	if (!con.Initialize())
		return false;

	//h_arr_i2c_setup = createArray(3);
	//h_arr_i2c_read = createArray(3);
	//h_arr_i2c_reply = createArray(9);

	initialized = true;

	return true;
}

CBuffer Brick::sendCommand(Command &com)
{
	CBuffer reply;
	if (com.getType() == DIRECT_COMMAND_REPLY)
	{
		if (!con.Send(com.toBytes(), &reply))
			printf("could not send command\n");
	}
	else if (!con.Send(com.toBytes()))
	{
		printf("could not send command\n");
	}
	return reply;
}

void Brick::setMotorSpeed(Output motor, int8_t speed)
{
	for (int cnt = 0; cnt < MSG_REPEAT; cnt++)
	{
		if (speed == 0)
		{
			Command c1(DIRECT_COMMAND_NO_REPLY, msg_cnt++, 0, 0);
			c1.stopOutput((uint8_t)motor, false);
			sendCommand(c1);
		}
		else
		{
			Command c1(DIRECT_COMMAND_NO_REPLY, msg_cnt++, 0, 0);
			c1.setMotorPower((uint8_t)motor, speed);
			c1.startOutput((uint8_t)motor);
			sendCommand(c1);
		}
	}
}

void Brick::runMotorForAngle(Output motor, int8_t speed, int32_t angle, bool brake)
{
	for (int cnt = 0; cnt < MSG_REPEAT; cnt++)
	{
		if (speed == 0)
		{
			Command c1(DIRECT_COMMAND_NO_REPLY, msg_cnt++, 0, 0);
			c1.stopOutput((uint8_t)motor, brake);
			sendCommand(c1);
		}
		else
		{
			Command c1(DIRECT_COMMAND_NO_REPLY, msg_cnt++, 0, 0);
			c1.turnMotorAtSpeedForAngle((uint8_t)motor, speed,0,angle,0,brake);
			c1.startOutput((uint8_t)motor);
			sendCommand(c1);
		}
	}
}

void Brick::runMotorForTime(Output motor, int8_t speed, uint32_t time, bool brake)
{
	for (int cnt = 0; cnt < MSG_REPEAT; cnt++)
	{
		if (speed == 0)
		{
			Command c1(DIRECT_COMMAND_NO_REPLY, msg_cnt++, 0, 0);
			c1.stopOutput((uint8_t)motor, brake);
			sendCommand(c1);
		}
		else
		{
			Command c1(DIRECT_COMMAND_NO_REPLY, msg_cnt++, 0, 0);
			c1.turnMotorAtSpeedForTime((uint8_t)motor, speed,0,time,0,brake);
			c1.startOutput((uint8_t)motor);
			sendCommand(c1);
		}
	}
}

void Brick::brakeMotor(Output motor)
{
	for (int cnt = 0; cnt < MSG_REPEAT; cnt++)
	{
		Command c1(DIRECT_COMMAND_NO_REPLY, msg_cnt++, 0, 0);
		c1.stopOutput((uint8_t)motor, true);
		sendCommand(c1);
	}
}

int32_t Brick::getTachoCount(Output port)
{
	Command c1(DIRECT_COMMAND_REPLY, msg_cnt++, 1, 0);
	c1.getTachoCount((uint8_t)port);
	CBuffer reply = sendCommand(c1);
	return Command::responseTachoCount(reply);
}

void Brick::resetTachoCount(Output motor)
{
	for (int cnt = 0; cnt < MSG_REPEAT; cnt++)
	{
		Command c1(DIRECT_COMMAND_NO_REPLY, msg_cnt++, 0, 0);
		c1.resetOutputTacho((uint8_t)motor);
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