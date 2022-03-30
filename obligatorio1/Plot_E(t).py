import matplotlib.pyplot as plt
import numpy as np

# El fichero debe estructurarse de la siguiente forma:
# 
#   x1, y1
#   x2, y2
#   x3, y3

x, y = np.loadtxt('ctes_mov.dat', delimiter=',', unpack=True)
plt.plot(x,y, label='Insert Label')

plt.xlabel('t')
plt.ylabel('E')
plt.title('Insert Title')
plt.legend()
plt.show()