import matplotlib.pyplot as plt
import numpy as np
import sys, os

fpath = "tmpData/" # tempfiles directory

# find n from first file
initialData = np.fromfile(fpath + "data0", sep = " ")
initialData = initialData.reshape(len(initialData) / 1., 1)
n = initialData[0]
initialData = initialData[1:]
initialData = initialData.reshape(len(initialData) )

for i in range(n-1):
    """loop through and normalize each column"""
    if np.max(initialData[n*i:n*(i+1)]) == 0: continue #ignore columns of zero to avoid division by zero
    InitialData[:,i] = initialData[n*i:n*(i+1)] / np.max(np.abs(initialData[n*i:n*(i+1)]) )

foo

x = np.linspace(0,1,n) #arbitary x-values
xi,yi = np.meshgrid(x,x); #create square grid

#initialize plots, set background color
fig, ax = plt.subplots(2,1)
ax = ax.ravel()

im = ax[0].imshow(initialData,  interpolation="nearest", origin="bottom",
                                vmin=np.min(initialData), vmax=np.max(initialData),
                                cmap="jet")

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

    c += 1
