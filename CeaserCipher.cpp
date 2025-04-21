#include <iostream>
#include <cctype>
#include <string>

using namespace std;

int main() {
    string text;
    char ch;
    int key, choice;

    cout << "1. Encrypt\n2. Decrypt\nEnter your choice: ";
    cin >> choice;
    cout << "Enter a message: ";
    cin >> text;
    cout << "Enter the key: ";
    cin >> key;

    for (int i = 0; text[i] != '\0'; ++i) {
        ch = text[i];

        if (isalnum(ch)) {
            if (choice == 1) {  // Encryption
                if (islower(ch)) {
                    ch = (ch - 'a' + key) % 26 + 'a';
                } else if (isupper(ch)) {
                    ch = (ch - 'A' + key) % 26 + 'A';
                } else if (isdigit(ch)) {
                    ch = (ch - '0' + key) % 10 + '0';
                }
            }
            else if (choice == 2) {  // Decryption
                if (islower(ch)) {
                    ch = (ch - 'a' - key + 26) % 26 + 'a';
                } else if (isupper(ch)) {
                    ch = (ch - 'A' - key + 26) % 26 + 'A';
                } else if (isdigit(ch)) {
                    ch = (ch - '0' - key + 10) % 10 + '0';
                }
            } else {
                cout << "Invalid choice! Please enter 1 or 2." << endl;
                return 1;
            }
        } else {
            cout << "Invalid character in the message." << endl;
            return 1;
        }

        text[i] = ch;
    }

    if (choice == 1) {
        cout << "Encrypted message: " << text << endl;
    } else if (choice == 2) {
        cout << "Decrypted message: " << text << endl;
    }

    return 0;
}

