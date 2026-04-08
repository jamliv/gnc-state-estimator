#include "logger.h"
#include <iostream>
#include "truth_model.h"
#include "kalman_filter.h"


logger::logger(const std::string& csvFileName, const std::string& eventFileName) {

    // Create log files
    csvFile.open(csvFileName);
    eventFile.open(eventFileName);

    // Attempt to open files
    if (!csvFile.is_open() || !eventFile.is_open()) {
        throw std::runtime_error("Failed to open log files");
    }

    // Make the CSV Header
    csvFile << "time,"
            << "truth_x,truth_y,truth_vx,truth_vy,"
            << "gps_x,gps_y,gps_available,"
            << "kf_x,kf_y,kf_vx,kf_vy,"
            << "err_x,err_y,err_vx,err_vy,"
            << "innov_x,innov_y,"
            << "P_x,P_y,P_vx,P_vy\n";
}

logger::~logger() {
    if (csvFile.is_open()) {
        csvFile.close();
    }

    if (eventFile.is_open()) {
        eventFile.close();
    }
}

void logger::logEvent(double time, const std::string& msg) {

    eventFile << "[" << time << "]" << " " << msg << "\n";
}

void logger::logStep(const LogRow& row) {

    csvFile << row.time << ","

            // Truth
            << row.xTruth << "," << row.yTruth << ","
            << row.vxTruth << "," << row.vyTruth << ","

            // GPS
            << row.xGPS << "," << row.yGPS << ","
            << row.gpsAvailable << ","

            // KF estimate
            << row.xKF << "," << row.yKF << ","
            << row.vxKF << "," << row.vyKF << ","

            // Error
            << row.xErr << "," << row.yErr << ","
            << row.vxErr << "," << row.vyErr << ","

            // Innovation
            << row.xInnov << "," << row.yInnov << ","

            // Covariance
            << row.xCovariance << "," << row.yCovariance << ","
            << row.vxCovariance << "," << row.vyCovariance

            << "\n";
}

LogRow buildLogRow(double time, truthState simState, state gpsState, bool gpsAvailable,
    Eigen::Vector4d kfState, Eigen::Matrix4d kfCovariance, Eigen::Vector2d kfInnovation) {

    LogRow row;
    
    // Set row variables
    row.time = time;

    row.xTruth = simState.x;
    row.yTruth = simState.y;
    row.vxTruth = simState.vx;
    row.vyTruth = simState.vy;

    row.xGPS = gpsState.x;
    row.yGPS = gpsState.y;
    row.gpsAvailable = gpsAvailable;

    row.xKF = kfState(0);
    row.yKF = kfState(1);
    row.vxKF = kfState(2);
    row.vyKF = kfState(3);

    // Calculate Error (KF - Truth)
    row.xErr = row.xKF - row.xTruth;
    row.yErr = row.yKF - row.yTruth;
    row.vxErr = row.vxKF - row.vxTruth;
    row.vyErr = row.vyKF - row.vyTruth;

    row.xInnov = kfInnovation(0);
    row.yInnov = kfInnovation(1);

    row.xCovariance = kfCovariance(0,0);
    row.yCovariance = kfCovariance(1,1);
    row.vxCovariance = kfCovariance(2,2);
    row.vyCovariance = kfCovariance(3,3);

    return row;
}