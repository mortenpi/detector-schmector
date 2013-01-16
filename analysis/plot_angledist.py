#!/usr/bin/python
import sys
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.mlab as mlab
import cbind.deserialize as dsr

fname = sys.argv[1]
print "Opening " + fname
evs = dsr.deserialize(fname)

#for e in evs:
#	print e['particle']['phi'],e['guess']['phi'] if e['guess'] else 'None'

xr = [e['particle']['phi'] for e in evs if e['guess'] and e['particle']['phi']<1.2]
xg = [e['guess']['phi'] for e in evs if e['guess'] and e['particle']['phi']<1.2]

fig = plt.figure()
ax = fig.add_subplot(111)

# the histogram of the data
n, bins, patches = ax.hist(xr, 20, range=(0,1.2), normed=1, facecolor='green', alpha=0.40)
n, bins, patches = ax.hist(xg, 20, range=(0,1.2), normed=1, facecolor='red', alpha=0.40)
ax.set_xlim(0, 1.2)
ax.set_ylim(0, 4)
ax.grid(True)

plt.show()
