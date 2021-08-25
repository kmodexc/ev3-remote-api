#pragma once
#include "Brick.h"
class ColorSensor{
	Input port;
public:
	ColorSensor(Input port);
	uint8_t ambient();
};