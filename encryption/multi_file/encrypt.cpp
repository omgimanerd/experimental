/*
 * File:   encrypt.cpp
 * Author: Alvin Lin (alvin.lin@stuypulse.com)
 * Multiple file encryption.
 * A text file named file.txt must exist for this to read the names
 * of all the files to encrypt. file.txt must contain the names of
 * all the files to encrypt. Each file name must include the extension
 * and be on its own line.
 * Created on August 28, 2014
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

// Given a string and a vector containing the values in the key, along with
// a counter for the current index, this function will return the encoded
// version of the given string.
string encode(string entryline,
              vector<int> vigenere_keyvector,
              int &charCounter) {
  string encodedline;
  int keydigits = vigenere_keyvector.size();
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

// keygen uses tostring function.
// Generates a key for encryption.
// Key is passed back by reference.
void keygen(vector<int> &vigenere_keyvector,
            string &outputkey,
            int keydigits) {
  srand(time(NULL));
  string keystring;

  // Generates key with specified number of digits and fills vector with digits.
  int temp;
  for (int i = 0; i < keydigits; i++) {
    temp = rand()%10;
    keystring.append(tostring(temp));
    vigenere_keyvector.push_back(temp);
  }

  // Generates dummy keystring.
  // Fills every other space with a garbage value - Even indices constitute key.
  for (int i = 0; i < keystring.length(); i++) {
    outputkey.append(1, keystring[i]);
    outputkey.append(tostring(rand()%10));
  }
}

int main(int argc, char** argv) {
  // First we must get the names of all the files to encrypt.
  ifstream file;
  file.open(".encrypt");
  if (file.fail()) {
    cout << "Could not read .encrypt" << endl;
    return 0;
  } else {
    cout << "Reading .encrypt" << endl;
  }
  // Vector to store the names of all the files to encrypt.
  vector<string> filenames;
  // Temporary storage for getline.
  string stor;
  while (getline(file, stor)) {
    filenames.push_back(stor);
  }
  // Closes input file.
  file.close();

  // Counter for the number of files actually encrypted.
  int encryptedfiles = 0;

  for (int i = 0; i < filenames.size(); i++) {
    ifstream infile;
    ofstream outfile;
    infile.open(filenames[i].c_str());
    if (infile.fail()) {
      cout << filenames[i] << " does not exist." << endl;
      continue;
    }
    else {
      cout << filenames[i] << " found and encrypted." << endl;
      encryptedfiles++;
    }

    // Takes all lines in the file and stores it into a vector.
    // Necessary because output file overwrites input file.
    vector<string> filestorage;
    // Temporary storage for getline
    string stor;
    while (getline(infile, stor)) {
      filestorage.push_back(stor);
    }
    infile.close(); // Closes input file.

    // Opens output file to overwrite input file
    outfile.open(filenames[i].c_str());
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
      outfile << encode(filestorage[i],
                        vigenere_keyvector,
                        charCounter) << endl;
    }
    // Closes output file
    outfile.close();
  }

  cout << "Encryption completed. " << encryptedfiles << " files encrypted." << endl;

  return 0;
}
