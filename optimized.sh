#!/usr/bin/bash

# Input values
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

g++ optimized.cc -o notmalware.vir || { echo "Compilation error"; exit 1; }

printf "%s %s %s %s %s %s %s" \
    "$k" "$h" "$tf" "$speed" "$theta" "$x0" "$y0" | ./notmalware.vir

sim=1
cd sims
while [ -d "sim$sim" ]; do
    ((sim++))
done
mkdir "sim$sim"
mv ../trajectory.csv "sim$sim"
cd "sim$sim"

python ../../graph.py