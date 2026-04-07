#ifndef GPS_SENSOR_H
#define GPS_SENSOR_H

#include "truth_model.h"
#include <random>

class constellation;

// GPS Sensor Class 
class gps {

    public:

        // Default Constructor
        gps();

        // Constructor (Custom Update Rate)
        gps(float dt);

        // Default Destructor
        ~gps();

        // Get stored data
        state data(const simulation& sim);

    private:

        // GPS Parameters
        float dt = 0.5;
        float acqRate = 0.05;
        double x = 0;
        double y = 0;
        double xBias = 0;
        double yBias = 0;

        // Random number generator
        std::mt19937 gen;

        // Acquisition Check
        bool acquisition(const constellation& satConstellation);
        
        // Internal Calculation to add noise (GPS Error)
        void gpsCalculation(const simulation& sim);
};

#endif