#!/usr/bin/python

import codecs
import sys

with codecs.open(sys.argv[1], encoding='utf-8') as infile:
  text = infile.read()

with codecs.open(sys.argv[1], encoding='utf-8', mode='w') as outfile:
  outfile.write(text.replace(';', u'\u037E'))

print 'Mischief managed!'
