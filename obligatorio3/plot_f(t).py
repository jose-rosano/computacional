from matplotlib import offsetbox
import numpy as np
import matplotlib.pyplot as plt

# Leemos datos de un fichero
data = np.loadtxt('probabilidad.dat', delimiter=",   ")
x = data[:,0]
y = data[:,1]

fig, ax = plt.subplots()
fig.suptitle("Probabilidad", fontsize=14, fontname="Times New Roman")

ax.plot(x,y)
ax.set_ylabel("|Φ|^2", fontsize=14, fontname="Times New Roman", labelpad=-1)
ax.set_xlabel("t", fontsize=14, fontname="Times New Roman")
ax.set_ylim(0,1.2)

plt.savefig("Probabilidad.png")
plt.show()


