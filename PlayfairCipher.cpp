#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

const int SIZE = 30;

void toLower(string &s) {
    transform(s.begin(), s.end(), s.begin(), ::tolower);
}

void removeSpaces(string &s) {
    s.erase(remove(s.begin(), s.end(), ' '), s.end());
}

int mod5(int x) {
    return (x + 5) % 5;
}

void genKey(const string &key, char tab[5][5]) {
    bool used[26] = { false };
    used['j' - 'a'] = true;
    int i = 0, j = 0;

    for (char ch : key) {
        if (!used[ch - 'a']) {
            tab[i][j++] = ch;
            used[ch - 'a'] = true;
            if (j == 5) i++, j = 0;
        }
    }

    for (char ch = 'a'; ch <= 'z'; ch++) {
        if (!used[ch - 'a']) {
            tab[i][j++] = ch;
            used[ch - 'a'] = true;
            if (j == 5) i++, j = 0;
        }
    }
}

void find(char tab[5][5], char a, char b, int pos[]) {
    if (a == 'j') a = 'i';
    if (b == 'j') b = 'i';
    for (int i = 0; i < 5; ++i)
        for (int j = 0; j < 5; ++j) {
            if (tab[i][j] == a) pos[0] = i, pos[1] = j;
            if (tab[i][j] == b) pos[2] = i, pos[3] = j;
        }
}

void prepareText(string &s) {
    if (s.length() % 2 != 0)
        s += 'z';
}

void playfair(string &s, char tab[5][5], int enc) {
    int p[4];
    for (size_t i = 0; i < s.length(); i += 2) {
        find(tab, s[i], s[i + 1], p);
        if (p[0] == p[2]) {
            s[i] = tab[p[0]][mod5(p[1] + enc)];
            s[i + 1] = tab[p[0]][mod5(p[3] + enc)];
        } else if (p[1] == p[3]) {
            s[i] = tab[mod5(p[0] + enc)][p[1]];
            s[i + 1] = tab[mod5(p[2] + enc)][p[1]];
        } else {
            s[i] = tab[p[0]][p[3]];
            s[i + 1] = tab[p[2]][p[1]];
        }
    }
}

int main() {
    string key, text;
    char tab[5][5];
    int choice;

    cout << "Enter key: ";
    getline(cin, key);

    cout << "Enter text: ";
    getline(cin, text);

    cout << "1. Encrypt\n2. Decrypt\nChoice: ";
    cin >> choice;

    toLower(key);
    toLower(text);
    removeSpaces(key);
    removeSpaces(text);
    prepareText(text);
    genKey(key, tab);

    if (choice == 1) {
        playfair(text, tab, 1);
        cout << "Cipher: " << text << endl;
    } else if (choice == 2) {
        playfair(text, tab, -1);
        cout << "Plain: " << text << endl;
    } else {
        cout << "Invalid choice." << endl;
    }

    return 0;
}
