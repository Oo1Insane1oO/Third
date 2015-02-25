from pylab import *
import sys

try:
    filename = sys.argv[1];
except IndexError:
    raise IndexError("specify filename!")

exec "{0} = fromfile(\"{0}\",sep=\" \"); {0} = {0}.reshape((len({0})/1.,1))".format(filename)

exec "filename = {0}".format(filename)

n = int(filename[0])
filename = filename[1:]
filename = filename.reshape(len(filename))

results = zeros((n,n))
for i in range(n-1):
    """loop through and normalize each column"""
    #if max(filename[n*i:n*(i+1)]) == 0: continue #ignore columns of zero to avoid division by zero
    results[:,i] = filename[n*i:n*(i+1)]/max(abs(filename[n*i:n*(i+1)]))

x = linspace(0,1,n) #arbitary x-values
xi,yi = meshgrid(x,x); #create square grid

#pcolor(xi,yi,results) #gradient plot
#cb = colorbar() #show colorbar

from mpl_toolkits.mplot3d import Axes3D
from matplotlib import cm
from matplotlib.ticker import LinearLocator, FormatStrFormatter

fig = plt.figure()
ax = fig.gca(projection='3d')

surf = ax.plot_surface(xi,yi,results, rstride=1, cstride=1, facecolors=cm.jet(results), linewidth=0, antialiased=False)
show() #show figure
