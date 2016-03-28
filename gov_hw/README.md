# US Government Class Homework

Using pdf2txt.py, we dump the contents of the textbook into a text file, stored
in /raw. We then parse the text file to extract a meaningful summary of each
chapter, which we have dumped into /summary.

## Dependencies
```
sudo pip install --upgrade 3to2           # Runs on Python 2.7
sudo pip install --upgrade language-check
```

## Scripts
```
./generate.py [chapter text file] [section]
./generate.py raw/ch01.txt 1    # Generates a summary of Section 1 of Chapter 1
./generate.py raw/ch01.txt 1 > summary/1_1.txt  # Example usage
```

## Creators
  - omgimanerd (Alvin Lin)
  - bleepbloopsify (Leon Chou)
