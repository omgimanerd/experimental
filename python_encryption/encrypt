#!/usr/bin/python

import argparse
import getpass
import hashlib
import os
import random

def wrap(num):
    while num < 0:
        num += 256
    return num % 256

def keygen():
    random.seed()
    keyvalues = 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890'
    key = ''
    for i in range(128):
        key += keyvalues[random.randint(0, len(keyvalues) - 1)]
    return key
    
def encode(method, key, plaintext):
    if method == 1:
        encryptedtext = chr(method) + key + '\n'
    else:
        encryptedtext = chr(method) + '\n'

    for i in range(len(plaintext)):
        shift = ord(key[i % len(key)])
        if i % 2 == 0:
            shift *= -1
        encryptedtext += chr(wrap(ord(plaintext[i]) + shift))
    return encryptedtext

excluded_types = ['jpg', 'png', 'ico', 'jpeg', 'mp3', 'mp4', 'ogg', 'class',
                  'pdf', 'iso', 'msi', 'exe', 'gif']

def list_files(path):
    files = []
    for name in os.listdir(path):
        pathname = os.path.join(path, name)
        if name[0] == '.' or name.split('.')[-1] in excluded_types or os.path.islink(pathname):
            continue
        if os.path.isfile(pathname):
            files.append(os.path.relpath(pathname))
    return files

def list_files_recursively(path):
    files = []
    for name in os.listdir(path):
        pathname = os.path.join(path, name)
        if name[0] == '.' or name.split('.')[-1] in excluded_types or os.path.islink(pathname):
            continue
        if os.path.isfile(pathname):
            files.append(os.path.relpath(pathname))
        else:
            subfiles = list_files_recursively(pathname)
            for subfile in subfiles:
                files.append(os.path.relpath(subfile))
    return files

def list_files_all(path):
    files = []
    for name in os.listdir(path):
        pathname = os.path.join(path, name)
        if os.path.islink(pathname):
            continue
        if os.path.isfile(pathname):
            files.append(os.path.relpath(pathname))
        else:
            subfiles = list_files_all(pathname)
            for subfile in subfiles:
                files.append(os.path.relpath(subfile))
    return files

################################################################################
################################################################################
################################################################################

def main():
    parser = argparse.ArgumentParser(description='This script encrypts specified files with a special vigenere cipher. If arguments are provided, then this script will encrypt all specified files and look inside all specified folders for files to encrypt. If no arguments are provided, every file and folder in the current working directory will be automatically passed in.')
    parser.add_argument('-key', '-keystring', action='store_true',
                        help='enables custom password')
    parser.add_argument('-a', '-all', action='store_true',
                        help='encrypt hidden and non-hidden files recursively')
    parser.add_argument('-r', '-recursive', action='store_true',
                        help='encrypt only non-hidden files recursively')
    parser.add_argument('files', nargs='*', default=argparse.SUPPRESS,
                        help='the file(s) or folder(s) to encrypt')
    args = parser.parse_args()

    filenames = []
    if 'files' in vars(args):
        for files in args.files:
            if files[-1] == '/':
                files = files[:-1] 
            fullpath = os.path.join(os.getcwd(), files)
            if not(files in os.listdir(os.getcwd())):
                print files + ' not found, skipping.'
            elif os.path.isfile(fullpath):
                filenames.append(files)
            else:
                if args.a:
                    filenames += list_files_all(fullpath)
                elif args.r:
                    filenames += list_files_recursively(fullpath)
                else:
                    filenames += list_files(fullpath)
    elif args.a:
        filenames = list_files_all(os.getcwd())
    elif args.r:
        filenames = list_files_recursively(os.getcwd())
    else:
        filenames = list_files(os.getcwd())

    if args.key:
        userinput = getpass.getpass();
        key = hashlib.sha256(userinput).hexdigest()
        method = 2
    else:
        key = keygen()
        method = 1

    files_encrypted = 0

    for filename in filenames:
        inputfile = open(filename, 'r')
        stor = inputfile.read()
        inputfile.close()

        outputfile = open(filename, 'wb+')
        outputfile.write(encode(method, key, stor))
        outputfile.close()

        print 'Encrypted ' + filename
        files_encrypted += 1

    print 'Encryption finished. ' + str(files_encrypted) + ' files encrypted'

if __name__ == '__main__':
    main()
