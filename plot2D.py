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
    results[:,i] = filename[n*i:n*(i+1)]/max(filename[n*i:n*(i+1)])

x = linspace(0,1,n)
xi,yi = meshgrid(x,x);

pcolor(xi,yi,results)
cb = colorbar()
show()
