//10. implement a digital signature algorithm
#include <iostream>
#include <string>
#include <cmath>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <vector>

// Simple big integer class for DSA operations (limited to 64-bit for simplicity)
class BigInt {
public:
    long long value;
    
    BigInt(long long v = 0) : value(v) {}
    
    BigInt operator+(const BigInt& other) const {
        return BigInt(value + other.value);
    }
    
    BigInt operator-(const BigInt& other) const {
        return BigInt(value - other.value);
    }
    
    BigInt operator*(const BigInt& other) const {
        return BigInt(value * other.value);
    }
    
    BigInt operator%(const BigInt& other) const {
        return BigInt(value % other.value);
    }
    
    bool operator==(const BigInt& other) const {
        return value == other.value;
    }
    
    bool operator<(const BigInt& other) const {
        return value < other.value;
    }
};

// Modular exponentiation: (base^exp) % mod
long long modPow(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    
    return result;
}

// Extended Euclidean Algorithm for modular inverse
long long modInverse(long long a, long long m) {
    long long m0 = m, x0 = 0, x1 = 1;
    
    if (m == 1) return 0;
    
    while (a > 1) {
        long long q = a / m;
        long long t = m;
        
        m = a % m;
        a = t;
        t = x0;
        
        x0 = x1 - q * x0;
        x1 = t;
    }
    
    if (x1 < 0) x1 += m0;
    
    return x1;
}

// Simple primality test (Miller-Rabin would be better for production)
bool isPrime(long long n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    
    for (long long i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }
    
    return true;
}

// Simple hash function (in production, use SHA-256)
long long simpleHash(const std::string& message) {
    long long hash = 0;
    for (char c : message) {
        hash = (hash * 31 + c) % 1000000007;
    }
    return hash;
}

class DSA {
private:
    long long p;  // Prime modulus
    long long q;  // Prime divisor of p-1
    long long g;  // Generator
    long long x;  // Private key
    long long y;  // Public key
    
    // Generate a prime number
    long long generatePrime(long long min, long long max) {
        srand(time(0));
        for (int attempts = 0; attempts < 1000; attempts++) {
            long long candidate = min + rand() % (max - min);
            if (isPrime(candidate)) {
                return candidate;
            }
        }
        return 0;
    }
    
    // Find a generator g
    long long findGenerator() {
        for (long long h = 2; h < p; h++) {
            g = modPow(h, (p - 1) / q, p);
            if (g > 1) {
                return g;
            }
        }
        return 2;
    }

public:
    DSA() : p(0), q(0), g(0), x(0), y(0) {}
    
    // Generate DSA parameters and keys
    void generateKeys() {
        std::cout << "Generating DSA parameters and keys..." << std::endl;
        
        // Generate prime q (smaller prime)
        q = generatePrime(1000, 5000);
        std::cout << "q (prime divisor): " << q << std::endl;
        
        // Generate prime p such that q divides (p-1)
        for (int i = 2; i < 100; i++) {
            long long candidate = i * q + 1;
            if (isPrime(candidate)) {
                p = candidate;
                break;
            }
        }
        std::cout << "p (prime modulus): " << p << std::endl;
        
        // Find generator g
        g = findGenerator();
        std::cout << "g (generator): " << g << std::endl;
        
        // Generate private key x (random number < q)
        srand(time(0) + 1);
        x = (rand() % (q - 1)) + 1;
        std::cout << "x (private key): " << x << std::endl;
        
        // Calculate public key y = g^x mod p
        y = modPow(g, x, p);
        std::cout << "y (public key): " << y << std::endl;
        
        std::cout << "\nKeys generated successfully!\n" << std::endl;
    }
    
    // Sign a message
    std::pair<long long, long long> sign(const std::string& message) {
        if (p == 0 || q == 0) {
            std::cout << "Error: Keys not generated yet!" << std::endl;
            return {0, 0};
        }
        
        // Hash the message
        long long h = simpleHash(message);
        std::cout << "Message hash: " << h << std::endl;
        
        // Generate random k (1 < k < q)
        srand(time(0) + rand());
        long long k = (rand() % (q - 2)) + 2;
        std::cout << "Random k: " << k << std::endl;
        
        // Calculate r = (g^k mod p) mod q
        long long r = modPow(g, k, p) % q;
        
        // Calculate s = (k^-1 * (h + x*r)) mod q
        long long k_inv = modInverse(k, q);
        long long s = (k_inv * (h + x * r)) % q;
        
        // Make sure r and s are not zero
        if (r == 0 || s == 0) {
            std::cout << "Error: Invalid signature (r or s is zero), regenerating..." << std::endl;
            return sign(message);
        }
        
        std::cout << "\nSignature generated:" << std::endl;
        std::cout << "r = " << r << std::endl;
        std::cout << "s = " << s << std::endl;
        
        return {r, s};
    }
    
    // Verify a signature
    bool verify(const std::string& message, long long r, long long s) {
        if (p == 0 || q == 0) {
            std::cout << "Error: Keys not generated yet!" << std::endl;
            return false;
        }
        
        // Check if r and s are in valid range
        if (r <= 0 || r >= q || s <= 0 || s >= q) {
            std::cout << "Invalid signature: r or s out of range" << std::endl;
            return false;
        }
        
        // Hash the message
        long long h = simpleHash(message);
        std::cout << "Message hash: " << h << std::endl;
        
        // Calculate w = s^-1 mod q
        long long w = modInverse(s, q);
        std::cout << "w = " << w << std::endl;
        
        // Calculate u1 = (h * w) mod q
        long long u1 = (h * w) % q;
        std::cout << "u1 = " << u1 << std::endl;
        
        // Calculate u2 = (r * w) mod q
        long long u2 = (r * w) % q;
        std::cout << "u2 = " << u2 << std::endl;
        
        // Calculate v = ((g^u1 * y^u2) mod p) mod q
        long long v1 = modPow(g, u1, p);
        long long v2 = modPow(y, u2, p);
        long long v = ((v1 * v2) % p) % q;
        std::cout << "v = " << v << std::endl;
        
        // Signature is valid if v == r
        return v == r;
    }
    
    void displayPublicKey() {
        std::cout << "\n=== Public Key ===" << std::endl;
        std::cout << "p = " << p << std::endl;
        std::cout << "q = " << q << std::endl;
        std::cout << "g = " << g << std::endl;
        std::cout << "y = " << y << std::endl;
    }
};

int main() {
    DSA dsa;
    std::string message;
    long long r = 0, s = 0;
    
    while (true) {
        std::cout << "\n=== Digital Signature Algorithm (DSA) ===" << std::endl;
        std::cout << "1. Generate Keys" << std::endl;
        std::cout << "2. Sign a Message" << std::endl;
        std::cout << "3. Verify a Signature" << std::endl;
        std::cout << "4. Display Public Key" << std::endl;
        std::cout << "5. Exit" << std::endl;
        std::cout << "\nChoice: ";
        
        int choice;
        std::cin >> choice;
        std::cin.ignore();
        
        if (choice == 1) {
            dsa.generateKeys();
            
        } else if (choice == 2) {
            std::cout << "Enter message to sign: ";
            std::getline(std::cin, message);
            
            auto signature = dsa.sign(message);
            r = signature.first;
            s = signature.second;
            
        } else if (choice == 3) {
            std::cout << "Enter message to verify: ";
            std::getline(std::cin, message);
            
            std::cout << "Enter r: ";
            std::cin >> r;
            std::cout << "Enter s: ";
            std::cin >> s;
            std::cin.ignore();
            
            std::cout << "\nVerifying signature..." << std::endl;
            bool isValid = dsa.verify(message, r, s);
            
            if (isValid) {
                std::cout << "\n✓ SIGNATURE VALID! The message is authentic." << std::endl;
            } else {
                std::cout << "\n✗ SIGNATURE INVALID! The message may have been tampered with." << std::endl;
            }
            
        } else if (choice == 4) {
            dsa.displayPublicKey();
            
        } else if (choice == 5) {
            std::cout << "Goodbye!" << std::endl;
            break;
            
        } else {
            std::cout << "Invalid choice." << std::endl;
        }
    }
    
    return 0;
}