#!/usr/bin/python
#import pylab
from matplotlib.backends.backend_pdf import PdfPages

import distplot

pdf = PdfPages('distribution_plots.pdf')

distplot.plot(
	'exp.fout',
	distplot.pdf_exp(0.7),
	xlim=(0.0, 8.0)
)
pdf.savefig()

distplot.plot(
	'normal.fout',
	distplot.pdf_norm(1.5,2.0),
	xlim=(-5.0, 8.0)
)
pdf.savefig()

distplot.plot(
	'normalGAR.fout',
	distplot.pdf_norm(-3.2,1.5),
	xlim=(-8.2, 2.8)
)
pdf.savefig()

pdf.close()
