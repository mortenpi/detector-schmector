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

bincenters = 0.5*(bins[1:]+bins[:-1])
y = 0.7*np.exp(-0.7*bincenters) # computing the values of sin(x)/x
ax.plot(bincenters,y, 'r--', linewidth=3)

#ax.set_xlabel('Smarts')
#ax.set_ylabel('Probability')
#ax.set_title(r'$\mathrm{Histogram\ of\ IQ:}\ \mu=100,\ \sigma=15$')
ax.set_xlim(0, 10)
ax.set_ylim(0, 0.65)
ax.grid(True)

plt.show()
