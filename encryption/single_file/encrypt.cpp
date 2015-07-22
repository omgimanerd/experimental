/**
 * File:   encrypt.cpp
 * Author: Alvin Lin (alvin.lin@stuypulse.com)
 * Single file encryption.
 * Created on July 23, 2013, 7:05 PM
 */
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

template <typename T>
string tostring(T number) {
  return dynamic_cast<stringstream *> (&(stringstream() << number))->str();
}

string encode(string entryline, vector<int> vigenere_keyvector,
              int keydigits, int &charCounter) {
  string encodedline;
  // Standard vigenere form.
  // Greater than 256 is automatically handled. 0 = 256, 1 = 257, 2 = 258, etc
  for (int i = 0; i < entryline.length(); i++) {
    encodedline.append(1, (char)((int)entryline.at(i) +
                                 vigenere_keyvector[charCounter % keydigits]));
    charCounter++;
    if (charCounter > keydigits) {charCounter %= keydigits;}
  }
  return encodedline;
}

// keygen uses tostring
// Generates a key for encryption
void keygen(vector<int> &vigenere_keyvector, string &outputkey, int keydigits) {
  srand(time(NULL));
  string keystring;

  // Generates key with specified number of digits and fills vector with digits
  int temp;
  for (int i = 0; i < keydigits; i++) {
    temp = rand()%10;
    keystring.append(tostring(temp));
    vigenere_keyvector.push_back(temp);
  }

  // Generates dummy keystring
  // Fills every other space with a garbage value - Even indices constitute key
  for (int i = 0; i < keystring.length(); i++) {
    outputkey.append(1, keystring[i]);
    outputkey.append(tostring(rand()%10));
  }
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
  //Temporary storage for getline
  string stor;
  while (getline(infile, stor)) {
    filestorage.push_back(stor);
  }
  infile.close(); // Closes input file

  // ###########################################################################
  // ##############################ENCRYPTING###################################
  // ###########################################################################

  // Output file to overwrite input file
  outfile.open(argv[1]);

  // Key storage for vigenere ciphers
  vector <int> vigenere_keyvector;
  // Number of digits to generate for the encryption key
  int keydigits = 64;
  // Storage for a dummy version of the key that will be outputted
  string outputkey;
  // Character counter for the vigenere ciphers
  // Prevents encryption algorithm from resetting count with each line
  int charCounter = 0;
  // Generates key and outputkey, returned by reference
  keygen(vigenere_keyvector, outputkey, keydigits);

  // Writes encryption method and key to top of file
  outfile << "P" << outputkey << endl;
  // Gets, encodes, and outputs every line after the first line
  // Will leave a trailing newline
  for (int i = 0; i < filestorage.size(); i++) {
    outfile << encode(filestorage[i], vigenere_keyvector, keydigits, charCounter) << endl;
  }

  // Closes output file
  outfile.close();

  cout << "Encryption finished." << endl;

  return 0;
}
