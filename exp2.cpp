// ins lab / exp2.cpp
// To implement Monoalphabetic decryption. Encrypting and Decrypting
// works exactly the same for all monoalphabetic ciphers.
// Encryption/Decryption: Every letter in the alphabet is represented by
// exactly one other letter in the key.

#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

// Function to build mapping from standard to key alphabet
unordered_map<char, char> buildMap(const string& from, const string& to) {
    unordered_map<char, char> map;
    for (int i = 0; i < 26; ++i) {
        map[from[i]] = to[i];
    }
    return map;
}

// Function to encrypt or decrypt text
string monoalphabeticCipher(const string& text, const unordered_map<char, char>& map) {
    string result = "";
    for (char c : text) {
        if (isupper(c)) {
            result += toupper(map.at(tolower(c)));
        } else if (islower(c)) {
            result += map.at(c);
        } else {
            result += c; // Keep non-alphabetic characters unchanged
        }
    }
    return result;
}

int main() {
    string plainAlphabet = "abcdefghijklmnopqrstuvwxyz";

    // Monoalphabetic key (must be a permutation of 26 unique letters)
    string keyAlphabet ="qwertyuiopasdfghjklzxcvbnm"; // key

    // Build encrypt and decrypt maps
    unordered_map<char, char> encryptMap = buildMap(plainAlphabet, keyAlphabet);
    unordered_map<char, char> decryptMap = buildMap(keyAlphabet, plainAlphabet);

    int choice;
    string input;

    cout << "Monoalphabetic Cipher\n";
    cout << "1. Encrypt\n2. Decrypt\nChoose (1 or 2): ";
    cin >> choice;
    cin.ignore(); // flush newline

    cout << "Enter text: ";
    getline(cin, input);

    if (choice == 1) {
        cout << "Encrypted Text: " << monoalphabeticCipher(input, encryptMap) << endl;
    } else if (choice == 2) {
        cout << "Decrypted Text: " << monoalphabeticCipher(input, decryptMap) << endl;
    } else {
        cout << "Invalid choice." << endl;
    }

    return 0;
}
