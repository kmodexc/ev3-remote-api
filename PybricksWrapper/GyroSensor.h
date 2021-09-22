#pragma once
#include "Brick.h"
class GyroSensor
{
    Port port;

public:
    GyroSensor(Port port);
    int angle();
};