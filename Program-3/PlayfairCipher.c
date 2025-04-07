#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 100

void preprocess(char* str, int* len, int fillZ) {
    int i, j = 0;
    for (i = 0; str[i]; ++i)
        if (str[i] != ' ') str[j++] = tolower(str[i] == 'j' ? 'i' : str[i]);
    if (fillZ && j % 2) str[j++] = 'z';
    str[j] = '\0'; *len = j;
}

void buildKeyTable(char* key, char keyT[5][5]) {
    int used[26] = {0}, i = 0, j = 0;
    for (int k = 0; key[k]; ++k) {
        char ch = (key[k] == 'j') ? 'i' : key[k];
        if (!used[ch - 'a']) {
            keyT[i][j++] = ch; used[ch - 'a'] = 1;
            if (j == 5) i++, j = 0;
        }
    }
    for (int k = 0; k < 26; ++k)
        if (!used[k] && k + 'a' != 'j') {
            keyT[i][j++] = k + 'a';
            if (j == 5) i++, j = 0;
        }
}

void locate(char keyT[5][5], char a, char b, int* pos) {
    for (int i = 0; i < 5; ++i)
        for (int j = 0; j < 5; ++j) {
            if (keyT[i][j] == a) pos[0] = i, pos[1] = j;
            if (keyT[i][j] == b) pos[2] = i, pos[3] = j;
        }
}

void playfair(char* str, char keyT[5][5], int len, int mode) {
    int p[4];
    for (int i = 0; i < len; i += 2) {
        locate(keyT, str[i], str[i+1], p);
        if (p[0] == p[2]) {
            str[i]   = keyT[p[0]][(p[1] + mode + 5) % 5];
            str[i+1] = keyT[p[0]][(p[3] + mode + 5) % 5];
        } else if (p[1] == p[3]) {
            str[i]   = keyT[(p[0] + mode + 5) % 5][p[1]];
            str[i+1] = keyT[(p[2] + mode + 5) % 5][p[1]];
        } else {
            str[i]   = keyT[p[0]][p[3]];
            str[i+1] = keyT[p[2]][p[1]];
        }
    }
}

int main() {
    char key[SIZE], text[SIZE], keyT[5][5];
    int choice, len;

    printf("Key: "); fgets(key, SIZE, stdin);
    printf("Text: "); fgets(text, SIZE, stdin);
    printf("1. Encrypt  2. Decrypt\nChoice: "); scanf("%d", &choice);

    key[strcspn(key, "\n")] = 0; text[strcspn(text, "\n")] = 0;
    preprocess(key, &len, 0); preprocess(text, &len, choice == 1);
    buildKeyTable(key, keyT);
    playfair(text, keyT, len, (choice == 1 ? 1 : -1));

    printf("%s text: %s\n", (choice == 1 ? "Encrypted" : "Decrypted"), text);
    return 0;
}
