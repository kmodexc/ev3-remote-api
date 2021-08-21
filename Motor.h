#pragma once
#include "Brick.h"

class Motor{
	static Brick gBrick;
	Output port;
public:
	Motor();
	void stop();
	void brake();
	void run(uint8_t speed);
	void run_time(uint8_t speed, uint32_t time, Then then = Then::Hold, bool wait=true);
	void run_angle(uint8_t speed, uint32_t angle, Then then = Then::Hold, bool wait=true);
};