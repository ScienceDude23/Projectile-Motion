#include <iostream>
#include <cmath>
#include <vector>
#include <array>
#include <fstream>

using State = std::array<double, 5>; // u=dx/dt,v=dy/dt,x=xposition,y=yposition,t=time
using Pos = std::array<double, 2>; // x,y position

/* 4th order Runge-Kutta method for projectile motion with drag
    dy/dt = f(t,y)
        k1 = f(t_n, y_n)
        k2 = f(t_n + h/2, y_n + h*k1/2)
        k3 = f(t_n + h/2, y_n + h*k2/2)
        k4 = f(t_n + h, y_n + h*k3)
    y_{n+1} = y_n + h/6 * (k1 + 2*k2 + 2*k3 + k4) 
Adapted for vector-valued function (k_n become vectors) */
std::vector<State> RK4(
    const Pos& X, // initial position vector (x,y)
    const double k, // k is combined drag coefficient a=-kv^2
    const double h, // h is step size
    const double tf, // tf is stop time
    const double speed, // initial speed
    const double theta // launch angle in degrees
    ){
    
    const double g = 9.81; // accel due to grav, m/s^2
    const double rad = theta * M_PI / 180.0; // convert angle to radians
    const double h2 = h / 2.0;
    const double h6 = h / 6.0;

    State k1, k2, k3, k4; // Runge-Kutta coefficients

    std::vector<State> trajectory; // array whose rows are the state vectors (u,v,x,y,t)
    State X0 = {speed * std::cos(rad), speed * std::sin(rad), X[0], X[1], 0.0}; // initial state: u,v,x,y,t
    trajectory.push_back(X0); // add initial state to trajectory
    
    while (X0[4] < tf) {
        // compute k1
        double u = X0[0]; // initial horizontal velocity
        double v = X0[1]; // initial vertical velocity
        double sp = std::sqrt(u*u + v*v); // magnitude of velocity
        k1 = {-k*u*sp, -g - k*v*sp, u, v, 1};

        // compute k2
        u = X0[0] + h2*k1[0];
        v = X0[1] + h2*k1[1];
        sp = std::sqrt(u*u + v*v);
        k2 = {-k*u*sp, -g - k*v*sp, u, v, 1};

        // compute k3
        u = X0[0] + h2*k2[0];
        v = X0[1] + h2*k2[1];
        sp = std::sqrt(u*u + v*v);
        k3 = {-k*u*sp, -g - k*v*sp, u, v, 1};

        // compute k4
        u = X0[0] + h*k3[0];
        v = X0[1] + h*k3[1];
        sp = std::sqrt(u*u + v*v);
        k4 = {-k*u*sp, -g - k*v*sp, u, v, 1};

        // update state
        for (int i = 0; i < 5; i++) {
            X0[i] += h6 * (k1[i] + 2*k2[i] + 2*k3[i] + k4[i]);
        }

        // add new state to trajectory
        trajectory.push_back(X0);
    }
    return trajectory;
}

int main() {
    // define parameter variables
    Pos X;
    double k, h, tf, speed, theta;

    std::cin >> k >> h >> tf >> speed >> theta >> X[0] >> X[1]; // input parameters
    std::vector<State> trajectory = RK4(X, k, h, tf, speed, theta); // call RK4 function

    // output trajectory to file
    std::ofstream file("trajectory.csv");
    file << "u,v,x,y,t\n"; // header
    for (const auto& row : trajectory) {
        file << row[0] << "," 
             << row[1] << "," 
             << row[2] << "," 
             << row[3] << "," 
             << row[4] << "\n";
    }

    return 0;
}
