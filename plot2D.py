import matplotlib.pyplot as plt
import numpy as np
import sys

try:
    filename = sys.argv[1];
except IndexError:
    raise IndexError("specify filename!")

exec "{0} = np.fromfile(\"tmpData/{0}\",sep=\" \"); {0} = {0}.reshape((len({0})/1.,1))".format(filename)

exec "filename = {0}".format(filename)

n = int(filename[0])
filename = filename[1:]
filename = filename.reshape(len(filename) )

results = np.zeros((n,n) )
for i in range(n-1):
    """loop through and normalize each column"""
    if max(filename[n*i:n*(i+1)]) == 0: continue #ignore columns of zero to avoid division by zero
    results[:,i] = filename[n*i:n*(i+1)] / np.max(np.abs(filename[n*i:n*(i+1)]) )

x = np.linspace(0,1,n) #arbitary x-values
xi,yi = np.meshgrid(x,x); #create square grid

#initialize plots, set background color
fig = plt.figure(); ax = fig.add_subplot(111)
ax.set_axis_bgcolor("white")
cb = colorbar() #show colorbar
lines, = pcolor(xi,yi,results) #gradient plot

#receive data, set plot data(axes, label, limits) and lines
fsize = 14

show()

# from mpl_toolkits.mplot3d import Axes3D
# from matplotlib import cm
# from matplotlib.ticker import LinearLocator, FormatStrFormatter
# 
# fig = plt.figure()
# ax = fig.gca(projection='3d')
# 
# surf = ax.plot_surface(xi,yi,results, rstride=1, cstride=1, facecolors=cm.jet(results), linewidth=0, antialiased=False)
# show() #show figure
