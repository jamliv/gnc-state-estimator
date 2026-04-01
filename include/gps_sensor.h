#include "truth_model.h"

// GPS Sensor Class 
class gps {

    public:

        // Default Constructor
        gps();

        // Constructor (Custom Update Rate)
        gps(float dt);

        // Constructor (Custom Acquisition Rate)
        gps(float acqRate);

        // Default Destructor
        ~gps();

        // Get stored data
        state data();

    private:

        // GPS Parameters
        float dt = 0.5;
        float acqRate = 0.1;
        double x = 0;
        double y = 0;

        // Acquisition Check
        bool acquisition();
        
        // Internal Calculation to add noise (GPS Error)
        void gpsCalculation();
};