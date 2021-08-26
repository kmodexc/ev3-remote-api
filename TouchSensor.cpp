#include "TouchSensor.h"
TouchSensor::TouchSensor(Input port)
{
	this->port = port;
	gBrick.Initialize();
}
bool TouchSensor::pressed()
{
	return gBrick.getSensorVal(port) > 2000;
}