Numerically solves for projectile motion in 2D with air resistance.
Requires numpy and matplotlib for graphing

The main files have the basic functionality of solving and printing at each timestep.
The main.cc file contains the solver, main.sh compiles it, runs it, and passes the inputs

The savetraj.cc file saves the values at each timestep and outputs the list of state vectors as a csv file.
The graph.py file takes the csv and produces various graphs of x,y,u,v,t.
The trajgraph.sh file compiles savetraj.cc, runs it, passes the inputs, then runs graph.py