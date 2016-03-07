#!/usr/bin/python

import argparse
import language_check
import random
import re

def main():
  # Reads in arguments from the command line.
  argument_parser = argparse.ArgumentParser(description='Does gov homework.')
  argument_parser.add_argument('filename',
                               help='The file containing the chapter text dump')
  argument_parser.add_argument('section', type=int,
                               help='The section to generate a summary for')
  args = argument_parser.parse_args()

  # Reads in the chapter
  with open(args.filename) as f:
    chapter = f.read().strip()

  # Isolates a single section of to summarize.
  section_begin = re.search('S\s*e\s*c\s*t\s*i\s*o\s*n\s*%s' % args.section,
                            chapter)
  section_end = re.search('Section\s*%s\s*Assessment' % args.section,
                          chapter)
  if not section_begin or not section_end:
    raise ValueError('Oh shit that section doesn\'t exist!')
  section = chapter[section_begin.start(): section_end.start()]

  # Removes all extraneous whitespace and symbols and separates the section
  # into a list of sentences.
  section = re.sub("[^\w\s .'\"!,()]", '', section)
  section = section.replace('. . .', '')
  section = re.sub('\s+', ' ', section)
  section = filter(lambda x: x != '', section.split('. '))

  # Filter out pertinent and useful sentences
  checker = language_check.LanguageTool('en-US')
  section = filter(lambda x: len(checker.check(x)) == 0, section)

  # Rejoin the list of sentences
  section = '. '.join(section)
  print section + '.'

if __name__ == '__main__':
  main()
