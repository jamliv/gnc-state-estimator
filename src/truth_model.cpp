#include "truth_model.h"
#include <cmath>

simulation::simulation() {}

simulation::simulation(double dt) {
    this->dt = dt;
}

simulation::simulation(double x, double y, double vx, double vy, double ax, double ay, double dt) {
    this->x = x;
    this->y = y;
    this->vx = vx;
    this->vy = vy;
    this->ax = ax;
    this->ay = ay;
    this->dt = dt;
}

simulation::~simulation() {}

state simulation::getState() const {
    return {x, y};
}

truthState simulation::getTruthState() const {
    return {x, y, vx, vy};
}

void simulation::propagate() {

    // Add a timestep
    time += dt;

    // Calculate current acceleration
    ax = 0.5 * sin(time);
    ay = 0.5 * cos(time);

    // Calculate and add change in position
    x += vx * dt + 0.5 * ax * dt * dt;
    y += vy * dt + 0.5 * ay * dt * dt;

    // Calculate current velocity
    vx += ax * dt;
    vy += ay * dt;
}

double simulation::getTime() const {
    return time;
}

void simulation::reset() {
    x = 0;
    y = 0;
    vx = 0;
    vy = 0;
    ax = 0;
    ay = 0;
    time = 0; 
    dt = 0.1;
}