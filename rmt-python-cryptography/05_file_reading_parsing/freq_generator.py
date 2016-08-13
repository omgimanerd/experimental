#!/usr/bin/python

import hashlib
import random
import sys

out = ""
for i in range(100):
  out += hashlib.sha256(str(random.randint(0, 100))).hexdigest() + '\n'

outfile = open(sys.argv[1], "wb+")
outfile.write(out)
