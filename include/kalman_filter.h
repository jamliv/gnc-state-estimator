#ifndef KALMAN_FILTER_H
#define KALMAN_FILTER_H

#include <eigen3/Eigen/Dense>

class KalmanFilter {

    public:

        //====================================================//
        //                    FUNCTIONS                       //
        //====================================================//

        /**
         * @brief Construct a new Kalman Filter object
         * 
         * Sets the time step used by the Kalman Filter. 
         * 
         * Constructs F, H, Q (based on sigmaA), and R (based on sigmaGPS).
         * 
         * @param dt Time Step [float]
         * @param sigmaA Standard Deviation of Acceleration Error [double]
         * @param sigmaGPS Standard Deviation of GPS Error/Noise [double]
         */
        KalmanFilter(float dt, double sigmaA, double sigmaGPS);

        /**
         * @brief Destroy the Kalman Filter object
         * 
         */
        ~KalmanFilter();

        void initialize(double x0, double y0, double sigmaPos, double sigmaVel);

        /**
         * @brief Step function with no GPS Measurement
         * 
         * Calls predict() function.
         * 
         */
        void step();

        /**
         * @brief Step function with GPS Measurement
         * 
         * Calls predict() and update() functions.
         * 
         * @param xGPS Position (x) from GPS Measurement [double]
         * @param yGPS Position (y) from GPS Measurement [double]
         */
        void step(double xGPS, double yGPS);

        /**
         * @brief Get the State Vector
         * 
         * @return Current State Vector [Eigen::Vector4d]
         */
        Eigen::Vector4d getState() const;


    private:

        //====================================================//
        //                    PARAMETERS                      //
        //====================================================//

        /**
         * @brief State Vector
         * 
         */
        Eigen::Vector4d xHat;

        /**
         * @brief Covariance Matrix
         * 
         */
        Eigen::Matrix4d P;

        /**
         * @brief Time step used by Kalman Filter
         * 
         */
        float dt;

        /**
         * @brief Checks if the State Vector and Covariance Matrix have been initialized
         * 
         */
        bool initialized;

        /**
         * @brief Process Noise Covariance
         * 
         * The covariance associated with the noise due to neglecting acceleration
         * in motion model calculation.
         * 
         */
        Eigen::Matrix4d Q;

        /**
         * @brief Measurement Noise Covariance
         * 
         * The covariance associated with the noise due to instrumentation.
         * 
         */
        Eigen::Matrix2d R;

        /**
         * @brief State Matrix
         * 
         * Propagates State Vector and stores in matrix.
         * 
         */
        Eigen::Matrix4d F;

        /**
         * @brief Measurement Matrix
         * 
         * Accounts for the parameters in State Vector associated with a 
         * given instrumentation.
         * 
         */
        Eigen::Matrix<double, 2, 4> H;

        //====================================================//
        //                    FUNCTIONS                       //
        //====================================================//

        /**
         * @brief Prediction step of the Kalman Filter
         *
         * Propagates the state estimate (xHat) forward in time using the motion model
         * (constant velocity). Also updates the covariance matrix (P) to reflect
         * increased uncertainty due to process noise.
         */
        void predict();

        /**
         * @brief Correction step of the Kalman Filter using GPS measurements
         *
         * Updates the predicted state estimate (xHat) and covariance matrix (P)
         * using GPS position measurements. Incorporates measurement uncertainty
         * to correct the prediction.
         * 
         * @param xGPS Position (x) from GPS Measurement [double]
         * @param yGPS Position (y) from GPS Measurement [double]
         */
        void update(double xGPS, double yGPS);
};

#endif