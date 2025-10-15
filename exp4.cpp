//To implement Polyalphabetic cipher encryption decryption.
//Encryption/Decryption: Based on substitution, using multiple substitution
//Alphabets
//implementing Vigenere cipher
#include <iostream>
#include <string>
using namespace std;

// Function to generate repeating key (ignores non-alphabet characters)
string generateKey(const string &text, const string &key) {
    string newKey;
    int j = 0; // index for key
    for (size_t i = 0; i < text.size(); i++) {
        if (isalpha(text[i])) {
            newKey.push_back(key[j % key.size()]);
            j++;
        } else {
            newKey.push_back(text[i]); // keep spaces/punctuation aligned
        }
    }
    return newKey;
}

// Encrypt function
string encryptText(const string &text, const string &key) {
    string cipher_text;
    for (size_t i = 0; i < text.size(); i++) {
        if (isupper(text[i])) {
            char x = ((text[i] - 'A') + (toupper(key[i]) - 'A')) % 26 + 'A';
            cipher_text.push_back(x);
        } else if (islower(text[i])) {
            char x = ((text[i] - 'a') + (tolower(key[i]) - 'a')) % 26 + 'a';
            cipher_text.push_back(x);
        } else {
            cipher_text.push_back(text[i]); // leave spaces/punctuation
        }
    }
    return cipher_text;
}

// Decrypt function
string decryptText(const string &cipher_text, const string &key) {
    string orig_text;
    for (size_t i = 0; i < cipher_text.size(); i++) {
        if (isupper(cipher_text[i])) {
            char x = ((cipher_text[i] - 'A') - (toupper(key[i]) - 'A') + 26) % 26 + 'A';
            orig_text.push_back(x);
        } else if (islower(cipher_text[i])) {
            char x = ((cipher_text[i] - 'a') - (tolower(key[i]) - 'a') + 26) % 26 + 'a';
            orig_text.push_back(x);
        } else {
            orig_text.push_back(cipher_text[i]);
        }
    }
    return orig_text;
}

int main() {
    string text, keyword;

    cout << "Enter plaintext: ";
    getline(cin, text);

    cout << "Enter key (letters only): ";
    cin >> keyword;

    string key = generateKey(text, keyword);
    string cipher_text = encryptText(text, key);

    cout << "\nEncrypted Text : " << cipher_text << endl;
    cout << "Decrypted Text : " << decryptText(cipher_text, key) << endl;

    return 0;
}
