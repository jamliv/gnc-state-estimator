#include "constellation.h"
#include <cmath>

//====================================================//
//                    SATELLITE                       //
//====================================================//

satellite::satellite(int identification, double offset, double amplitude, double period, int count) 
: id(identification), offset(offset), amplitude(amplitude) {

    // Calculate Angular Velocity
    omega = 2 * PI / period;

    // Calculate the Phase Shift
    phase = (2 * PI * identification) / count;

    // Perform initial Elevation calculation
    update(0.0);
}

satellite::~satellite() {}

bool satellite::usable() const {
    if (elevation >= 10) return true;
    return false;
}

void satellite::update(double time) {

    // Elevation equation is as follow:
    //      elevation = Offset + Amplitude * sin(AngVel * t + PhaseShift)
    elevation = offset + amplitude * sin(omega * time + phase);
}

int satellite::getID() {
    return id;
}

//====================================================//
//                  CONSTELLATION                     //
//====================================================//

constellation::constellation(int count, double offset, double amplitude, double period) {

    // Create [count] satellites for the constellation
    for (int i = 0; i < count; ++i) {
        satellites.push_back(satellite(i, offset, amplitude, period, count));
    }
}

constellation::~constellation() {}

void constellation::update(double time) {

    // Update each satellite
    for (satellite sat : satellites) sat.update(time);
}

bool constellation::gpsLock() const {

    if (operationalCount() >= 4) return true;

    return false;
}

int constellation::operationalCount() const {
    
    int valid = 0;
    for (satellite sat: satellites) {
        if (sat.usable()) ++valid;
    }

    return valid;
}