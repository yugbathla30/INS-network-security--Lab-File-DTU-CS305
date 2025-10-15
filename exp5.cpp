// To implement Hill- cipher encryption decryption
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// Function to get modulo inverse of a number under mod 26
int modInverse(int a, int m) {
	a = a % m;
	for (int x = 1; x < m; x++) {
		if ((a * x) % m == 1) return x;
	}
	return -1;
}

// Function to get determinant of matrix (only for 2x2 and 3x3)
int determinant(const vector<vector<int>> &mat, int n) {
	if (n == 2)
		return (mat[0][0]*mat[1][1] - mat[0][1]*mat[1][0]);
	else if (n == 3)
		return (mat[0][0]*(mat[1][1]*mat[2][2] - mat[1][2]*mat[2][1])
				- mat[0][1]*(mat[1][0]*mat[2][2] - mat[1][2]*mat[2][0])
				+ mat[0][2]*(mat[1][0]*mat[2][1] - mat[1][1]*mat[2][0]));
	return 0;
}

// Function to get adjoint of 2x2 or 3x3 matrix
vector<vector<int>> adjoint(const vector<vector<int>> &mat, int n) {
	vector<vector<int>> adj(n, vector<int>(n));
	if (n == 2) {
		adj[0][0] = mat[1][1];
		adj[0][1] = -mat[0][1];
		adj[1][0] = -mat[1][0];
		adj[1][1] = mat[0][0];
	} else if (n == 3) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				vector<vector<int>> temp(2, vector<int>(2));
				int r = 0;
				for (int k = 0; k < n; k++) {
					if (k == i) continue;
					int c = 0;
					for (int l = 0; l < n; l++) {
						if (l == j) continue;
						temp[r][c] = mat[k][l];
						c++;
					}
					r++;
				}
				adj[j][i] = ((temp[0][0]*temp[1][1] - temp[0][1]*temp[1][0]) * (((i+j)%2==0)?1:-1));
			}
		}
	}
	return adj;
}

// Function to get inverse of matrix mod 26
vector<vector<int>> inverseMatrix(const vector<vector<int>> &mat, int n) {
	int det = determinant(mat, n);
	det = (det % 26 + 26) % 26;
	int invDet = modInverse(det, 26);
	if (invDet == -1) {
		throw runtime_error("Key matrix is not invertible mod 26");
	}
	vector<vector<int>> adj = adjoint(mat, n);
	vector<vector<int>> inv(n, vector<int>(n));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int val = adj[i][j] * invDet;
			val = (val % 26 + 26) % 26;
			inv[i][j] = val;
		}
	}
	return inv;
}

// Function to multiply matrix and vector mod 26
vector<int> multiply(const vector<vector<int>> &mat, const vector<int> &vec, int n) {
	vector<int> res(n);
	for (int i = 0; i < n; i++) {
		int sum = 0;
		for (int j = 0; j < n; j++) {
			sum += mat[i][j] * vec[j];
		}
		res[i] = (sum % 26 + 26) % 26;
	}
	return res;
}

string processText(const string &text, int n) {
	string t = text;
	t.erase(remove_if(t.begin(), t.end(), [](char c){ return !isalpha(c); }), t.end());
	transform(t.begin(), t.end(), t.begin(), ::toupper);
	while (t.size() % n != 0) t += 'X';
	return t;
}

string encrypt(const string &plaintext, const vector<vector<int>> &key, int n) {
	string pt = processText(plaintext, n);
	string ct;
	for (size_t i = 0; i < pt.size(); i += n) {
		vector<int> block(n);
		for (int j = 0; j < n; j++) block[j] = pt[i+j] - 'A';
		vector<int> enc = multiply(key, block, n);
		for (int j = 0; j < n; j++) ct += (enc[j] + 'A');
	}
	return ct;
}

string decrypt(const string &ciphertext, const vector<vector<int>> &key, int n) {
	vector<vector<int>> invKey = inverseMatrix(key, n);
	string ct = processText(ciphertext, n);
	string pt;
	for (size_t i = 0; i < ct.size(); i += n) {
		vector<int> block(n);
		for (int j = 0; j < n; j++) block[j] = ct[i+j] - 'A';
		vector<int> dec = multiply(invKey, block, n);
		for (int j = 0; j < n; j++) pt += (dec[j] + 'A');
	}
	return pt;
}

int main() {
	int n;
	cout << "Enter size of key matrix (2 or 3): ";
	cin >> n;
	if (n != 2 && n != 3) {
		cout << "Only 2x2 or 3x3 matrices supported.\n";
		return 1;
	}
	vector<vector<int>> key(n, vector<int>(n));
	cout << "Enter key matrix (row-wise):\n";
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> key[i][j];
	cin.ignore();
	string text;
	cout << "Enter text: ";
	getline(cin, text);
	int choice;
	cout << "1. Encrypt\n2. Decrypt\nEnter choice: ";
	cin >> choice;
	try {
		if (choice == 1) {
			string ct = encrypt(text, key, n);
			cout << "Encrypted text: " << ct << endl;
		} else if (choice == 2) {
			string pt = decrypt(text, key, n);
			cout << "Decrypted text: " << pt << endl;
		} else {
			cout << "Invalid choice.\n";
		}
	} catch (const exception &e) {
		cout << "Error: " << e.what() << endl;
	}
	return 0;
}
