#include "Brick.h"

int Brick::sendCommand(Command& com){
	if(com.responseHandler != nullptr)
	{
		CBuffer reply;
		if (!con.Send(com.toBytes(),&reply)){
			printf("could not send command\n");
			return INT32_MIN;
		}
		return com.responseHandler(reply);
	}
	else{
		if (!con.Send(com.toBytes()))
			printf("could not send command\n");
		return INT32_MIN;
	}
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
		c1.startMotor((uint8_t)motor);
		sendCommand(c1);
	}
}

int Brick::getSensorVal(Input port)
{
	Command c1(DIRECT_COMMAND_REPLY, msg_cnt++);
	c1.readSensor((uint8_t)port);
	return sendCommand(c1);
}