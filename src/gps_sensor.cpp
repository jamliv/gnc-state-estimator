#include "gps_sensor.h"
#include "constellation.h"
#include <random>
#include <iostream>

gps::gps() 
    : gen(std::random_device{}()), pos({0, 0}), xBias(0), yBias(0) {}

gps::~gps() {};

state gps::initialConditions(const simulation& sim, constellation& satConstellation, int runs) {

    // Set Loop Variables
    int successfulAcqs = 0;
    int maxAttempts = 30;
    int attempts = 0;

    // Set Time Variables
    double simTime = 0.0;      // time for constellation only
    double dtConst = 0.1;      // constellation update rate
    double dtGPS = 1.0;        // GPS attempt rate
    double gpsTimer = 0.0;

    // Sum variables
    double xSum = 0.0;
    double ySum = 0.0;

    while (successfulAcqs < runs && attempts < maxAttempts) {

        // Update constellation continuously
        satConstellation.update(simTime);

        // Accumulate time until next GPS attempt
        gpsTimer += dtConst;

        if (gpsTimer >= dtGPS) {
            gpsTimer = 0.0;
            ++attempts;

            if (acquisition(satConstellation)) {
                measure(sim); 
                xSum += pos.x;
                ySum += pos.y;
                ++successfulAcqs;
            }
        }

        simTime += dtConst;
    }

    if (successfulAcqs < runs) {
        throw std::runtime_error("Failed to complete initialization GPS measurements.");
    }

    // Return average
    return {xSum / runs, ySum / runs};
}

bool gps::update(const simulation& sim, constellation& satConstellation) {
    
    // Attempt to acquire ; if failure, return false
    if (!acquisition(satConstellation)) return false;

    // If successful, measure data
    measure(sim);

    // Return success flag (data is prepped for extraction)
    return true;
}

void gps::updateBias() {

    // Set distribution for drift
    std::normal_distribution<double> driftDist(0.0, 0.01);

    // Calculate current Bias
    xBias += driftDist(gen);
    yBias += driftDist(gen);
}

state gps::data() const {
    return pos;
}

bool gps::acquisition(const constellation& satConstellation) {
    return satConstellation.gpsLock();
}

void gps::measure(const simulation& sim) {

    // Set distribution for noise
    std::normal_distribution<double> noiseDist(0.0, 2.0);

    // Get current sim data
    state s = sim.getState();
    double xSim = s.x;
    double ySim = s.y;

    // Calculate GPS Measurement
    pos.x = xSim + xBias + noiseDist(gen);
    pos.y = ySim + yBias + noiseDist(gen);
}