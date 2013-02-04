import sys
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.mlab as mlab

def pdf_exp(p):
	return (lambda x: p*np.exp(-p*x))
def pdf_norm(mu, sigma):
	return (lambda x: mlab.normpdf(x, mu, sigma))

def plot(fname, pdf, xlim=(-5,5), bins=20):
	print "Plotting: " + fname
	fh = open(fname, 'r')
	x = map(float, fh.readlines())
	fh.close()

	fig = plt.figure()
	ax = fig.add_subplot(111)

	# the histogram of the data
	n, binlist, patches = ax.hist(x, bins, range=xlim, normed=0, facecolor='green', alpha=0.75)
	
	# Plot the analytical PDF
	binwidth = float(xlim[1]-xlim[0])/float(bins)
	histarea = float(len(x))*binwidth
	bincenters = np.arange(xlim[0], xlim[1], binwidth/10)
	y = map(lambda x: histarea*pdf(x), bincenters)
	l = ax.plot(bincenters, y, 'r--', linewidth=2)
	
	# Axis settings
	#ax.set_xlabel('Smarts')
	#ax.set_ylabel('Probability')
	#ax.set_title(r'$\mathrm{Histogram\ of\ IQ:}\ \mu=100,\ \sigma=15$')
	ax.set_xlim( xlim )
	#ax.set_ylim(0, 0.22)
	ax.grid(True)
	#ax.set_yscale('log')

	#plt.show()
