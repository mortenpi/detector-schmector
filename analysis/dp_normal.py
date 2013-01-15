#!/usr/bin/python
import sys
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.mlab as mlab

fname = sys.argv[1]
print "Opening " + fname
fh = open(fname, 'r')
x = map(float, fh.readlines())
fh.close()

fig = plt.figure()
ax = fig.add_subplot(111)

# the histogram of the data
n, bins, patches = ax.hist(x, 50, normed=1, facecolor='green', alpha=0.75)

# hist uses np.histogram under the hood to create 'n' and 'bins'.
# np.histogram returns the bin edges, so there will be 50 probability
# density values in n, 51 bin edges in bins and 50 patches.  To get
# everything lined up, we'll compute the bin centers
bincenters = 0.5*(bins[1:]+bins[:-1])
# add a 'best fit' line for the normal PDF
y = mlab.normpdf( bincenters, 1.5, 2.0)
l = ax.plot(bincenters, y, 'r--', linewidth=3)

#ax.set_xlabel('Smarts')
#ax.set_ylabel('Probability')
#ax.set_title(r'$\mathrm{Histogram\ of\ IQ:}\ \mu=100,\ \sigma=15$')
ax.set_xlim(-9.5, 12.5)
ax.set_ylim(0, 0.22)
ax.grid(True)

plt.show()
