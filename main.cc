#include <iostream>
#include <cmath>
#include <array>
#include <vector>
#include <fstream>

double k,h,tf,speed,theta; // k is combined drag coefficient F=-kv^2, h is step size, tf is stop time
double g = 9.81; // accel due to grav, m/s^2
int ts = 0; // timestep number

double u,v,x,y,t;
std::array<double,5> U;
std::array<double,5> X0;

void RK4() {
    while (X0[4] < tf) {
        u = X0[0]; v = X0[1]; x = X0[2]; y = X0[3];
        U = {-k*u*std::sqrt(std::pow(u,2)+std::pow(v,2)),-g-k*v*std::sqrt(std::pow(u,2)+std::pow(v,2)),u,v,1};
        std::array<double,5> k1 = U;

        std::array<double,5> a;
        for (int i = 0; i < 5; i++) {
            a[i] = k1[i] * h /2;
        }
        u = X0[0] + a[0]; v = X0[1] + a[1]; x = X0[2] + a[2]; y = X0[3] + a[3];
        U = {-k*u*std::sqrt(std::pow(u,2)+std::pow(v,2)),-g-k*v*std::sqrt(std::pow(u,2)+std::pow(v,2)),u,v,1};
        std::array<double,5> k2 = U;

        std::array<double,5> b;
        for (int i = 0; i < 5; i++) {
            b[i] = k2[i] * h /2;
        }
        u = X0[0] + b[0]; v = X0[1] + b[1]; x = X0[2] + b[2]; y = X0[3] + b[3];
        U = {-k*u*std::sqrt(std::pow(u,2)+std::pow(v,2)),-g-k*v*std::sqrt(std::pow(u,2)+std::pow(v,2)),u,v,1};
        std::array<double,5> k3 = U;
        
        std::array<double,5> c;
        for (int i = 0; i < 5; i++) {
            c[i] = k3[i] * h;
        }
        u = X0[0] + c[0]; v = X0[1] + c[1]; x = X0[2] + c[2]; y = X0[3] + c[3];
        U = {-k*u*std::sqrt(std::pow(u,2)+std::pow(v,2)),-g-k*v*std::sqrt(std::pow(u,2)+std::pow(v,2)),u,v,1};
        std::array<double,5> k4 = U;

        double d = h / 6;
        for (int i = 0; i < 5; i++) {
            X0[i] += d * (k1[i] + 2*k2[i] + 2*k3[i] + k4[i]);
        }

        ts += 1;
        std::cout << "Timestep " << ts << ": (";
        for (int i = 0; i < 5; i++){
            std::cout << X0[i];
            if (i < 4){
                std::cout << ",";
            }
        }
        std::cout << ")\n";
    }
}

int main() {
        // This block inputs initial state
    char c;
    std::cin >> speed >> theta;
    X0[0] = speed * std::cos(theta);
    X0[1] = speed * std::sin(theta);

    std::cin >> c;
    for (int i = 2; i < 4; i++) {
        std::cin >> X0[i];
        std::cin >> c;
    }

    X0[4] = 0;
    
    // This block inputs the other parameters
    std::cin >> h;
    std::cin >> tf;
    std::cin >> k;

    // Run the algorithm and save 
    RK4();

    return 0;
}
