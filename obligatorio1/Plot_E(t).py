from matplotlib import offsetbox
import numpy as np
import matplotlib.pyplot as plt

# Leemos datos de un fichero
data = np.loadtxt('ctes_mov.dat')
x = data[:,0]
y = data[:,1]
z = data[:,2]

fig, (ax1, ax2) = plt.subplots(2, 1)
fig.suptitle("Conservación Energía y Momento Angular (sin reescalar)", fontsize=14, fontname="Times New Roman")

ax1.plot(x,y)
ax1.set_ylabel("E", fontsize=14, fontname="Times New Roman", labelpad=-1)
ax1.set_xlim(0,1600)
ax1.set_ylim(0,0.001)

ax2.plot(x,z)
ax2.set_ylabel("L", fontsize=14, fontname="Times New Roman", labelpad=5)
ax2.set_xlabel("t", fontsize=14, fontname="Times New Roman")
ax2.set_xlim(0,1600)
ax2.set_ylim(0,0.005)


plt.savefig("E(t).png")
plt.show()


