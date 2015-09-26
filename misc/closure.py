#!/usr/bin/python
# This refactors the Google Closure Compilation process of JavaScript
# into a single script.
# Author: Alvin Lin (alvin.lin@stuypulse.com)

import argparse
import requests
import os

"""
This function takes a path in the current directory and returns all the files
in the directory by searching it recursively.
"""
def list_files(path):
  files = []
  if os.path.isfile(path):
    files.append(path)
  elif os.path.isdir(path):
    for name in os.listdir(path):
      fullpath = os.path.join(path, name)
      if os.path.isfile(fullpath):
        files.append(fullpath)
      else:
        subfiles = list_files(os.path.join(path, name))
        for subfile in subfiles:
          files.append(os.path.join(name, subfile))
  return files

def main():
  # Sets up ArgumentParser.
  parser = argparse.ArgumentParser(description="""This script compiles all
  inputted JavaScript files using the Google Closure compiler.""")
  parser.add_argument('-r', '-recursive', action='store_true',
                      help='search recursively for files to compile')
  parser.add_argument('files', nargs='*',
                      help='files to compile')

  # Gets all the queried files and filters out the JavaScript files.
  files = []
  for f in parser.parse_args().files:
    files += list_files(f)
  files = filter(lambda x: x[-3:] == '.js', files)

  # Concatenates all the JavaScript files together.
  js = ''
  for f in files:
    with open(f) as current_file:
      js += current_file.read()

  # Sends the JavaScript to the Google Closure Compiler.
  headers = { "Content-type": "application/x-www-form-urlencoded" }
  data = {
    'js_code': js,
    'language': 'ECMASCRIPTS',
    'compilation_level': 'SIMPLE_OPTIMIZATIONS',
    'output_format': 'text',
    'output_info': 'compiled_code'
  }
  r = requests.post('http://closure-compiler.appspot.com/compile',
                    headers=headers,
                    data=data)
  print r.text

if __name__ == '__main__':
  main()
