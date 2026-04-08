#ifndef LOGGER_H
#define LOGGER_H

#include "truth_model.h"
#include "kalman_filter.h"

#include <fstream>
#include <string>

/**
 * @brief Struct that sets up the row for Logger to use to input into the CSV file
 * 
 */
struct LogRow {

    // Simulation Time
    double time;

    // Truth state
    double xTruth;
    double yTruth;
    double vxTruth;
    double vyTruth;

    // GPS measurement
    double xGPS;
    double yGPS;
    bool gpsAvailable;

    // Kalman Filter estimate
    double xKF;
    double yKF;
    double vxKF;
    double vyKF;

    // Estimation error (kf - truth)
    double xErr;
    double yErr;
    double vxErr;
    double vyErr;

    // Innovation (measurement residual)
    double xInnov;
    double yInnov;

    // Covariance (diagonal of P)
    double xCovariance;
    double yCovariance;
    double vxCovariance;
    double vyCovariance;
};

LogRow buildLogRow(double time, truthState simState, state gpsState, bool gpsAvailable,
    Eigen::Vector4d kfState, Eigen::Matrix4d kfCovariance, Eigen::Vector2d kfInnovation);

class logger {

    public: 

        logger(const std::string& csvFileName, const std::string& eventFileName);

        ~logger();

        void logEvent(double time, const std::string& msg);

        void logStep(const LogRow& row);

    private:

        std::ofstream csvFile;
        std::ofstream eventFile;

};




#endif