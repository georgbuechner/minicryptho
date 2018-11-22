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
        

CUser::CUser(char* chName)
{
    CFunctions F;
    F.allocate(m_chName, chName);
    m_listFriends = new std::map<std::string, CFriend*>;

    load();
}
    
void CUser::encryptMessage()
{
    //Variables
    CVigenere crypto;
    CFunctions function;

    //Select friend to get key
    selectFriend();
     
    //User Input - plain text
    std::string sPlainText;
    std::cout << "Plain test: ";
    function.m_getline(sPlainText);
    char* chPlainText = (char*)sPlainText.c_str();

    crypto.encryption(chPlainText, m_curFriend->getKey(), m_chEncryptedText);
    std::cout << "Encrypted text: " << m_chEncryptedText << "\n";
}

void CUser::decryptMessage()
{
    //Variables
    CVigenere crypto;
    CFunctions function;

    //select friend to get key
    selectFriend();

    //User input - encrypted text
    std::string sEncryptedText;
    std::cout << "Encrypted text: ";
    function.m_getline(sEncryptedText);
    char* chEncryptedText = (char*)sEncryptedText.c_str();

    //Decrypt text and print text
    crypto.decryption(chEncryptedText, m_curFriend->getKey(), m_chDecryptedText);
    std::cout << "Decrypted test: " << m_chDecryptedText << "\n";
}

void CUser::addFriend()
{
    //Variables
    CFunctions function;
    std::string sName;

    //User input
    std::cout << "Name: ";
    function.m_getline(sName);
    char* chName = (char*)sName.c_str();

    for(;;)
    {
        std::cout << "1: Generate key \n";
        std::cout << "2: Enter key \n"; 
        std::cout << "> "; 

        //User input
        std::string sInput;
        function.m_getline(sInput);
        char* chInput = (char*)sInput.c_str();

        if(function.compare(chInput, (char*)"1") == true || function.compare(chInput, (char*)"Generate key") == true)
        {
            srand(time(NULL));
            char chKey[5000];

            //Select security level
            int securityLevel = 0;
            for(;;)
            {
                std::cout << "Security level (1-10): ";

                //Player input
                std::string sSecurity;
                function.m_getline(sSecurity);
                char* chSecurity = (char*)sSecurity.c_str();

                if(function.compare(chSecurity, (char*)"1") == true || 
                    function.compare(chSecurity, (char*)"2") == true ||
                    function.compare(chSecurity, (char*)"3") == true || 
                    function.compare(chSecurity, (char*)"4") == true ||
                    function.compare(chSecurity, (char*)"5") == true || 
                    function.compare(chSecurity, (char*)"6") == true ||
                    function.compare(chSecurity, (char*)"7") == true || 
                    function.compare(chSecurity, (char*)"8") == true ||
                    function.compare(chSecurity, (char*)"9") == true || 
                    function.compare(chSecurity, (char*)"10") == true)
                 {
                    securityLevel = stoi(sSecurity);
                    break;
                 }
                
                 else
                    std::cout << "Worng input. Try again.\n";   
            }

            cout << "Selected security level " << securityLevel;
            std::cout << " = " << 50*securityLevel << " characters.\n";
            
            //Generate key
            for(int i=0; i<50*securityLevel*10; i++)
            {
                int iSecret = rand() % 26 + 65;
                chKey[i] = iSecret;
            }
            chKey[50*securityLevel] = '\0';

            CFriend* newFriend = new CFriend(chName, chKey);
            m_listFriends->insert(pair<std::string, CFriend*> (sName, newFriend));

            break;
        }

        else if(function.compare(chInput, (char*)"2") == true || function.compare(chInput, (char*)"Enter key") == true)
        {
            std::string sKey;
            std::cout << "Enter Key: ";
            function.m_getline(sKey);
            char* chKey = (char*)sKey.c_str();
            CFriend* newFriend = new CFriend(chName, chKey);
            m_listFriends->insert(pair<std::string, CFriend*> (sName, newFriend));
            break;
        }

        else
            std::cout << "Wrong input! \n\n";
    }

}

void CUser::deleteFriend()
{
    //Variables
    CFunctions function;

    //Select friend
    selectFriend();
    std::string sName(m_curFriend->getName());

    for(;;)
    {
        std::cout << "Sure you want to delete " << sName << "?\n";
        std::cout << "Y(es)/(N)o? >"; 

        std::string sInput;
        function.m_getline(sInput);
        char* chInput = (char*)sInput.c_str();

        if(function.compare(chInput, (char*)"Y") == true || function.compare(chInput, (char*)"y") == true)
        {
            m_listFriends->erase(sName);
            delete m_curFriend;
        
            std::cout << sName << " has been deleted.\n";
            return;
        }

        else if(function.compare(chInput, (char*)"N") == true ||function.compare(chInput, (char*)"n") == true)
        {
            std::cout << sName << " has  n o t  been deleted.\n";
            return;
        }

        else
            std::cout << "Wrong input!\n\n";
    }
}

/**
* changeKey: change the Key of a friend
* 1. generate new key
* 2. enter new key
**/
void CUser::changeKey()
{
    //Variables
    CFunctions function;

    //Select friend
    selectFriend();

    for(;;)
    {
        std::cout << "1. Generate new key?   \n";
        std::cout << "2. Enter new key?      \n";
        std::cout << "3. Changed your mind?  \n";
        std::cout << "> ";
        
        //User input
        std::string sInput;
        function.m_getline(sInput);
        char* chInput = (char*)sInput.c_str();

        if(function.compare(chInput, (char*)"1") == true ||
            function.contains(chInput, (char*)"Generate") == true)
        {
            srand(time(NULL));
            char chKey[5000];

            //Generate key
            for(int i=0; i<100; i++)
            {
                int iSecret = rand() % 26 + 65;
                chKey[i] = iSecret;
            }
            chKey[100] = '\0';

            //Set new key
            m_curFriend->setKey(chKey);

            break;
        }

        else if(function.compare(chInput, (char*)"2") == true ||
            function.contains(chInput, (char*)"Enter") == true)
        {
            //User input (new key)
            std::string sKey;
            std::cout << "Enter new key: ";
            function.m_getline(sKey);
            char* chKey = (char*)sKey.c_str();

            //Set new key
            m_curFriend->setKey(chKey);
            
            break;
        }

        else if(function.compare(chInput, (char*)"3") == true ||
            function.compare(chInput, (char*)"exit") == true)
        {
            std::cout << "Prozess of changing key stopped on own account\n"; 
            break;
        }

        else
            std::cout << "Wrong input! Enter \"exit\" to end prozess.\n";
    }
}    

/**
* selectFriend: select a friend from list of the users friends
**/
void CUser::selectFriend()
{
    //Variables
    CFunctions function;

    //Show friends
    showFriends();

    for(;;)
    {
        std::cout << "Select friend (enter name): ";
        std::string sInput;
        function.m_getline(sInput);

        if(m_listFriends->count(sInput) == 1)
        {
                m_curFriend = m_listFriends->find(sInput)->second;
                break;
        }
    }
}

void CUser::showFriends()
{
    unsigned int counter = 1;

    for(auto it=m_listFriends->begin(); it!=m_listFriends->end(); it++)
    {
        std::cout << counter << ": " << (*it).first << "\n"; 
        counter++;
    }
}

void CUser::showKey()
{
    selectFriend();

    std::cout << m_curFriend->getName() << "\n";
    std::cout << "Key: " << m_curFriend->getKey() << "\n";
}
    
/**
* safe: safes all friends into a list
*/
void CUser::safe()
{
    //Variables
    std::string sPath = "users";
    sPath.append(m_chName);
    sPath.append("/listFriends.txt");
    std::cout << sPath << "\n";
    ofstream write;
    write.open(sPath);
    
    for(auto it = m_listFriends->begin(); it != m_listFriends->end(); it++)
    {
        std::cout << (*it).second->getName() << " is being saved...\n";
        write << (*it).second->getName();
        write << " ";
        write << (*it).second->getKey(); 
        write << "\n";
    }    

    std::cout << "Saving finished.\n";
    write.close();
}

/**
* load: loades all friends into dictionary of friends (std::map<std::string, CFriend*>* m_listFriends)
**/
void CUser::load()
{
    //Variables
    CFunctions function;

    //Create path
    std::string sPath = "users/";
    sPath.append(m_chName);
    sPath.append("/listFriends.txt");

    //Open file
    ifstream read;
    read.open(sPath);

    //Check whether file could be openend
    if(!read)
    {
        std::cout << "No friends yet. Add some friends to send messages.\n";
        return;
    }

    //Parse file
    std::string sBuffer;
    char chName[128];
    std::string sKey;
    while(!read.eof())
    {
        //Create buffer and read new line from file into buffer
        std::string sBuffer;
        getline(read, sBuffer);

        //Check whether there is a new friend in this line or only parts of a key

        //Only key -> Read key
        if(sBuffer.find(" ") == std::string::npos)
            sKey.append(sBuffer);

        //New name -> read name & read begining of new key
        else
        {
            if(sKey.length() != 0)
            {
                //Create key as a char array and  name a string
                char* chKey = (char*)sKey.c_str();
                std::string sName(chName);

                //Create friend and add to dictionary of friends
                CFriend* newFriend = new CFriend(chName, chKey);
                m_listFriends->insert(std::pair<std::string, CFriend*> (sName, newFriend));
    
                function.clearMemory(chName);
                function.clearMemory(chKey);
            }

            //Read name
            size_t found = sBuffer.find(" ");
            size_t length = sBuffer.copy(chName, found, 0);
            chName[length] = '\0';

            //Read beginng of key
            sKey = sBuffer.erase(0, found+1);
        }
    }
    
    //Add last friend in list
    if(sKey.length() != 0)
    {    
        //Create key as a char array and  name a string
        char* chKey = (char*)sKey.c_str();
        std::string sName(chName);

        //Create friend and add to dictionary of friends
        CFriend* newFriend = new CFriend(chName, chKey);
        m_listFriends->insert(std::pair<std::string, CFriend*> (sName, newFriend));
    
        function.clearMemory(chName);
        function.clearMemory(chKey);
    }
        
}

