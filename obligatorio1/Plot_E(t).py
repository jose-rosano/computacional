import matplotlib.pyplot as plt
import numpy as np

x, y = np.loadtxt('example.txt', delimiter=',', unpack=True)
plt.plot(x,y, label='Insert Label')

plt.xlabel('t')
plt.ylabel('E')
plt.title('Insert Title')
plt.legend()
plt.show()