#pragma once
#include "Brick.h"
class TouchSensor{
	Port port;
public:
	TouchSensor(Port port);
	bool pressed();
};