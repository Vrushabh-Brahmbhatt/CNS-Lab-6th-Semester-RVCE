#include <iostream>
#include <string>

using namespace std;

const string POLY = "10001000000100001";  // CRC-CCITT

void xorOperation(string &segment, const string &poly) {
    for (size_t i = 0; i < poly.size(); ++i)
        segment[i] = (segment[i] == poly[i]) ? '0' : '1';
}

string computeCRC(const string &data, const string &poly) {
    string padded = data + string(poly.size() - 1, '0');

    for (size_t i = 0; i <= padded.size() - poly.size(); ++i) {
        if (padded[i] == '1') {
            string segment = padded.substr(i, poly.size());
            xorOperation(segment, poly);
            padded.replace(i, poly.size(), segment);
        }
    }

    return padded.substr(data.size());
}

string generateCodeword(const string &data, const string &poly) {
    string crc = computeCRC(data, poly);
    string codeword = data + crc;

    cout << "\nChecksum: " << crc << "\nFinal Codeword: " << codeword << "\n";
    return codeword;
}

void detectError(string codeword, const string &poly) {
    for (size_t i = 0; i <= codeword.size() - poly.size(); ++i) {
        if (codeword[i] == '1') {
            string segment = codeword.substr(i, poly.size());
            xorOperation(segment, poly);
            codeword.replace(i, poly.size(), segment);
        }
    }

    // Check if the remainder has any '1'
    if (codeword.substr(codeword.size() - poly.size() + 1).find('1') != string::npos)
        cout << "Error detected.\n";
    else
        cout << "No error detected.\n";
}

int main() {
    string data;
    int choice, pos;

    cout << "Enter data: ";
    cin >> data;

    string codeword = generateCodeword(data, POLY);

    cout << "\nTest error detection? (0-Yes / 1-No): ";
    cin >> choice;

    if (choice == 0) {
        cout << "Enter position to flip: ";
        cin >> pos;

        if (pos >= 0 && pos < codeword.size()) {
            codeword[pos] = (codeword[pos] == '0') ? '1' : '0';
            cout << "Corrupted Codeword: " << codeword << "\n";
            detectError(codeword, POLY);
        } else {
            cout << "Invalid position.\n";
        }
    }

    return 0;
}

