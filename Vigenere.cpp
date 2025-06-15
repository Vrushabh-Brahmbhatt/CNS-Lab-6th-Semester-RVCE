#include <iostream>
#include <string>
#include <cctype>

using namespace std;

char shift(char m, char k, int dir) {
    int a = tolower(m) - 'a';
    int b = tolower(k) - 'a';
    return 'a' + (a + dir * b + 26) % 26;
}

int main() {
    int ch;

    while (true) {
        cout << "Vigenère Cipher\n1 - Encrypt\n2 - Decrypt\n3 - Quit\nChoice: ";
        cin >> ch;

        if (ch == 1 || ch == 2) {
            string msg, key, res;
            int mode = (ch == 1) ? 1 : -1;

            cout << "Enter message: ";
            cin >> msg;

            cout << "Enter key: ";
            cin >> key;

            int len = msg.length();
            int klen = key.length();

            for (int i = 0; i < len; i++) {
                res += shift(msg[i], key[i % klen], mode);
            }

            if (mode == 1)
                cout << "Encrypted message: " << res << "\n\n";
            else
                cout << "Decrypted message: " << res << "\n\n";
        } 
        else if (ch == 3) {
            break;
        } 
        else {
            cout << "Invalid choice!\n";
        }
    }

    return 0;
}
