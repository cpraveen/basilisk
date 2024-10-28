import numpy as np
import matplotlib.pyplot as plt

WIDTH = 10.0

def distance(x,y):
    if(y <= 1 and x <= WIDTH/2):
         d = min(1 - y, WIDTH/2 - x);
    elif(y > 1 and x <= WIDTH/2):
         d = 1 - y;
    elif(x > WIDTH/2 and y < 1):
         d = WIDTH/2 - x;
    else:
         d = -np.sqrt((x - WIDTH/2)**2 + (y - 1)**2);
    return d

N = 256
M = N//4
x = np.linspace(0,WIDTH,N)
y = x[0:M]
X,Y = np.meshgrid(x,y,indexing="ij")
Z = np.empty_like(X)

for i in range(N):
    for j in range(M):
        Z[i,j] = distance(X[i,j], Y[i,j])

print("Min = %f, Max = %f" % (Z.min(), Z.max()))

plt.figure(figsize=(10,2.5))
plt.contour(X,Y,Z,levels=10,linestyles="solid",negative_linestyles="dashed")
plt.contour(X,Y,Z,levels=[0],colors="red")
plt.axis("equal")
plt.show()
