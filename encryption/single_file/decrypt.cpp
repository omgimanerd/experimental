/**
 * File:   decrypt.cpp
 * Author: Alvin Lin (alvin.lin@stuypulse.com)
 * Single file decryption.
 * Created on July 23, 2013, 7:05 PM
 */
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

string decode(string entryline,
              vector<int> vigenere_keyvector,
              int keydigits,
              int &charCounter) {
  string decodedline;
  // Start vigenere form.
  // Greater than 256 is automatically handled.
  for (int i = 0; i < entryline.length(); i++) {
    decodedline.append(1, (char)((int)entryline.at(i) -
                                 vigenere_keyvector[charCounter % keydigits]));
    charCounter++;
    if (charCounter > keydigits) {charCounter %= keydigits;}
  }
  return decodedline;
}

// Isolates the key from the keystring since key is every other digit
void keyfind(string keystring,
             vector<int> &vigenere_keyvector,
             int &keydigits) {
  // Loop appends every other character starting at 1 to remove encryption
  // label and get actual key
  for (int i = 1; i < keystring.length(); i+=2) {
    vigenere_keyvector.push_back((int)keystring[i] - (int)'0');
  }
  // Can decode this cipher with any key length
  keydigits = vigenere_keyvector.size();
}

int main(int argc, char** argv) {

  ifstream infile;
  ofstream outfile;

  infile.open(argv[1]);
  if(infile.fail()) {
    cout << "Invalid file." << endl;
    cout << "Usage: " << argv[0] << " <filename>" << endl;
    return 0;
  }
  else {
    cout << "File verified." << endl;
  }

  // Takes all lines in the file and stores it into a vector
  // Necessary because output file overwrites input file
  vector <string> filestorage;
  // Temporary storage for getline
  string stor;
  while (getline(infile, stor)) {
    filestorage.push_back(stor);
  }
  infile.close(); // Closes input file

  // ###########################################################################
  // #################################DECRYPTING################################
  // ###########################################################################

  // Storage for whole keystring
  string keystring = filestorage[0];
  // Erases key from filestorage
  filestorage.erase(filestorage.begin());
  // Storage of the part of the key for vigenere ciphers
  vector<int> vigenere_keyvector;
  // Storage for the number of digits in the key
  int keydigits;
  // Character counter for vigenere cipher
  int charCounter = 0;
  //Decrypts dummy key and returns actual key in a vector
  keyfind(keystring, vigenere_keyvector, keydigits);

  // Only decrypts files if they are encrypted by matching encryption algorithm
  // denoted by P at the beginning of the keystring
  if (keystring.at(0) == 'P') {
    // Opens output file to overwrite input file if an only if the keystring is
    // valid.
    outfile.open(argv[1]);
    // Gets, decodes, and outputs every line after the first line
    // Will leave a trailing newline
    for (int i = 0; i < filestorage.size(); i++) {
      outfile << decode(filestorage[i],
                        vigenere_keyvector,
                        keydigits,
                        charCounter) << endl;
    }
    // Closes output file
    outfile.close();

    cout << "Decryption finished." << endl;
  }
  // If it is unable to read the keystring, or if the file is not encrypted
  // with this algorithm, then it will reoutput the file as is.
  else {
    cout << "Unable to decode, invalid keystring." << endl;
  }

  return 0;
}
