#pragma once

#include <iostream>
#include <string.h>
#include <string>

class CVigenere
{
    public:
        void encryption(char* chText, char* chKey, char* chEncryptedText) 
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
       }

       void decryption(char* chText, char* chKey, char* chDecryptedText)
       {   
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
            
            std::cout << chDecryptedText << "\n";
        }
};
            
            
            
