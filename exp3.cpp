//To implement Play fair cipher encryption-decryption.
// Generate the Key Table (5×5 grid of letters)
// Fill with the keyword (no duplicates).
// Fill remaining spaces with the rest of the alphabet (merge I and J into one cell).
// Prepare the Plaintext
// Convert to uppercase, remove spaces.
// Replace J with I.
// Split into digraphs (pairs of letters).
// If both letters are the same, insert an X between them.
// If there’s an odd number of letters, pad with X.
// Encryption Rules
// Same Row → replace each letter with the one to its right (wrap around).
// Same Column → replace each letter with the one below (wrap around).
// Rectangle → replace each letter with the letter in the same row but the column of the other letter.
// Decryption Rules (reverse of encryption)
// Same Row → replace each letter with the one to its left.
// Same Column → replace each letter with the one above.
// Rectangle → same as encryption (swap columns).

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cctype>

using namespace std;

class PlayfairCipher {
    vector<vector<char>> keyTable;
    map<char, pair<int, int>> pos; // letter -> (row, col)

public:
    PlayfairCipher(string key) {
        createKeyTable(key);
    }

    void createKeyTable(string key) {
        vector<bool> used(26, false);
        keyTable.assign(5, vector<char>(5, ' '));
        string filteredKey;

        // Uppercase, replace J with I, remove duplicates
        for (char c : key) {
            c = toupper(static_cast<unsigned char>(c));
            if (c == 'J') c = 'I';
            if (c < 'A' || c > 'Z') continue;
            if (!used[c - 'A']) {
                used[c - 'A'] = true;
                filteredKey.push_back(c);
            }
        }

        // Add remaining letters
        for (char c = 'A'; c <= 'Z'; c++) {
            if (c == 'J') continue;
            if (!used[c - 'A']) {
                used[c - 'A'] = true;
                filteredKey.push_back(c);
            }
        }

        // Fill 5x5 table
        int idx = 0;
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                keyTable[i][j] = filteredKey[idx];
                pos[filteredKey[idx]] = {i, j};
                idx++;
            }
        }
    }

    string prepareText(string text, bool forEncryption) {
        string processed;
        for (char c : text) {
            c = toupper(static_cast<unsigned char>(c));
            if (c == 'J') c = 'I';
            if (c >= 'A' && c <= 'Z') processed.push_back(c);
        }

        if (forEncryption) {
            string result;
            for (size_t i = 0; i < processed.size(); i++) {
                result.push_back(processed[i]);
                if (i + 1 == processed.size()) {
                    result.push_back('X'); // padding
                } else if (processed[i] == processed[i + 1]) {
                    result.push_back('X');
                } else {
                    result.push_back(processed[i + 1]);
                    i++;
                }
            }
            return result;
        }
        return processed; // For decryption, no digraph processing needed
    }

    string encrypt(string plaintext) {
        string text = prepareText(plaintext, true);
        string cipher;
        for (size_t i = 0; i < text.size(); i += 2) {
            char a = text[i], b = text[i + 1];
            pair<int, int> p1 = pos[a];
            pair<int, int> p2 = pos[b];
            int r1 = p1.first, c1 = p1.second;
            int r2 = p2.first, c2 = p2.second;


            if (r1 == r2) { // Same row
                cipher.push_back(keyTable[r1][(c1 + 1) % 5]);
                cipher.push_back(keyTable[r2][(c2 + 1) % 5]);
            } else if (c1 == c2) { // Same column
                cipher.push_back(keyTable[(r1 + 1) % 5][c1]);
                cipher.push_back(keyTable[(r2 + 1) % 5][c2]);
            } else { // Rectangle
                cipher.push_back(keyTable[r1][c2]);
                cipher.push_back(keyTable[r2][c1]);
            }
        }
        return cipher;
    }

    string decrypt(string ciphertext) {
        string text = prepareText(ciphertext, false);
        string plain;
        for (size_t i = 0; i < text.size(); i += 2) {
            char a = text[i], b = text[i + 1];
            auto [r1, c1] = pos[a];
            auto [r2, c2] = pos[b];

            if (r1 == r2) { // Same row
                plain.push_back(keyTable[r1][(c1 + 4) % 5]);
                plain.push_back(keyTable[r2][(c2 + 4) % 5]);
            } else if (c1 == c2) { // Same column
                plain.push_back(keyTable[(r1 + 4) % 5][c1]);
                plain.push_back(keyTable[(r2 + 4) % 5][c2]);
            } else { // Rectangle
                plain.push_back(keyTable[r1][c2]);
                plain.push_back(keyTable[r2][c1]);
            }
        }
        return plain;
    }

    void printKeyTable() {
        for (auto &row : keyTable) {
            for (char c : row) cout << c << ' ';
            cout << "\n";
        }
    }
};

int main() {
    string key, plaintext;

    cout << "Enter key: ";
    getline(cin, key);

    PlayfairCipher cipher(key);

    cout << "\nKey Table:\n";
    cipher.printKeyTable();

    cout << "\nEnter plaintext: ";
    getline(cin, plaintext);

    string encrypted = cipher.encrypt(plaintext);
    string decrypted = cipher.decrypt(encrypted);

    cout << "\nPlaintext:  " << plaintext;
    cout << "\nEncrypted:  " << encrypted;
    cout << "\nDecrypted:  " << decrypted << "\n";

    return 0;
}
