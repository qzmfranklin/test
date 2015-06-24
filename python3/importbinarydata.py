#! /usr/bin/env python

import numpy as np
import struct

file_in = 'strange_binary_format.dat'
fd = open(file_in,'rb')
position = 0
no_of_doubles = 1000
# move to position in file
fd.seek(position,0)

# straight to numpy data (no buffering) 
numpy_data = np.fromfile(fd, dtype = np.dtype('d'), count = no_of_doubles)
