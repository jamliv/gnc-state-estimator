#include "truth_model.h"
#include "gps_sensor.h"
#include "constellation.h"
#include "kalman_filter.h"
#include "logger.h"

#include <iostream> 
using namespace std;

int main() {

    // Set time step
    double dt = 0.1; // seconds

    // Initialize Simulation
    simulation sim(dt);

    // Initialize Logger
    string csvFile = "SIM_RUN_DATA.csv";
    string eventFile = "SIM_LOG.txt";
    logger simLog("../data/" + csvFile, "../data/" + eventFile);

    // Initialize GPS Sensor
    gps gpsSensor;

    // Constellation Variables
    int satCount = 8;
    double offset = 15;    // degrees
    double amplitude = 60; // degrees
    double period = 12;    // seconds

    // Initialize Constellation
    constellation satArray(satCount, offset, amplitude, period);

    // The runs required to average and initialize KF
    int runsRequired = 10;

    // Get initial position measurement average
    state initial = gpsSensor.initialConditions(sim, satArray, runsRequired);

    // Kalman Filter Variables (and Tuning)
    double sigmaA = 1.0;
    double sigmaGPS = 3;
    double sigmaPos = 1.0;
    double sigmaVel = 25;

    // Declare and Initialize Kalman Filter
    KalmanFilter kf(dt, sigmaA, sigmaGPS);
    kf.initialize(initial.x, initial.y, sigmaPos, sigmaVel);

    // Set step variables
    int maxSimTime = 20; // seconds

    // Calculate maximum step count 
    int maxStepCount = maxSimTime / dt; 

    // Log Sim Start
    simLog.logEvent(0, "Simulation Start");

    // Initialize Loop Parameters
    int step = 1; // Step 0 was initializing the KF
    double time;

    // Set GPS Loop Parameters
    int gpsSteps = 5;
    bool gpsAvailable;
    state gpsPos;

    // Commence Simulation
    while (step <= maxStepCount) {

        // Set current time
        time = step * dt;

        // Set GPS Availability to False
        gpsAvailable = false;

        // Propagate Simulation
        sim.propagate();

        // Update constellation
        satArray.update(time);

        // Update the Bias in the sensor
        gpsSensor.updateBias();

        // GPS Measurement Check
        if (step % gpsSteps == 0) {

            // Attempt to update GPS Measurement
            if (gpsSensor.update(sim, satArray)) {

                // Extract and flag successful measurement 
                gpsPos = gpsSensor.data();
                gpsAvailable = true;
                simLog.logEvent(time, "GPS Measurement Acquired");

                // Update KF Prediction with GPS Measurement
                kf.step(gpsPos.x, gpsPos.y);
                simLog.logEvent(time, "Kalman Filter Updated with GPS Measurement");
            }

            // Failed to update - do a normal KF Prediction
            else {
                kf.step();
                simLog.logEvent(time, "GPS Lock Failure");
            }
        }

        // Make a normal KF Prediction
        else kf.step();

        // Extract important parameters
        truthState simState = sim.getTruthState();
        state gpsState = gpsSensor.data();
        Eigen::Vector4d kfState = kf.getState();
        Eigen::Matrix4d kfCovariance = kf.getCovariance();
        Eigen::Vector2d kfInnovation = kf.getInnovation();

        LogRow row = buildLogRow(time, simState, gpsState, gpsAvailable, kfState, kfCovariance, kfInnovation);

        // Create row in CSV
        simLog.logStep(row);

        // Increment step count
        ++step;
    }

    // Log Sim End
    simLog.logEvent(time, "Simulation Complete");

    return 0;
}

