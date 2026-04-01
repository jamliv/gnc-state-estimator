#include "truth_model.h"
#include "gps_sensor.h"

gps::gps() {}

gps::gps(float dt) {
    this->dt = dt;
}

gps::gps(float acqRate) {
    this->acqRate = acqRate;
}

gps::~gps() {};

state gps::data() {
    return {x, y};
}

bool gps::acquisition() {

    
}