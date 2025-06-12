#include <iostream>
#include <string>
using namespace std;

const string POLY = "10001000000100001";

string xorStrings(string a, const string &b) {
    for (size_t i = 0; i < b.size(); ++i)
        a[i] = (a[i] == b[i]) ? '0' : '1';
    return a;
}

string computeCRC(string data, const string &poly) {
    data += string(poly.size() - 1, '0');
    for (size_t i = 0; i <= data.size() - poly.size(); ++i)
        if (data[i] == '1')
            data.replace(i, poly.size(), xorStrings(data.substr(i, poly.size()), poly));
    return data.substr(data.size() - poly.size() + 1);
}

bool hasError(string codeword, const string &poly) {
    for (size_t i = 0; i <= codeword.size() - poly.size(); ++i)
        if (codeword[i] == '1')
            codeword.replace(i, poly.size(), xorStrings(codeword.substr(i, poly.size()), poly));
    return codeword.substr(codeword.size() - poly.size() + 1).find('1') != string::npos;
}

int main() {
    string data;
    int choice, pos;

    cout << "Enter data: ";
    cin >> data;

    string crc = computeCRC(data, POLY);
    string codeword = data + crc;

    cout << "\nChecksum: " << crc << "\nFinal Codeword: " << codeword << "\n";

    cout << "\nTest error detection? (0-Yes / 1-No): ";
    cin >> choice;

    if (choice == 0) {
        cout << "Enter position to flip: ";
        cin >> pos;
        if (pos >= 0 && pos < codeword.size()) {
            codeword[pos] = (codeword[pos] == '0') ? '1' : '0';
            cout << "Corrupted Codeword: " << codeword << "\n";
            cout << (hasError(codeword, POLY) ? "Error detected.\n" : "No error detected.\n");
        } else {
            cout << "Invalid position.\n";
        }
    }
    return 0;
}
