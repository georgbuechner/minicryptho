#include "CVigenere.h"

using namespace std;

/**
* encryption: encrypt a given text using vigere: move each character by number of 
* characters of the matching charater in the key along the alphabet
* @parameter char* chText (given plain text)
* @parameter char* chKey (given key for encryption) 
* @parameter char* chEncryptedText (char array to fill with encrypted text)
**/
void CVigenere::encryption(char* chText, char* chKey, char* chEncryptedText)
{
    //Clear memory of chEncryptedText
    for(unsigned int i=0; i<sizeof(chEncryptedText); i++)
        chEncryptedText[i] = '\0';

    unsigned int j = 0;
    //Loop over char array implementing encryption
    for(unsigned int i=0; i<strlen(chText); i++)
    {
        //Variables

        //Counter for key
        j=i;
        if(j > strlen(chKey)-1)
            j=0;

        //Cast key and text to integer 
        int Key = (int)chKey[j] - 65; 
        int Text = (int)chText[i];

        //Convert from non-capital to capital letter
        if(checkCapital(Text) == 0)
            Text -= 32;
        //Don't encrypt when not a letter
        else if(checkCapital(Text) == 2)
        {
            chEncryptedText[i] = chText[i];
            continue;
        }

        //Encrypt using vigenere
        if(Text + Key >= 90)
            chEncryptedText[i] = (char)Text-26+Key; //Corrct, when out of bounds 
        else
            chEncryptedText[i] = (char)Text+Key;    //Uncomplicated encryption
    }

    //Check that array does not contain nonsense character at the end
    chEncryptedText[strlen(chText)] = '\0';
}

/**
* decryption: decrypt a given text using vigere: move each character by number of 
* characters of the matching charater in the key along the alphabet
* @parameter char* chText (given encrypted text)
* @parameter char* chKey (given key for decryption) 
* @parameter char* chDecryptedText (char array to fill with decrypted text)
**/
void CVigenere::decryption(char* chText, char* chKey, char* chDecryptedText)
{
    //Clear memory of chDecryptedText
    for(unsigned int i=0; i<strlen(chDecryptedText); i++)
        chDecryptedText[i] = '\0';

    unsigned int j = 0;
    //Loop over char arry implementing
    for(unsigned int i=0; i<strlen(chText); i++)
    {
        //Variables

        //Counter vor key
        j=i;
        if(j > strlen(chKey)-1)
            j=0;
        
        //Cast key and text to integer
        int Key = (int)chKey[j] - 65;
        int Text = (int)chText[i];

        //Convert from non-capital to capital letters
        if(checkCapital(Text) == 0)
            Text -= 32;
        //Don't decrypt when not a letter
        else if(checkCapital(Text) == 2)
        {
            chDecryptedText[i] = chText[1];
            continue;
        }

        //Decrypting using vigenere
        if(Text-Key < 65)
            chDecryptedText[i] = (char)Text+26-Key; //Correct, when out of bounds
        else
            chDecryptedText[i] = (char)Text-Key;    //Uncomplicated decryption
    }

    //Check that array does not contain nonsense character at the end
    chDecryptedText[strlen(chText)] = '\0';
}

/**
* checkCapital: check wether given letter is a capital letter
* 0 -> no capital; 1 -> capital; 2 -> out of range
* @parameter char (letter)
* @return int
**/
int CVigenere::checkCapital(int value)
{
    //Capital letters between 65 and 90
    if(value >= 65 && value <= 90)
        return 1;
    //Non-capital letters between 97 and 122
    else if(value >= 97 && value <= 122)
        return 0;
    //Out of bounds
    else
        return 2;
}


