#include "gps_sensor.h"
#include "constellation.h"
#include <random>

gps::gps() : gen(std::random_device{}()) {}

gps::gps(float dt) : gen(std::random_device{}()){
    this->dt = dt;
}

gps::~gps() {};

state gps::data(const simulation& sim) {
    gpsCalculation(sim);
    return {x, y};
}

bool gps::acquisition(const constellation& satConstellation) {

    if (satConstellation.gpsLock()) return true;    
    return false;
}

void gps::gpsCalculation(const simulation& sim) {

    // Set distributions for noise and drift
    std::normal_distribution<double> driftDist(0.0, 0.01);
    std::normal_distribution<double> noiseDist(0.0, 2.0);

    // Calculate current Bias
    xBias += driftDist(gen);
    yBias += driftDist(gen);

    // Get current sim data
    state s = sim.getState();
    double xSim = s.x;
    double ySim = s.y;

    // Calculate GPS Measurement
    x = xSim + xBias + noiseDist(gen);
    y = ySim + yBias + noiseDist(gen);
}