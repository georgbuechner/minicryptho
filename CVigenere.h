#pragma once

#include <iostream>
#include <string.h>
#include "CBase64.h"
#include "CFunctions.h"

class CVigenere
{
    public:
        /**
        * encryption: encrypt a given text using vigere: move each character by number of 
        * characters of the matching charater in the key along the alphabet
        * @parameter char* chText (given plain text)
        * @parameter char* chKey (given key for encryption) 
        * @parameter char* chEncryptedText (char array to fill with encrypted text)
        **/
        void encryption(char* chText, char* chKey, char* chEncryptedText);

        /**
        * encryption: encrypt a given text using vigere: move each character by number of 
        * characters of the matching charater in the key along the alphabet
        * @parameter char* chText (given plain text)
        * @parameter char* chKey (given key for encryption) 
        * @parameter char* chEncryptedText (char array to fill with encrypted text)
        **/
        void decryption(char* chText, char* chKey, char* chDecryptedText);

        /**
        * checkCapital: check wether given letter is a capital letter
        * 0 -> no capital; 1 -> capital; 2 -> out of range
        * @parameter char (letter)
        * @return int
        **/
        int checkCapital(int value);

};
            
            
/**
* encryption: encrypt a given text using vigere: move each character by number of 
* characters of the matching charater in the key along the alphabet
* @parameter char* chText (given plain text)
* @parameter char* chKey (given key for encryption) 
* @parameter char* chEncryptedText (char array to fill with encrypted text)
**/
void CVigenere::encryption(char* chText, char* chKey, char* chEncryptedText)
{

    CFunctions function;

    //Clear memory of chEncryptedText
    function.clearMemory(chEncryptedText);

    unsigned int j = 0; //counter for key
    unsigned int x = 0; //Counter for multible of 12...
    //unsigned int y = 1; //Counter for multible of 12...
    //Loop over char array implementing encryption
    for(unsigned int i=0; i<strlen(chText); i++)
    {
        //Counter for key
        j=i;
        if(j > strlen(chKey)-1)
            j=0;

        //Cast key and text to integer 
        int Key = static_cast<int>(chKey[j])-65;
        int Text = static_cast<int>(chText[i]);

        chEncryptedText[i-x] = static_cast<char>(Text+Key);    //Uncomplicated encryption
    }

    std::string sBase64 = base64_encode(reinterpret_cast<unsigned char const*>(chEncryptedText), strlen(chEncryptedText));
    function.clearMemory(chEncryptedText);
    function.allocate(chEncryptedText, const_cast<char*>(sBase64.c_str()));   

    //Check that array does not contain nonsense character at the end
    chEncryptedText[sBase64.length()] = '\0';

    
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
    CFunctions function;

    std::string sBase64 = chText;
    std::string sNoBase64 = base64_decode(sBase64);
    
    function.clearMemory(chDecryptedText);
    function.clearMemory(chText);
    function.allocate(chText, const_cast<char*>(sNoBase64.c_str()));
    

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
        int Key = static_cast<int>(chKey[j])-65;
        int Text = static_cast<int>(chText[i]);

        //Decrypting using vigenere
        chDecryptedText[i] = static_cast<char>(Text-Key);    //Uncomplicated decryption
    }

    cout << "Decryption succsesful.\n";
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

           
