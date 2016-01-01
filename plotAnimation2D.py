import matplotlib.pyplot as plt
import numpy as np
import sys, os

def setData(dataArray):
    """ function for setting data """

    n = int(dataArray[0])
    dataArray = dataArray[1:]
    dataArray.reshape(len(dataArray) )

    finalArray = np.zeros((n,n) )
    for i in xrange(n-1):
        finalArray[:,i] = dataArray[n*i:n*(i+1)]
    # end for i

    return n, finalArray
# and function setData

jump = int(sys.argv[1])
fpath = "tmpData/" # tempfiles directory

# find n and initial data from first file
initialData = np.fromfile(fpath + "data0", sep = " ")
n, initialData = setData(initialData)

x = np.linspace(0,1,n) #arbitary x-values
xi,yi = np.meshgrid(x,x); #create square grid

#initialize plots, set background color
fig = plt.figure(); ax = fig.add_subplot(111)
ax.set_axis_bgcolor("blue")
im = plt.imshow(initialData, interpolation="nearest", origin="bottom", aspect="auto", cmap="jet")
cb = plt.colorbar(im)
#initialize backgrounds, draw canvas
bg = fig.canvas.copy_from_bbox(ax.bbox)
fig.canvas.draw()

# loop until files end
c = jump
while True:
    # set file and check for ending (last file)
    filename = "data" + str(c)
    if os.path.exists(fpath + filename) == False:
        """ check if file exists """
        print "ending"
        break
    # end if os False

    # read file, remove first and reshape
    tempData = np.fromfile(fpath + filename, sep = " ")
    n, tempData = setData(tempData)

    # restore background, update figure and draw results
    fig.canvas.restore_region(bg)
    im.set_data(tempData)
    ax.draw_artist(im)
   
    # show without block
    plt.show(block=False)

    # update and clear(flush) figure canvas
    fig.canvas.update(); fig.canvas.flush_events()

    c += jump
# end while True

# keep last figure shown
plt.show()
