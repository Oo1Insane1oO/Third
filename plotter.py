from pylab import *
import sys

try:
    filename = sys.argv[1];
except IndexError:
    raise IndexError("specify filename!")

exec "{0} = fromfile(\"{0}\",sep=\" \"); {0} = {0}.reshape((len({0})/2.,2))".format(filename)

x = test[:,0]
test = test[:,1]/max(test[:,1])

plot(x,test)
show()


