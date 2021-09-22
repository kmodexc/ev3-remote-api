#pragma once
#include "Brick.h"
class GyroSensor
{
    Port port;
    int offset;

public:
    GyroSensor(Port port);
    int angle();
    void reset_angle();
};