#ifndef GPS_SENSOR_H
#define GPS_SENSOR_H

#include "truth_model.h"
#include <random>

class constellation;

// GPS Sensor Class 
class gps {

    public:

        //====================================================//
        //                    FUNCTIONS                       //
        //====================================================//

        /**
         * @brief Construct a new GPS Sensor
         * 
         */
        gps();

        /**
         * @brief Destroy the gps object
         * 
         */
        ~gps();

        /**
         * @brief Conducts the initial N (runs) measurements required for Kalman Filter initialization
         * 
         * @param sim Simulation (Truth Model)
         * @param satConstellation Satellite Constellation
         * @param runs Number of runs required for Kalman Filter initialization
         * @return Average of N (runs) runs at initial position
         */
        state initialConditions(const simulation& sim, constellation& satConstellation, int runs); 

        /**
         * @brief Updates the GPS internal measurement upon success of acquisition
         * 
         * If acquision fails, return failure flag.
         * 
         * If successful, data is ready for extraction.
         * 
         * @param sim Simulation (Truth Model)
         * @param satConstellation Satellite Constellation
         * @return Success Flag for update
         */
        bool update(const simulation& sim, constellation& satConstellation);

        /**
         * @brief Updates the bias
         * 
         */
        void updateBias();

        /**
         * @brief Returns the stored state data
         * 
         * @return GPS State Measurement
         */
        state data() const;

    private:

        //====================================================//
        //                    PARAMETERS                      //
        //====================================================//

        /**
         * @brief GPS State Measurement
         * 
         */
        state pos;

        /**
         * @brief Bias in the x-direction
         * 
         * This value will be updated with a drift value every timestep.
         * 
         */
        double xBias;

        /**
         * @brief Bias in the y-direction
         * 
         * This value will be updated with a drift value every timestep.
         * 
         */
        double yBias;

        /**
         * @brief Random number generator used to generate random noise and drift
         * 
         */
        std::mt19937 gen;

        //====================================================//
        //                    FUNCTIONS                       //
        //====================================================//

        /**
         * @brief Determines if GPS has confirmed acquisition of satellites
         * 
         * GPS Requires a minimum of four satellites for successful acquisition.
         * Checks Constellation satellites to confirm GPS lock.
         * 
         * @param satConstellation Satellite Constellation
         * @return GPS Lock Flag
         */
        bool acquisition(const constellation& satConstellation);
        
        /**
         * @brief Measures the position
         * 
         * Takes data from simulation then adds a noise and bias error. Stores measurements
         * in pos parameter.
         * 
         * @param sim Simulation (Truth Model)
         */
        void measure(const simulation& sim);
};

#endif