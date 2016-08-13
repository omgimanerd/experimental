#!/usr/bin/python

import hashlib
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
        encryptedtext = chr(method) + keygen() + '\n'
    else:
        encryptedtext = chr(method) + '\n'

    for i in range(len(plaintext)):
        shift = ord(key[i % len(key)])
        if i % 2 == 0:
            shift *= -1
        encryptedtext += chr(wrap(ord(plaintext[i]) + shift))
    return encryptedtext
