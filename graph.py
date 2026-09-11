from matplotlib import pyplot as plt
import numpy as np

X = np.loadtxt('trajectory.csv', delimiter=',', skiprows=1)
u = X[:,0]
v = X[:,1]
x = X[:,2]
y = X[:,3]
t = X[:,4]

plt.figure() # C(x,y)
plt.plot(x,y)
plt.xlabel("x (m)")
plt.ylabel("y (m)")
plt.title("Trajectory curve C(x,y)")
plt.savefig("trajectory.png", dpi=300)
plt.close()

plt.figure() # V(u,v)
plt.plot(u,v)
plt.xlabel("u (m/s)")
plt.ylabel("v (m/s)")
plt.title("Velocity curve V(u,v)")
plt.savefig("velocity.png", dpi=300)
plt.close()

plt.figure() # x(t)
plt.plot(t,x)
plt.xlabel("t (s)")
plt.ylabel("x (m)")
plt.title("Position function x(t)")
plt.savefig("xpos.png", dpi=300)
plt.close()

plt.figure() # y(t)
plt.plot(t,y)
plt.xlabel("t (s)")
plt.ylabel("y (m)")
plt.title("Position function y(t)")
plt.savefig("ypos.png",dpi=300)
plt.close()

plt.figure() # u(t)
plt.plot(t,u)
plt.xlabel("t (s)")
plt.ylabel("u (m/s)")
plt.title("Velocity function u(t)")
plt.savefig("uvel.png",dpi=300)
plt.close()

plt.figure() # v(t)
plt.plot(t,v)
plt.xlabel("t (s)")
plt.ylabel("v (m/s)")
plt.title("Velocity function v(t)")
plt.savefig("vvel.png",dpi=300)
plt.close()

plt.figure()
plt.plot(t, x, label="x(t)")
plt.plot(t, y, label="y(t)")
plt.xlabel("t (s)")
plt.ylabel("Position (m)")
plt.title("Position vs Time")
plt.legend()
plt.savefig("xypos.png",dpi=300)
plt.close()

plt.figure()
plt.plot(t, u, label="u(t)")
plt.plot(t, v, label="v(t)")
plt.xlabel("t (s)")
plt.ylabel("Velocity (m/s)")
plt.title("Velocity vs Time")
plt.legend()
plt.savefig("uvvel.png",dpi=300)
plt.close()