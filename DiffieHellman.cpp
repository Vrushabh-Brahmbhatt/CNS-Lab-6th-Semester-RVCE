#include <iostream>
using namespace std;

// Modular exponentiation function (efficient method)
int modX(int base, int exp, int mod) {
    int res = 1;
    base %= mod;
    while (exp) {
        if (exp & 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return res;
}

int main() {
    int p, g;  // Prime modulus and primitive root

    cout << "Enter a prime number (p): ";
    cin >> p;

    cout << "Enter a primitive root modulo p (g): ";
    cin >> g;

    // Private keys of Alice and Bob
    int a, b;
    cout << "Enter Alice's private key (a): ";
    cin >> a;

    cout << "Enter Bob's private key (b): ";
    cin >> b;

    // Public keys using modX
    int A = modX(g, a, p);  // Alice's public key
    int B = modX(g, b, p);  // Bob's public key

    // Shared secret keys
    int secretA = modX(B, a, p);  // Alice computes secret
    int secretB = modX(A, b, p);  // Bob computes secret

    cout << "\nPublic values:\n";
    cout << "p = " << p << ", g = " << g << "\n";
    cout << "Alice's Public Key (A = g^a mod p): " << A << "\n";
    cout << "Bob's Public Key (B = g^b mod p): " << B << "\n";

    cout << "\nShared Secret Keys:\n";
    cout << "Alice's Secret Key: " << secretA << "\n";
    cout << "Bob's Secret Key: " << secretB << "\n";

    if (secretA == secretB) {
        cout << "\nKey exchange successful! Shared key = " << secretA << "\n";
    } else {
        cout << "\nKey exchange failed.\n";
    }

    return 0;
}
