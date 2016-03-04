#!/usr/bin/python

import language_check
import random
import re

FILENAME = "ch02.unlocked.txt"
dirname = "raw/"

if __name__ == '__main__':
  checker = language_check.LanguageTool('en-US')

  with open(dirname + FILENAME) as f:
    chapter = f.read().strip()

  match_3 = re.search("S e c t i on\s+[4]", chapter)
  match_3_end = re.search("Section\s+4\sAssessment", chapter)

  section = chapter[match_3.start():match_3_end.start()]
  section = re.sub("[^\w\s .'\"!,()-]", '', section)
  section = section.split("\n")
  section = map(lambda x: x.strip(), section)
  section = filter(lambda x: x != '', section)
  section = ' '.join(section).split('. ')
  section = filter(lambda x: x != '', section)

  # section = filter(lambda x: len(checker.check(x)) == 0, section)

  print ". ".join(section)
