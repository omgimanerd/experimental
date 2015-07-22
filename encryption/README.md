Encryption
========
The python scripts in this directory can encrypt all files in the current
working directory as well as any other files in any subdirectory recursively.
The current cipher is a variation of the vigenere cipher where a 64-digit key
is used for shifting each character.
<br>
The C++ scripts in the subdirectories are the prototypes and do not have the
capability of the python scripts.
<br>
Note: Sometimes the decryption scripts bug out when run on Windows machines.
This may be due to the machines not being able to read some null or sub
characters or a file read bug. Both scripts run fine on Linux.
