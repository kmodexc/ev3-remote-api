#include "GyroSensor.h"
GyroSensor::GyroSensor(Port port)
{
    this->port = port;
    offset = 0;
    gBrick.Initialize();
}
int GyroSensor::angle()
{
    return gBrick.getSensorVal(port) - offset;
}
void GyroSensor::reset_angle()
{
    offset = angle();
}