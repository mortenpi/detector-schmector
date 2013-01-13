#!/usr/bin/python
import sys
import matplotlib.pyplot as mp

fname = sys.argv[1]
print "Opening " + fname
fh = open(fname, 'r')
lines = fh.readlines()
fh.close()

data = [map(float, ln.split(',')) for ln in lines[2:]]
x = [d[0] for d in data]
y = [d[1] for d in data]

c = map(float, lines[1].split(','))
print c

mp.scatter(x,y)
mp.ylim([-0.5,0.5])
mp.xlim([0,1.5])

cr1 = mp.Circle((0.624986, -0.625014), 0.883883, color='r', fill=False)
#cr2 = mp.Circle((-0.623383, 0.630122), 0.890109, color='b', fill=False)
cr2 = mp.Circle((c[0], c[1]), c[2], color='b', fill=False)
mp.gca().add_artist(cr1)
mp.gca().add_artist(cr2)

mp.show()
