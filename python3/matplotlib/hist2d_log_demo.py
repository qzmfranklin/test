#!/usr/local/bin/python3

'''
INPUT DATA FORMAT:
    x0 y0
    x1 y1
    x2 y2
    ...
    (The delimiter can be changed through the -d, --delimiter option)

OUTPUT:
    A 2D histogram of the input data points.

REQUIREMENT:
    numpy
    matplotlib
'''

import argparse
from matplotlib.colors import LogNorm
import numpy as np
import pylab
import sys

if __name__ == '__main__':
    parser = argparse.ArgumentParser(formatter_class=argparse.ArgumentDefaultsHelpFormatter)
    parser.add_argument('-i', '--input',
            type = argparse.FileType('r', encoding = 'utf8'),
            default = sys.stdin,
            help = 'input file')
    parser.add_argument('--num-bins',
            type = int, default = 50,
            help = 'number of bins in x and y direction')
    parser.add_argument('-d',
            type = str, default = ' ',
            help = 'delimiter')

    args = parser.parse_args()

    x, y = np.loadtxt(args.input, delimiter = args.delimiter, unpack = True)

    pylab.hist2d(x,y,bins=args.num_bins,norm=LogNorm())
    pylab.colorbar()
    pylab.show()
