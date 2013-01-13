#!/usr/bin/python
import sys
import matplotlib.pyplot as mp

fname = sys.argv[1]
print "Opening " + fname
fh = open(fname, 'r')
lines = fh.readlines()[1:]
fh.close()

data = [map(float, ln.split(',')) for ln in lines]
x = [d[0] for d in data]
y = [d[1] for d in data]

mp.scatter(x,y)
mp.ylim([-0.5,0.5])
mp.xlim([0,1.5])
mp.show()
