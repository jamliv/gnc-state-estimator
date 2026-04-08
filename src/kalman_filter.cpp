#include "kalman_filter.h"
#include <iostream>

KalmanFilter::KalmanFilter(double dt, double sigmaA, double sigmaGPS) : dt(dt), initialized(false) {

    // Create F Matrix
    F << 1, 0, dt, 0,
         0, 1, 0, dt,
         0, 0, 1,  0,
         0, 0, 0,  1;

    // Create H Matrix
    H << 1, 0, 0, 0,
         0, 1, 0, 0;

    // Calculate dt^2,3,4
    double dtPow2 = dt * dt;
    double dtPow3 = dtPow2 * dt;
    double dtPow4 = dtPow3 * dt;

    // Create Q matrix
    Q << dtPow4/3, 0, dtPow3/2, 0,
         0, dtPow4/3, 0, dtPow3/2,
         dtPow3/2, 0, dtPow2, 0,
         0, dtPow3/2, 0, dtPow2;

    // Multiply Q Matrix by sigmaA^2
    double aSigmaPow2 = sigmaA * sigmaA;
    Q *= aSigmaPow2;

    // Calculate GPS Variance
    double gpsSigmaPow2 = sigmaGPS * sigmaGPS;

    // Create R Matrix
    R << gpsSigmaPow2, 0,
         0, gpsSigmaPow2;

    // Initialize Innovation to Dummy Numbers
    innovation << 0, 0;
}

KalmanFilter::~KalmanFilter() {}

// TODO: Think of a better solution for this
void KalmanFilter::step() {

    // Initialization check
    if (!initialized) {
        throw std::runtime_error("Kalman Filter not initialized.");
        return;
    }

    // Make prediction
    predict();
}

void KalmanFilter::step(double xGPS, double yGPS) {

    // Call step()
    step();

    // Update prediction
    update(xGPS, yGPS);
}

Eigen::Vector4d KalmanFilter::getState() const {
    return xHat;
}

Eigen::Matrix4d KalmanFilter::getCovariance() const {
    return P;
}

Eigen::Vector2d KalmanFilter::getInnovation() const {
    return innovation;
}

void KalmanFilter::initialize(double x0, double y0, double sigmaPos, double sigmaVel) {

    // Initialize xHat
    xHat << x0, y0, 0, 0;

    // Calculate variances
    double sigmaPosPow2 = sigmaPos * sigmaPos;
    double sigmaVelPow2 = sigmaVel * sigmaVel;

    // Create Covariance Matrix, P
    P << sigmaPosPow2, 0, 0, 0,
         0, sigmaPosPow2, 0, 0,
         0, 0, sigmaVelPow2, 0,
         0, 0, 0, sigmaVelPow2;

    // Set initialized flag
    initialized = true;
}

void KalmanFilter::predict() {

    // Predict the new state
    xHat = F * xHat;

    // Update Covariance Matrix
    P = F * P * F.transpose() + Q;
}

void KalmanFilter::update(double xGPS, double yGPS) {

    // Place GPS Measurements into a vector
    Eigen::Vector2d gpsMeasurement;
    gpsMeasurement << xGPS, yGPS;

    // Calculate innovation (measurement residual)
    innovation = gpsMeasurement - H * xHat;

    // Create a matrix for part of the function 
    Eigen::Matrix2d partial = H * P * H.transpose() + R;

    // Calculate Kalman Gain
    Eigen::Matrix<double, 4, 2> K = P * H.transpose() * partial.inverse();

    // Correct state estimate using measurement
    xHat = xHat + K * innovation;

    // Create an Identity Matrix
    Eigen::Matrix4d I = Eigen::Matrix4d::Identity();

    // Update Covariance Matrix
    P = (I - K * H) * P * (I - K * H).transpose() + K * R * K.transpose();
}