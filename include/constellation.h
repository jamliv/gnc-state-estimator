#ifndef CONSTELLATION_H
#define CONSTELLATION_H

#include <vector>

using namespace std;
const double PI = 3.141592653589793;

class satellite {

    public:

        //====================================================//
        //                    PARAMETERS                      //
        //====================================================//

        /**
         * @brief Identification Number of satellite.
         * 
         */
        int id;

        /**
         * @brief Elevation of satellite in degrees.
         * 
         */
        double elevation; 

        /**
         * @brief Offset used by satellite in degrees.
         * 
         * Offset is used to shift the satellites up to increase
         * visibility for the sake fo the project.
         * 
         * Using 20 degrees as default.
         * 
         */
        double offset;

        /**
         * @brief Amplitude used by satellite in degrees.
         * 
         * Amplitude is used to increase the trajectory of satellite.
         * Currently set to 60 degrees.
         * 
         */
        double amplitude;

        /**
         * @brief Phase Shift used by satellite in radians.
         * 
         * Phase Shift is used to differentiate the satellites from
         * each other. Calculated using the equation:
         * 
         * Phase = (2 * PI * id) / SatelliteCount
         * 
         */
        double phase;

        /**
         * @brief Angular Velocity used by satellite in radians / sec.
         * 
         * Calculated through period as follows:
         * 
         * AngVel = 2 * PI / period
         * 
         */
        double omega;

        //====================================================//
        //                    FUNCTIONS                       //
        //====================================================//

        /**
         * @brief Construct a new satellite object
         * 
         * @param identification Identification Number of satellite
         * @param offset Offset (degrees) 
         * @param amplitude Amplitude (degrees)
         * @param period Period (s)
         * @param count Total satellite count
         */
        satellite(int identification, double offset, double amplitude, double period, int count);

        /**
         * @brief Destroy the satellite object
         * 
         */
        ~satellite();

        /**
         * @brief Returns availability of satellite based on elevation
         * 
         * Checks to see if satellite elevation is within threshold to 
         * be usable for GPS Lock. Threshold is set to be 10 degrees 
         * above horizon.
         * 
         * @return Availability status of satellite [bool]
         */
        bool usable() const;

        /**
         * @brief Updates satellite elevation and usability state
         * 
         * Computes the current elevation angle using the sinusoidal
         * visibility model.
         * 
         * @param time Current simulation time [s]
         * 
         * @note Elevation model:
         *       elevation = Offset + Amplitude * sin(AngVel * time + PhaseShift)
         */
        void update(double time);

        /**
         * @brief Returns satellite identification number
         * 
         * @return Identification Number [int]
         */
        int getID();

};

class constellation {

    public:

        //====================================================//
        //                    PARAMETERS                      //
        //====================================================//

        /**
        * @brief Vector of satellites in the constellation
        */
        vector<satellite> satellites;

        //====================================================//
        //                    FUNCTIONS                       //
        //====================================================//

        /**
         * @brief Construct a new constellation object
         * 
         * @param count Number of satellites in the constellation
         * @param offset Offset for satellite trajectory
         * @param amplitude Amplitude for satellite trajectory
         * @param period Period for satellite trajectory
         */
        constellation(int count, double offset, double amplitude, double period);

        /**
         * @brief Destroy the constellation object
         * 
         */
        ~constellation();

        /**
         * @brief Calls update function in all satellites to update the elevation
         * 
         * Updates the satellite trajectory by calling the update functions
         * in the satellite class for each satellite.
         * 
         * @param time Current time in simulation
         */
        void update(double time);

        /**
         * @brief Returns confirmation of GPS Lock
         * 
         * Calls operationalCount() to determine how many satellites are available.
         * 
         * @return Confirmation of GPS Lock [bool]
         */
        bool gpsLock() const;

    private: 

        /**
         * @brief Returns the count of useable satellites.
         * 
         * Counts the number of satellites that meet the elevation threshold
         * to be used by GPS. Threshold is 10 degrees or higher above horizon.
         * 
         * @return Satellites available [int] 
         */
        int operationalCount() const;
};

#endif