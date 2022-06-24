from matplotlib import offsetbox
import numpy as np
import matplotlib.pyplot as plt

# Leemos datos de un fichero
data = np.loadtxt('memoria.dat', delimiter=",   ")
x = data[:,0]
y = data[:,1]

fig, ax = plt.subplots()
#fig.suptitle("Probabilidad", fontsize=14, fontname="Times New Roman")

ax.plot(x,y, '.') #Si se cambia '.' por '.-', une los puntos
ax.set_xlabel('P')
ax.set_ylabel('$P_c$') #μ
ax.set_xlim(0,101)
ax.set_ylim(-0.25,2.25)


plt.savefig("memoria.png")
plt.show()


