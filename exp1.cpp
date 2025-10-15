// experiment 1 
// To implement Caesar cipher encryption
// Encryption: Replace each plaintext letter with one a Fixed number of
// places down the alphabet.
// Decryption: Replace each cipher text letter with one a fixed number of
// places up the alphabet.
#include <iostream>
#include <string>
using namespace std;

// Encrypt a message using Caesar Cipher
string encrypt(string text, int shift) {
    string result = "";

    for (char c : text) {
        if (isupper(c)) {
            result += char((c - 'A' + shift) % 26 + 'A');
        } else if (islower(c)) {
            result += char((c - 'a' + shift) % 26 + 'a');
        } else {
            result += c; // leave non-alphabet characters unchanged
        }
    }

    return result;
}

// Decrypt a message using Caesar Cipher
string decrypt(string text, int shift) {
    string result = "";

    for (char c : text) {
        if (isupper(c)) {
            result += char((c - 'A' - shift + 26) % 26 + 'A');
        } else if (islower(c)) {
            result += char((c - 'a' - shift + 26) % 26 + 'a');
        } else {
            result += c;
        }
    }

    return result;
}

int main() {
    string text;
    int shift, choice;

    cout << "Caesar Cipher\n";
    cout << "1. Encrypt\n2. Decrypt\nChoose (1 or 2): ";
    cin >> choice;
    cin.ignore(); // ignore newline character left in input buffer

    cout << "Enter text: ";
    getline(cin, text);

    cout << "Enter shift value (e.g., 3): ";
    cin >> shift;

    if (choice == 1) {
        cout << "Encrypted Text: " << encrypt(text, shift) << endl;
    } else if (choice == 2) {
        cout << "Decrypted Text: " << decrypt(text, shift) << endl;
    } else {
        cout << "Invalid choice.\n";
    }

    return 0;
}
