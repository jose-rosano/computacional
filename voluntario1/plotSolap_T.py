from matplotlib import offsetbox
import numpy as np
import matplotlib.pyplot as plt

# Leemos datos de un fichero
data = np.loadtxt('solap(T).dat', delimiter=",   ")
x = data[:,0]
y = data[:,1]

fig, ax = plt.subplots()
#fig.suptitle("Probabilidad", fontsize=14, fontname="Times New Roman")

ax.plot(x,y, '.-')
plt.xscale("log")
ax.set_xlabel('T')
ax.set_ylabel('$m^1$') #μ
ax.set_xlim(0.00008,1)
ax.set_ylim(-1.25,1.25)


plt.savefig("solap(T).png")
plt.show()


