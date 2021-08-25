#pragma once
#include "Brick.h"
class TouchSensor{
	Input port;
public:
	TouchSensor(Input port);
	bool pressed();
};