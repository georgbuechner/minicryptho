#pragma once

#include <iostream>
#include <string.h>

class CVigenere
{
    private:
        char m_chEncryptedText[128];
        char m_chDecryptedText[128];
    public:
        char* encryption(char* chText, char* chKey) 
        {
            unsigned int j = 0;
            for(unsigned int i=0; i<strlen(chText); i++)
            {
                j=i;
                if(j > strlen(chKey)-1)
                    j=0;

                int Text = (int)chText[i];
                int Key = (int)chKey[j] - 65;

                if(Text + Key >= 90)
                    m_chEncryptedText[i] = (char)Text-26+Key;
                else
                    m_chEncryptedText[i] = (char)Text+Key;
            }
            
            return m_chEncryptedText;
        }

        char* decryption(char* chText, char* chKey)
        {
            unsigned int j = 0;

            for(unsigned int i=0; i<strlen(chText); i++)
            {
                j=i;
                if(j > strlen(chKey)-1)
                    j=0;

                int Text = (int)chText[i];
                int Key = (int)chKey[j] - 65;

                if(Text-Key < 65)
                    m_chDecryptedText[i] = (char)Text+26-Key;
                else
                    m_chDecryptedText[i] = (char)Text-Key;
            }
            
            return m_chDecryptedText;
        }

    
};
            
            
            
