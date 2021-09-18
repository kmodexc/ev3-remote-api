#pragma once
#include "Brick.h"
class UltrasonicSensor
{
    Port port;

public:
    UltrasonicSensor(Port port);
    int distance();
};