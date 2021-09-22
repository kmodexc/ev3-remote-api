#include "GyroSensor.h"
GyroSensor::GyroSensor(Port port)
{
    this->port = port;
    gBrick.Initialize();
}
int GyroSensor::angle()
{
    return gBrick.getSensorVal(port);
}