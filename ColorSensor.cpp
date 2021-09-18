#include "ColorSensor.h"

ColorSensor::ColorSensor(Port port)
{
	this->port = port;
	gBrick.Initialize();
}

uint8_t ColorSensor::ambient()
{
	return gBrick.getSensorVal(port);
}