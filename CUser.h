#pragma once

#include <iostream>
#include <string>
#include <list>
#include "CVigenere.h"
#include "CFriends.h"
#include "CFunctions.h"


class CUser
{
    private: 
        char m_chName[128];
        char m_chEncryptedText[128];
        char m_chDecryptedText[128];

        CFriend* m_curFriend;
        std::list<CFriend*>* m_listFriends; 
    public:
        CUser(char* chName);
        void encryptMessage();
        void decryptMessage();

        void addFriend();
        void showFriends();

        char* getName() {
            return m_chName;
        }

        void m_getline(std::string &var);
};
        
