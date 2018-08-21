#include <iostream>
#include "vigenere.h"

using namespace std;


int main()
{
    CVigenere crypto;
    char chPlainText[128];
    char chKey[128];

    cout << (char)91 << endl;

    cout << "Plain text: ";
    cin.getline(chPlainText, 127);
    cout << "Key: ";
    cin.getline(chKey, 127);

    cout << "Encrypted text: " << crypto.encryption(chPlainText, chKey) << endl;
    cout << "Decrypted text: " << crypto.decryption(crypto.encryption(chPlainText, chKey), chKey) << endl;
}
