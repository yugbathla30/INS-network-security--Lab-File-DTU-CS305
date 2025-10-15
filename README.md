# Information Security Lab 🔐

A comprehensive collection of cryptographic algorithms and security protocols implemented in C++. This repository contains implementations of classical and modern encryption techniques, hash functions, and digital signature algorithms as per the Information Security Laboratory curriculum.

## 📚 Table of Contents

- [Experiments Overview](#experiments-overview)
- [Prerequisites](#prerequisites)
- [Compilation & Execution](#compilation--execution)
- [Detailed Algorithm Descriptions](#detailed-algorithm-descriptions)
- [Usage Examples](#usage-examples)
- [Contributing](#contributing)

---

## 🔬 Experiments Overview

| Exp # | Aim | Algorithm | File |
|-------|-----|-----------|------|
| 1 | To implement Caesar cipher encryption | Caesar Cipher | `exp1.cpp` |
| 2 | To implement Monoalphabetic decryption | Monoalphabetic Cipher | `exp2.cpp` |
| 3 | To implement Playfair cipher encryption-decryption | Playfair Cipher | `exp3.cpp` |
| 4 | To implement Polyalphabetic cipher encryption decryption | Vigenère Cipher | `exp4.cpp` |
| 5 | To implement Hill cipher encryption decryption | Hill Cipher | `exp5.cpp` |
| 6 | To implement S-DES subkey generation | S-DES | `exp6.cpp` |
| 7 | To implement Diffie-Hellman key exchange algorithm | Diffie-Hellman | `exp7.cpp` |
| 8 | To implement RSA encryption-decryption | RSA | `exp8.cpp` |
| 9 | Write a program to generate SHA-1 hash | SHA-1 | `exp9.cpp` |
| 10 | Implement a digital signature algorithm | DSA | `exp10.cpp` |

---

## 🛠️ Prerequisites

- **Compiler**: G++ with C++11 support or later
- **Operating System**: Linux, macOS, or Windows (with MinGW)
- **Terminal**: Command-line interface

---

## 🚀 Compilation & Execution

### General Compilation

```bash
g++ -std=c++11 exp<number>.cpp -o exp<number>
./exp<number>
```

### Example

```bash
g++ -std=c++11 exp1.cpp -o exp1
./exp1
```

---

## 📖 Detailed Algorithm Descriptions

### Experiment 1: Caesar Cipher
**Aim**: To implement Caesar cipher encryption

**Encryption**: Replace each plaintext letter with one a fixed number of places down the alphabet.

**Decryption**: Replace each cipher text letter with one a fixed number of places up the alphabet.

**File**: `exp1.cpp`

**Usage**:
```bash
./exp1
Choose (1=Encrypt / 2=Decrypt): 1
Enter text: Hello World
Enter shift value: 3
```

**Output**: `Khoor Zruog`

**Features**:
- Supports both encryption and decryption
- Preserves non-alphabetic characters
- Case-insensitive operations
- Configurable shift value

---

### Experiment 2: Monoalphabetic Cipher
**Aim**: To implement Monoalphabetic decryption. Encrypting and Decrypting works exactly the same for all monoalphabetic ciphers.

**Encryption/Decryption**: Every letter in the alphabet is represented by exactly one other letter in the key.

**File**: `exp2.cpp`

**Key Alphabet**: `qwertyuiopasdfghjklzxcvbnm`

**Usage**:
```bash
./exp2
Choose (1=Encrypt / 2=Decrypt): 1
Enter text: security
```

**Output**: Encrypted text based on substitution key

**Features**:
- Fixed substitution key mapping
- Bidirectional encryption/decryption
- Preserves case and non-alphabetic characters

---

### Experiment 3: Playfair Cipher
**Aim**: To implement Playfair cipher encryption-decryption.

**File**: `exp3.cpp`

**Description**: Encrypts pairs of letters (digraphs) using a 5×5 key matrix.

**Encryption/Decryption Rules**:
- **Same Row** → shift right (wrap around)
- **Same Column** → shift down (wrap around)
- **Rectangle** → swap columns

**Key Matrix Generation**:
1. Fill with keyword (no duplicates)
2. Fill remaining with alphabet (I and J combined)

**Usage**:
```bash
./exp3
Enter key: monarchy
Choose (1=Encrypt / 2=Decrypt): 1
Enter plaintext: hello world
```

**Features**:
- Dynamic key matrix generation
- Handles repeated letters with 'X' insertion
- Pads odd-length text with 'X'
- Displays the 5×5 key table

---

### Experiment 4: Polyalphabetic Cipher
**Aim**: To implement Polyalphabetic cipher encryption decryption.

**Encryption/Decryption**: Based on substitution, using multiple substitution alphabets.

**Implementation**: Vigenère Cipher

**File**: `exp4.cpp`

**Description**: Uses a repeating keyword to shift letters by different amounts, providing better security than monoalphabetic ciphers.

**Usage**:
```bash
./exp4
Choose (1=Encrypt / 2=Decrypt): 1
Enter plaintext: ATTACKATDAWN
Enter key: LEMON
```

**Output**: `LXFOPVEFRNHR`

**Features**:
- Repeating key mechanism
- Ignores non-alphabetic characters in key generation
- Multiple substitution alphabets based on key
- Resistant to frequency analysis

**Formula**:
- Encryption: `C[i] = (P[i] + K[i]) mod 26`
- Decryption: `P[i] = (C[i] - K[i] + 26) mod 26`

---

### Experiment 5: Hill Cipher
**Aim**: To implement Hill cipher encryption decryption.

**File**: `exp5.cpp`

**Description**: Matrix-based cipher using linear algebra for encryption and decryption.

**Supported**: 2×2 and 3×3 key matrices

**Usage**:
```bash
./exp5
Enter size of key matrix (2 or 3): 2
Enter key matrix (row-wise):
3 3
2 5
Choose (1=Encrypt / 2=Decrypt): 1
Enter text: HELP
```

**Key Requirements**:
- Matrix must be invertible modulo 26
- Determinant must be coprime to 26

**Mathematical Operations**:
- **Encryption**: `C = K × P (mod 26)`
- **Decryption**: `P = K⁻¹ × C (mod 26)`

**Features**:
- Dynamic key matrix input
- Automatic padding with 'X'
- Matrix inversion mod 26
- Error handling for non-invertible matrices

---

### Experiment 6: S-DES Subkey Generation
**Aim**: To implement S-DES subkey generation.

**File**: `exp6.cpp`

**Description**: Generates two 8-bit subkeys (K1, K2) from a 10-bit master key using permutation and circular shift operations.

**Process**:
1. P10 permutation on 10-bit key
2. Split into two 5-bit halves
3. Circular left shift
4. P8 permutation → K1
5. Another circular left shift
6. P8 permutation → K2

**Usage**:
```bash
./exp6
Enter a 10-bit binary key: 1010000010
```

**Output**:
```
Subkey K1: 10100100
Subkey K2: 01000011
```

**Permutation Tables**:
- **P10**: {3, 5, 2, 7, 4, 10, 1, 9, 8, 6}
- **P8**: {6, 3, 7, 4, 8, 5, 10, 9}

---

### Experiment 7: Diffie-Hellman Key Exchange
**Aim**: To implement Diffie-Hellman key exchange algorithm.

**File**: `exp7.cpp`

**Description**: Allows two parties (Alice and Bob) to establish a shared secret key over an insecure channel without exchanging the secret directly.

**Parameters**:
- **Prime modulus (P)**: 23 (publicly known)
- **Generator (G)**: 9 (publicly known)
- **Alice's private key (a)**: 4
- **Bob's private key (b)**: 3

**Key Exchange Process**:
1. Alice computes: `x = G^a mod P`
2. Bob computes: `y = G^b mod P`
3. Exchange x and y publicly
4. Alice computes: `ka = y^a mod P`
5. Bob computes: `kb = x^b mod P`
6. Result: `ka = kb` (shared secret)

**Usage**:
```bash
./exp7
```

**Output**:
```
The value of P: 23
The value of G: 9
Alice's public key (x): 6
Bob's public key (y): 16
Alice's secret key: 9
Bob's secret key: 9
```

**Security**: Based on the difficulty of computing discrete logarithms.

---

### Experiment 8: RSA Encryption-Decryption
**Aim**: To implement RSA encryption-decryption.

**File**: `exp8.cpp`

**Description**: Asymmetric encryption algorithm based on the mathematical difficulty of factoring large prime numbers.

**Key Generation**:
1. Select two prime numbers: `p = 7919`, `q = 1009`
2. Compute `n = p × q = 7,989,071`
3. Compute `φ(n) = (p-1)(q-1)`
4. Choose public exponent `e` where `gcd(e, φ(n)) = 1`
5. Compute private exponent `d` where `(e × d) mod φ(n) = 1`

**Usage**:
```bash
./exp8
```

**Output**:
```
Public Key (e, n): (5, 7989071)
Private Key (d, n): (4791245, 7989071)
Original Message: 123
Encrypted Message: 4051753
Decrypted Message: 123
```

**Mathematical Operations**:
- **Encryption**: `C = M^e mod n`
- **Decryption**: `M = C^d mod n`

**Note**: 
- Works for integer messages only
- Primes are hardcoded for demonstration
- Production systems use much larger primes (2048+ bits)

---

### Experiment 9: SHA-1 Hash Generation
**Aim**: Write a program to generate SHA-1 hash.

**File**: `exp9.cpp`

**Description**: Generates a 160-bit (40 hexadecimal characters) cryptographic hash from input text, ensuring data integrity.

**Features**:
1. **Hash Generation**: Convert any text to SHA-1 hash
2. **Hash Verification**: Verify if a message matches a given hash
3. **Case-insensitive comparison**

**Usage**:
```bash
./exp9

=== SHA-1 Hash Generator ===
1. Hash a message
2. Verify message matches hash
3. Exit

Choice: 1
Enter text to hash: Hello World
```

**Output**: 
```
SHA-1 Hash: 0a4d55a8d778e5022fab701977c5d840bbc486d0
```

**Verification Example**:
```bash
Choice: 2
Enter message: Hello World
Enter expected hash: 0a4d55a8d778e5022fab701977c5d840bbc486d0
✓ Hash matches! Message is authentic.
```

**Algorithm Steps**:
1. Message padding (append bit '1', zeros, and length)
2. Break into 512-bit blocks
3. Process each block with 80 rounds
4. Produce 160-bit hash value

**⚠️ Security Note**: SHA-1 is deprecated due to collision vulnerabilities. Use SHA-256 or SHA-3 in production.

---

### Experiment 10: Digital Signature Algorithm (DSA)
**Aim**: Implement a digital signature algorithm.

**File**: `exp10.cpp`

**Description**: Provides authentication, message integrity, and non-repudiation using asymmetric cryptography.

**Components**:
- **Parameters**: p (prime), q (prime divisor), g (generator)
- **Keys**: x (private key), y (public key)
- **Signature**: (r, s) pair

**Menu Options**:
1. **Generate Keys** - Create DSA parameters and key pair
2. **Sign Message** - Create digital signature
3. **Verify Signature** - Validate signature authenticity
4. **Display Public Key** - Show public parameters
5. **Exit**

**Usage**:

**Step 1: Generate Keys**
```bash
./exp10
Enter your choice: 1

[Generates p, q, g, x, y]
```

**Step 2: Sign a Message**
```bash
Enter your choice: 2
Enter message to sign: Hello World

Digital Signature (r, s):
r = 1234
s = 5678
```

**Step 3: Verify Signature**
```bash
Enter your choice: 3
Enter message to verify: Hello World
Enter r value: 1234
Enter s value: 5678

✓ SIGNATURE IS VALID!
```

**Signature Generation**:
1. Hash the message
2. Generate random k
3. Compute `r = (g^k mod p) mod q`
4. Compute `s = (k⁻¹ × (hash + x×r)) mod q`

**Signature Verification**:
1. Compute `w = s⁻¹ mod q`
2. Compute `u1 = (hash × w) mod q`
3. Compute `u2 = (r × w) mod q`
4. Compute `v = ((g^u1 × y^u2) mod p) mod q`
5. Signature valid if `v = r`

**Properties**:
- ✅ Authentication (verifies sender identity)
- ✅ Integrity (detects message tampering)
- ✅ Non-repudiation (sender cannot deny signing)

---

## 💡 Usage Examples

### Caesar Cipher (Experiment 1)
```bash
# Encrypt
./exp1
1
Enter text: HELLO
Enter shift: 3
Output: KHOOR

# Decrypt
./exp1
2
Enter text: KHOOR
Enter shift: 3
Output: HELLO
```

### Hill Cipher (Experiment 5)
```bash
./exp5
Enter size: 2
Enter key matrix:
6 24
1 13
Enter text: HELP
1. Encrypt
Output: GTKP
```

### SHA-1 Hash (Experiment 9)
```bash
./exp9
1
Enter text: password123
Output: cbfdac6008f9cab4083784cbd1874f76618d2a97
```

### Digital Signature (Experiment 10)
```bash
./exp10
# Step 1: Generate keys
1

# Step 2: Sign message
2
Enter message: Confidential Document

# Step 3: Verify signature
3
Enter message: Confidential Document
[Enter r and s values from signing]
Output: ✓ SIGNATURE VALID
```

---

## 📊 Algorithm Comparison

| Algorithm | Type | Key Size | Security Level | Use Case |
|-----------|------|----------|----------------|----------|
| Caesar | Symmetric | 1-25 | Very Low | Learning |
| Monoalphabetic | Symmetric | 26! permutations | Low | Learning |
| Playfair | Symmetric | 25! permutations | Low | Historical |
| Vigenère | Symmetric | Variable | Low-Medium | Learning |
| Hill | Symmetric | Matrix size | Medium | Learning |
| DES | Symmetric | 56 bits | Obsolete | Legacy systems |
| Diffie-Hellman | Key Exchange | Variable | High | Key establishment |
| RSA | Asymmetric | 1024-4096 bits | High | Encryption, Signatures |
| SHA-1 | Hash | N/A | Deprecated | Legacy verification |
| DSA | Digital Signature | 1024-3072 bits | High | Authentication |

---

## 📝 Important Notes

### Security Considerations

⚠️ **For Educational Purposes Only**

These implementations are designed for learning cryptographic concepts. They are **NOT** suitable for production use due to:

#### Classical Ciphers (Experiments 1-5)
- ❌ Vulnerable to frequency analysis
- ❌ Small key spaces
- ❌ No confusion/diffusion properties
- ✅ Good for understanding basic principles

#### Modern Algorithms (Experiments 6-10)
- ⚠️ Use larger keys in production (2048+ bits for RSA)
- ⚠️ Implement proper random number generation
- ⚠️ SHA-1 is deprecated (use SHA-256/SHA-3)
- ⚠️ Use established libraries (OpenSSL, Crypto++)

### Best Practices for Production

1. **Use Standard Libraries**: OpenSSL, Crypto++, libsodium
2. **Key Sizes**: 
   - RSA: ≥ 2048 bits
   - AES: 128/192/256 bits
   - DSA: ≥ 2048 bits
3. **Hash Functions**: SHA-256, SHA-3, BLAKE2
4. **Random Number Generation**: Cryptographically secure RNG
5. **Key Management**: Secure storage, rotation policies

---

## 🔧 Troubleshooting

### Compilation Errors

**Issue**: `error: 'to_string' is not a member of 'std'`
```bash
# Solution: Use C++11 or later
g++ -std=c++11 file.cpp -o output
```

**Issue**: Linking errors on macOS
```bash
# Solution: Ensure Xcode Command Line Tools installed
xcode-select --install
```

### Runtime Issues

**Hill Cipher**: "Key matrix not invertible mod 26"
```bash
# Solution: Use a matrix with determinant coprime to 26
# Valid 2×2 example:
3 3
2 5
# (determinant = 9, gcd(9,26) = 1)
```

**DSA**: "Keys not generated yet"
```bash
# Solution: Always generate keys first (Option 1)
```

**SHA-1**: Hash mismatch during verification
```bash
# Solution: 
# 1. Ensure exact message match
# 2. Comparison is case-insensitive for hashes
# 3. Check for extra spaces or newlines
```

---

## 📚 Learning Path

### Week 1-2: Classical Ciphers
- ✅ Experiment 1: Caesar Cipher
- ✅ Experiment 2: Monoalphabetic Cipher
- ✅ Experiment 3: Playfair Cipher
- ✅ Experiment 4: Vigenère Cipher
- ✅ Experiment 5: Hill Cipher

**Learning Outcomes**: Understanding substitution, transposition, and basic cryptanalysis.

### Week 3-4: Modern Cryptography
- ✅ Experiment 6: S-DES Subkey Generation
- ✅ Experiment 7: Diffie-Hellman Key Exchange
- ✅ Experiment 8: RSA Encryption-Decryption

**Learning Outcomes**: Public-key cryptography, key exchange protocols, modular arithmetic.

### Week 5: Hash Functions & Digital Signatures
- ✅ Experiment 9: SHA-1 Hash Generation
- ✅ Experiment 10: Digital Signature Algorithm

**Learning Outcomes**: Message integrity, authentication, non-repudiation.

---

## 📖 Resources

### Books
- *Applied Cryptography* by Bruce Schneier
- *Introduction to Modern Cryptography* by Katz & Lindell
- *Cryptography and Network Security* by William Stallings

### Online Resources
- [Cryptography on Wikipedia](https://en.wikipedia.org/wiki/Cryptography)
- [NIST Cryptographic Standards](https://csrc.nist.gov/)
- [Coursera - Cryptography Courses](https://www.coursera.org/)
- [Khan Academy - Cryptography](https://www.khanacademy.org/computing/computer-science/cryptography)

### Tools
- [CyberChef](https://gchq.github.io/CyberChef/) - Web-based crypto tool
- [OpenSSL](https://www.openssl.org/) - Production-grade library
- [CrypTool](https://www.cryptool.org/) - Educational crypto software

---

## 🎯 Learning Objectives

After completing these experiments, you should be able to:

### Theoretical Understanding
✅ Differentiate between classical and modern cryptography  
✅ Explain symmetric vs. asymmetric encryption  
✅ Understand the role of hash functions  
✅ Describe digital signature mechanisms  
✅ Explain key exchange protocols  

### Practical Skills
✅ Implement basic encryption algorithms  
✅ Perform modular arithmetic operations  
✅ Work with matrices in cryptography  
✅ Generate and verify digital signatures  
✅ Analyze cipher vulnerabilities  

### Security Awareness
✅ Identify weak encryption methods  
✅ Understand importance of key size  
✅ Recognize deprecated algorithms  
✅ Apply best practices for secure implementation  

---

## 🤝 Contributing

Contributions are welcome! Areas for improvement:

- 🐛 Bug fixes
- ⚡ Performance optimizations
- 📝 Documentation enhancements
- 🔐 Additional algorithms (AES, SHA-256, ECC)
- 🧪 Unit tests
- 🎨 Code refactoring

### How to Contribute
1. Fork the repository
2. Create a feature branch (`git checkout -b feature/improvement`)
3. Commit changes (`git commit -am 'Add new feature'`)
4. Push to branch (`git push origin feature/improvement`)
5. Create Pull Request

---

## 📄 License

This project is for educational purposes. Feel free to use and modify for learning.

---

## 👨‍💻 Author

Information Security Laboratory  
Academic Year: 2024-2025

---

## 📞 Support

For questions or issues:
- 📧 Create an issue in the repository
- 💬 Discussion forum (if available)
- 📚 Refer to the experiment manual

---

## 🏆 Acknowledgments

- Faculty of Computer Science Department
- Cryptography course instructors
- Open-source cryptography community

---

**Happy Learning! 🎓🔐**

*"In cryptography, we trust mathematics, not miracles."*
