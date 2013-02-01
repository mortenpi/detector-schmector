Particle detector simulation
============================
A particle detector simulation software that uses Monte Carlo methods.
Or atleast one day will.

The code is roughly in two parts:

 *  The actual Monte Carlo and simulation part is written in C++.
    Couple C++ programs create datasets that can be analyzed.
 *  There are Python scripts that use Matplotlib and NumPy/SciPy
    to analyze the produced datasets, create plots etc.

Compiling
=========
Project uses the [Perforce Jam](http://www.perforce.com/documentation/jam)
build tool. Just run `jam` (or `ftjam`, since it's backwards compatible)
in the top-level directory to build everything.

Dependencies
------------
C++ part of the project uses:

 *  [GNU GSL library](http://www.gnu.org/software/gsl/).
    
    It should be linked with `-lgsl -lgslcblas` flags.
    A related example: `test/gls.cpp`.

 *  [Boost C++ Libraries](http://www.boost.org/)
    
    Currently only the serialization library is used from Boost.
    Code should be compiled with `-lboost_serialization`.
    A related example: `test/boostserialization.cpp`

Python part of the project uses the following Python libraries:

 *  [NumPy](http://www.numpy.org/)
 *  [SciPy](http://www.scipy.org/)
 *  [Matplotlib](http://matplotlib.org/)

License
=======
Copyright (C) 2013 Morten Piibeleht

Written for the Computational Physics I course  
University of Tartu

MIT License
-----------

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom
the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
