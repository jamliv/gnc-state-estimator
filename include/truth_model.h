#ifndef TRUTH_MODEL_H
#define TRUTH_MODEL_H

// State structure that contains the position and velocity information for the current state
struct state {
    double x;
    double y;
};

struct truthState {
    double x;
    double y;
    double vx;
    double vy;
};

// Truth Model of the Vehicle
class simulation {
    public:

        // Constructor (No Params)
        simulation();

        // Constructor (Only dt set)
        simulation(double dt);

        // Contructor (All Params)
        simulation (double x, double y, double vx, double vy, double ax, double ay, double dt);

        // Destructor
        ~simulation();

        state getState() const;

        truthState getTruthState() const;

        // Propagate the simulation by dt
        void propagate();

        // Get current simulation time
        double getTime() const;

        // Reset the simulation
        void reset();

    private:

        // Pos, Vel, Acc, and Time variables
        double x = 0;
        double y = 0;
        double vx = 1;
        double vy = 0.5;
        double ax = 0;
        double ay = 0;
        double time = 0; 
        double dt = 0.1;


};

#endif