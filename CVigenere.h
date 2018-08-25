#pragma once

#include <iostream>
#include <string.h>

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
            
            
            
