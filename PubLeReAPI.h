#include "Brick.h"

void *createBrick();
void deleteBrick(void *);
void setMotorSpeed(void *, uint8_t port, int8_t speed);
int getSensorVal(void *, uint8_t port);

extern "C"{
	void* c_createBrick(void);
}
