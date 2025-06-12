#include <iostream>
#include <string>
#include <cctype>

using namespace std;

char shift(char m, char k, int dir) {
    int a = tolower(m) - 'a';
    int b = tolower(k) - 'a';
    return 'a' + (a + dir * b + 26) % 26;
}

void process(int mode) {
    string msg, key, res;

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

int main() {
    int ch;
    while (true) {
        cout << "Vigenère Cipher\n1 - Encrypt\n2 - Decrypt\n3 - Quit\nChoice: ";
        cin >> ch;

        if (ch == 1)
            process(1);
        else if (ch == 2)
            process(-1);
        else if (ch == 3)
            break;
        else
            cout << "Invalid choice!\n";
    }

    return 0;
}
