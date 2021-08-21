#include "Motor.h"

Brick gBrick;

Motor::Motor(Output port)
{
	gBrick.Initialize();
	this->port = port;
}
void Motor::stop()
{
	gBrick.setMotorSpeed(port,0);
}
void Motor::brake()
{
	gBrick.brakeMotor(port);
}
void Motor::run(uint8_t speed)
{
	gBrick.setMotorSpeed(port,speed);
}
void Motor::run_time(uint8_t speed, uint32_t time, Then then)
{
	gBrick.runMotorForTime(port, speed, time, (then == Then::Brake || then == Then::Hold ? true : false));
}
void Motor::run_angle(uint8_t speed, uint32_t angle, Then then)
{
	gBrick.runMotorForAngle(port, speed, angle, (then == Then::Brake || then == Then::Hold ? true : false));
}