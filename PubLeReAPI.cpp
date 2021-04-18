#include "PubLeReAPI.h"

void* createBrick()
{
	Brick* brick = new Brick();
	brick->Initialize();
	return brick;
}
void deleteBrick(void * brick)
{
	delete ((Brick*)brick);
}
void setMotorSpeed(void *brick, uint8_t port, int8_t speed)
{
	((Brick*)brick)->setMotorPower(Output(port),speed);
}
int getSensorVal(void *brick, uint8_t port)
{
	return ((Brick*)brick)->getSensorVal(Input(port));
}

extern "C"{
	void* c_createBrick(void){
		return createBrick(); 
	}
}