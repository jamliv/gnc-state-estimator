#ifndef TRUTH_MODEL_H
#define TRUTH_MODEL_H

// State structure that contains the position and velocity information for the current state
struct state {
    double x;
    double y;
};

// Truth Model of the Vehicle
class simulation {
    public:

        // Constructor (No Params)
        simulation();

        // Constructor (Only dt set)
        simulation(float dt);

        // Contructor (All Params)
        simulation (double x, double y, double vx, double vy, double ax, double ay, double dt);

        // Destructor
        ~simulation();

        state getState() const;

        // Propagate the simulation by dt
        state propagate();

        // Get current simulation time
        double getTime() const;

        // Reset the simulation
        void reset();

    private:

        // Pos, Vel, Acc, and Time variables
        double x = 0;
        double y = 0;
        double vx = 0;
        double vy = 0;
        double ax = 0;
        double ay = 0;
        double time = 0; 
        float dt = 0.1;


};

#endif