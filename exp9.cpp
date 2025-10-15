//9.write a program to generate SHA-1 hash
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <cstring>
#include <fstream>
#include <algorithm>

class SHA1 {
public:
    SHA1() { reset(); }

    void update(const std::string &s) {
        update(reinterpret_cast<const unsigned char*>(s.c_str()), s.size());
    }

    std::string final() {
        unsigned char digest[20];
        finalize(digest);

        std::ostringstream oss;
        for (int i = 0; i < 20; ++i)
            oss << std::hex << std::setw(2) << std::setfill('0') << (int)digest[i];
        return oss.str();
    }

    void reset() {
        h0 = 0x67452301;
        h1 = 0xEFCDAB89;
        h2 = 0x98BADCFE;
        h3 = 0x10325476;
        h4 = 0xC3D2E1F0;
        buffer.clear();
        bit_len = 0;
        finalized = false;
    }

private:
    uint32_t h0, h1, h2, h3, h4;
    std::vector<unsigned char> buffer;
    uint64_t bit_len = 0;
    bool finalized = false;

    static uint32_t leftrotate(uint32_t value, uint32_t bits) {
        return (value << bits) | (value >> (32 - bits));
    }

    void process_block(const unsigned char *block) {
        uint32_t w[80];

        for (int i = 0; i < 16; ++i) {
            w[i]  = (block[i * 4 + 0] << 24);
            w[i] |= (block[i * 4 + 1] << 16);
            w[i] |= (block[i * 4 + 2] << 8);
            w[i] |= (block[i * 4 + 3]);
        }

        for (int i = 16; i < 80; ++i)
            w[i] = leftrotate(w[i - 3] ^ w[i - 8] ^ w[i - 14] ^ w[i - 16], 1);

        uint32_t a = h0, b = h1, c = h2, d = h3, e = h4;

        for (int i = 0; i < 80; ++i) {
            uint32_t f, k;
            if (i < 20) { f = (b & c) | ((~b) & d); k = 0x5A827999; }
            else if (i < 40) { f = b ^ c ^ d; k = 0x6ED9EBA1; }
            else if (i < 60) { f = (b & c) | (b & d) | (c & d); k = 0x8F1BBCDC; }
            else { f = b ^ c ^ d; k = 0xCA62C1D6; }

            uint32_t temp = leftrotate(a, 5) + f + e + k + w[i];
            e = d;
            d = c;
            c = leftrotate(b, 30);
            b = a;
            a = temp;
        }

        h0 += a;
        h1 += b;
        h2 += c;
        h3 += d;
        h4 += e;
    }

    void update(const unsigned char *data, size_t len) {
        bit_len += len * 8;
        for (size_t i = 0; i < len; ++i) {
            buffer.push_back(data[i]);
            if (buffer.size() == 64) {
                process_block(buffer.data());
                buffer.clear();
            }
        }
    }

    void finalize(unsigned char digest[20]) {
        if (finalized) return;
        finalized = true;

        buffer.push_back(0x80);
        while ((buffer.size() % 64) != 56)
            buffer.push_back(0x00);

        unsigned char length_bytes[8];
        for (int i = 0; i < 8; ++i)
            length_bytes[7 - i] = (bit_len >> (i * 8)) & 0xFF;

        buffer.insert(buffer.end(), length_bytes, length_bytes + 8);

        for (size_t i = 0; i < buffer.size(); i += 64)
            process_block(&buffer[i]);

        uint32_t h[5] = {h0, h1, h2, h3, h4};
        for (int i = 0; i < 5; ++i) {
            digest[i * 4 + 0] = (h[i] >> 24) & 0xFF;
            digest[i * 4 + 1] = (h[i] >> 16) & 0xFF;
            digest[i * 4 + 2] = (h[i] >> 8) & 0xFF;
            digest[i * 4 + 3] = h[i] & 0xFF;
        }
    }
};

std::string hashString(const std::string& input) {
    SHA1 sha;
    sha.update(input);
    return sha.final();
}

void toLowerCase(std::string& str) {
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
}

bool verifyHash(const std::string& input, const std::string& target_hash) {
    std::string computed = hashString(input);
    std::string target = target_hash;
    toLowerCase(computed);
    toLowerCase(target);
    return computed == target;
}


int main() {
    while (true) {
        std::cout << "\n=== SHA-1 Tool ===" << std::endl;
        std::cout << "1. Hash a message" << std::endl;
        std::cout << "2. Verify message matches hash" << std::endl;
        std::cout << "3. Exit" << std::endl;
        std::cout << "\nChoice: ";
        
        int choice;
        std::cin >> choice;
        std::cin.ignore();
        
        if (choice == 1) {
            std::string input;
            std::cout << "Enter text to hash: ";
            std::getline(std::cin, input);
            std::cout << "SHA-1 hash: " << hashString(input) << std::endl;
            
        } else if (choice == 2) {
            std::string input, hash;
            std::cout << "Enter message: ";
            std::getline(std::cin, input);
            std::cout << "Enter hash: ";
            std::getline(std::cin, hash);
            
            if (verifyHash(input, hash)) {
                std::cout << "✓ Match! The message produces this hash." << std::endl;
            } else {
                std::cout << "✗ No match. The message does not produce this hash." << std::endl;
            }

        } else if (choice == 3) {
            std::cout << "Goodbye!" << std::endl;
            break;
            
        } else {
            std::cout << "Invalid choice." << std::endl;
        }
    }
    
    return 0;
}
