#include "Brick.h"

Brick::Brick(){
	msg_cnt = 0;
}

Brick::~Brick(){

}

bool Brick::Initialize(const char* path){
	return con.Initialize(path);
}

void Brick::setMotorPower(Output motor,int8_t power){
	Command c1(DIRECT_COMMAND_NO_REPLY,msg_cnt++);
	c1.startMotorPower((uint8_t)motor,power);
	if(!con.Send(c1.toBytes()))
		printf("could not send command\n");
	Command c2(DIRECT_COMMAND_NO_REPLY,msg_cnt++);
	c2.startMotor((uint8_t)motor);
	if(!con.Send(c2.toBytes()))
		printf("could not send command\n");
}

int Brick::getSensorVal(Input port)
{
	Command c1(DIRECT_COMMAND_REPLY,msg_cnt++);
	c1.readSensor((uint8_t)port);
	CBuffer reply;
	if(!con.Send(c1.toBytes(),&reply))
		printf("could not send command\n");
	return c1.responseHandler(reply);
}