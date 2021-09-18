#pragma once
#include "Brick.h"
class ColorSensor{
	Port port;
public:
	ColorSensor(Port port);
	uint8_t ambient();
};