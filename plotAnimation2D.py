import matplotlib.pyplot as plt
import numpy as np
import sys, os

jump = int(sys.argv[1])
fpath = "tmpData/" # tempfiles directory

# find n from first file
initialData = np.fromfile(fpath + "data0", sep = " ")
initialData = initialData.reshape(len(initialData) / 1., 1)
n = int(initialData[0])
initialData = initialData[1:]
initialData = initialData.reshape(len(initialData) )

tempInitialData = np.zeros((n,n) )
for i in xrange(n-1):
    tempInitialData[:,i] = initialData[n*i:n*(i+1)]
initialData = tempInitialData

x = np.linspace(0,1,n) #arbitary x-values
xi,yi = np.meshgrid(x,x); #create square grid

#initialize plots, set background color
fig = plt.figure(); ax = fig.add_subplot(111)
ax.set_axis_bgcolor("white")
pc = plt.pcolor(xi,yi, initialData)
#initialize backgrounds, draw canvas
bg = fig.canvas.copy_from_bbox(ax.bbox)
fig.canvas.draw()

# loop til files end
c = 1
while True:
    filename = "data" + str(c)
    if os.path.exists(fpath+filename) == False:
        """ check if file exists """
        print "ending"
        break

    # read file, remove first and reshape
    tempData = np.fromfile(fpath + filename, sep = " ")
    tempData = tempData.reshape(len(tempData) / 1., 1)
    tempData = tempData[1:]
    tempData = tempData.reshape(len(tempData) )

    fig.canvas.restore_region(bg)
    myCmap = plt.get_cmap('jet')
    newColor = myCmap(tempData.T.ravel() )
    pc.update({'facecolors':newColor})
#     plt.draw()
    fig.canvas.draw()

    #update and clear(flush) figure canvas
    fig.canvas.update(); fig.canvas.flush_events()

    plt.show(block=False)

    c += jump
    print c

plt.show()
