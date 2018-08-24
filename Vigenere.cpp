#include "CVigenere.h"

using namespace std;

void CVigenere::encryption(char* chText, char* chKey, char* chEncryptedText)
{
    for(unsigned int i=0; i<sizeof(chEncryptedText); i++)
        chEncryptedText[i] = '\0';

    unsigned int j = 0;
    for(unsigned int i=0; i<strlen(chText); i++)
    {
        int Text = (int)chText[i];
        if(Text > 90 || Text < 65)
        {
            chEncryptedText[i] = (char)Text;
            continue;
        }

        j=i;
        if(j > strlen(chKey)-1)
            j=0;

        int Key = (int)chKey[j] - 65;

        if(Text + Key >= 90)
            chEncryptedText[i] = (char)Text-26+Key;
        else
            chEncryptedText[i] = (char)Text+Key;
    }

    chEncryptedText[strlen(chText)] = '\0';
}


void CVigenere::decryption(char* chText, char* chKey, char* chDecryptedText)
{
    for(unsigned int i=0; i<strlen(chDecryptedText); i++)
        chDecryptedText[i] = '\0';

    unsigned int j = 0;
    for(unsigned int i=0; i<strlen(chText); i++)
    {
        int Text = (int)chText[i];
        if(Text > 90 || Text < 65)
        {
            chDecryptedText[i] = (char)Text;
            continue;
        }

        j=i;
        if(j > strlen(chKey)-1)
            j=0;

        int Key = (int)chKey[j] - 65;

        if(Text-Key < 65)
            chDecryptedText[i] = (char)Text+26-Key;
        else
            chDecryptedText[i] = (char)Text-Key;
    }

    chDecryptedText[strlen(chText)] = '\0';
}


