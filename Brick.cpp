#include "Brick.h"

int Brick::sendCommand(Command& com){
	if(com.responseHandler != nullptr)
	{
		CBuffer reply;
		if (!con.Send(com.toBytes(),&reply))
			printf("could not send command\n");
		return com.responseHandler(reply);
	}
	else{
		if (!con.Send(com.toBytes()))
			printf("could not send command\n");
		return INT32_MIN;
	}
}

Brick::Brick(bool debug):
	msg_cnt(0),
	debug(debug),
	con(debug)
{
}

Brick::~Brick()
{
}

bool Brick::Initialize(const char *path)
{
	return con.Initialize(path);
}

void Brick::setMotorPower(Output motor, int8_t power)
{
	if (power == 0)
	{
		Command c1(DIRECT_COMMAND_NO_REPLY, msg_cnt++);
		c1.stopMotor((uint8_t)motor);
		sendCommand(c1);
	}
	else
	{
		Command c1(DIRECT_COMMAND_NO_REPLY, msg_cnt++);
		c1.startMotorPower((uint8_t)motor, power);
		sendCommand(c1);
		Command c2(DIRECT_COMMAND_NO_REPLY, msg_cnt++);
		c2.startMotor((uint8_t)motor);
		sendCommand(c2);
	}
}

int Brick::getSensorVal(Input port)
{
	Command c1(DIRECT_COMMAND_REPLY, msg_cnt++);
	c1.readSensor((uint8_t)port);
	return sendCommand(c1);
}