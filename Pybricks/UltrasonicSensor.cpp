#include "UltrasonicSensor.h"
UltrasonicSensor::UltrasonicSensor(Port port){
    this->port = port;
    gBrick.Initialize();
}
int UltrasonicSensor::distance(){
    return gBrick.getSensorVal(this->port);
}