#include "ColorSensor.h"

ColorSensor::ColorSensor(Input port)
{
	this->port = port;
	gBrick.Initialize();
}

uint8_t ColorSensor::ambient()
{
	return gBrick.getSensorVal(port);
}