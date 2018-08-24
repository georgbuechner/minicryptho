#pragma once

#include <iostream>
#include <stdio.h>
#include <time.h>
#include <fstream>
#include <string>
#include <map>
#include "CVigenere.h"
#include "CFriends.h"
#include "CFunctions.h"


class CUser
{
    private: 
        char m_chName[128];
        char m_chEncryptedText[5000];
        char m_chDecryptedText[5000];

        CFriend* m_curFriend;
        std::map<std::string, CFriend*>* m_listFriends; 
    public:
        CUser(char* chName);
        void encryptMessage();
        void decryptMessage();

        void addFriend();
        void deleteFriend();
        void changeKey();
        void showFriends();
        void selectFriend();
        void showKey();

        char* getName() {
            return m_chName;
        }

        void load();
        void safe();
};
        
