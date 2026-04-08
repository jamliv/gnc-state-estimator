#include "constellation.h"
#include <cmath>
#include <iostream>
#include <random>

//====================================================//
//                    SATELLITE                       //
//====================================================//

satellite::satellite(int identification, double offset, double amplitude, double period, int count) 
    : id(identification) {

    // Random generator shared for satellite construction
    static std::mt19937 gen(std::random_device{}());

    // Convert degrees to radians when needed
    double deg2rad = PI / 180.0;

    // Small random perturbations
    std::uniform_real_distribution<double> phaseJitter(-10.0 * deg2rad, 10.0 * deg2rad);
    std::uniform_real_distribution<double> offsetJitter(-4.0, 4.0);
    std::uniform_real_distribution<double> amplitudeJitter(-4.0, 4.0);

    // Set satellite-specific parameters
    this->offset = offset + offsetJitter(gen);
    this->amplitude = amplitude + amplitudeJitter(gen);

    // Calculate angular velocity
    omega = 2 * PI / period;

    // Base evenly spaced phase
    double basePhase = (2 * PI * identification) / count;

    // Add phase perturbation
    phase = basePhase + phaseJitter(gen);

    // Perform initial elevation calculation
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
    for (satellite& sat : satellites) sat.update(time);
}

bool constellation::gpsLock() const {

    if (operationalCount() >= 4) return true;
    return false;
}

int constellation::operationalCount() const {
    
    int valid = 0;
    for (const satellite& sat: satellites) {
        if (sat.usable()) ++valid;
    }

    return valid;
}