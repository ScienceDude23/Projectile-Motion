#!/usr/bin/bash

# Input values for the model
speed=3 # m/s
theta=45 # degrees
x0=0 # m
y0=5 # m
h=0.01 # s
tf=10 # s

rho=1.225 # kg/m3, air is 1.225
A=.5 # surface area, m2
Cd=.5 # dimensionless
m=2 # mass, kg

k=$(awk "BEGIN {print ($rho * $A * $Cd) / (2 * $m)}")

g++ savetraj.cc -o notavirus.sus || { echo "Compilation error"; exit 1; }

printf "%s %s\n(%s,%s)\n%s\n%s\n%s\n" \
    "$speed" "$theta" "$x0" "$y0" "$h" "$tf" "$k" | ./notavirus.sus

sim=1
while [ -d "sim$sim" ]; do
    ((sim++))
done
mkdir "sim$sim"
mv trajectory.csv "sim$sim"
cd "sim$sim"

python ../graph.py