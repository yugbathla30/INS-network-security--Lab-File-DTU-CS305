// to implement S-DES sub key generation 
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Function to permute the key based on the given permutation table
string permute(const string& key, const vector<int>& table) {
    string permutedKey;
    for (int i : table) {
        permutedKey += key[i - 1]; // -1 for zero-based indexing
    }
    return permutedKey;
}

// Function to perform left shift on the given bits
string leftShift(const string& bits) {
    return bits.substr(1) + bits[0]; // Shift left
}

// Function to generate subkeys K1 and K2 from the given key
void generateSubkeys(const string& key, string& K1, string& K2) {
    // P10 and P8 permutation tables
    vector<int> P10 = {3, 5, 2, 7, 4, 10, 1, 9, 8, 6};
    vector<int> P8 = {6, 3, 7, 4, 8, 5, 10, 9};

    // Step 1: Permute the key using P10
    string permutedKey = permute(key, P10);

    // Step 2: Split the key into two halves
    string leftHalf = permutedKey.substr(0, 5);
    string rightHalf = permutedKey.substr(5, 5);

    // Step 3: Generate K1
    leftHalf = leftShift(leftHalf);
    rightHalf = leftShift(rightHalf);
    K1 = permute(leftHalf + rightHalf, P8);

    // Step 4: Generate K2
    leftHalf = leftShift(leftHalf);
    rightHalf = leftShift(rightHalf);
    K2 = permute(leftHalf + rightHalf, P8);
}

int main() {
    string key;
    
    // Input 10-bit binary key
    cout << "Enter a 10-bit binary key: ";
    cin >> key;

    // Validate key length
    if (key.length() != 10) {
        cout << "Error: Key must be exactly 10 bits long." << endl;
        return 1;
    }

    // Variables to hold the subkeys
    string K1, K2;

    // Generate subkeys
    generateSubkeys(key, K1, K2);

    // Output the subkeys
    cout << "Subkey K1: " << K1 << endl;
    cout << "Subkey K2: " << K2 << endl;

    return 0;
}
