#include "CUser.h"

using namespace std;

CUser::CUser(char* chName)
{
    CFunctions F;
    F.allocate(m_chName, chName);
    m_listFriends = new list<CFriend*>;
}
    
void CUser::encryptMessage()
{
    //Variables
    CVigenere crypto;
    bool bWahl = false;
    int counter = 1;

    showFriends();
    do
    {
        cout << "Select friend (number): ";
        string sInput;
        m_getline(sInput);
        
        cout << sInput << endl;

        for(auto it=m_listFriends->begin(); it!=m_listFriends->end(); it++)
        {
            cout << counter << endl;
            if(stoi(sInput) == counter)
            {
                m_curFriend = (*it);
                bWahl = true;
                break;
            }
            counter++;
        }
        
        if(bWahl == false)
            cout << "Wrong input!\n\n";
    }while(bWahl == false);
 
    //User Input

    //Plain Text
    string sPlainText;
    cout << "Plain test: ";
    m_getline(sPlainText);
    char* chPlainText = (char*)sPlainText.c_str();

    crypto.encryption(chPlainText, m_curFriend->getKey(), m_chEncryptedText);
    cout << "Encrypted text: " << m_chEncryptedText << "\n";
}

void CUser::decryptMessage()
{
    //Variables
    CVigenere crypto;

    //User input

    //Encrypted text
    string sEncryptedText;
    cout << "Encrypted text: ";
    m_getline(sEncryptedText);
    char* chEncryptedText = (char*)sEncryptedText.c_str();

    //Key
    string sKey;
    cout << "Key: ";
    m_getline(sKey);
    char* chKey = (char*)sKey.c_str();

    crypto.decryption(chEncryptedText, chKey, m_chDecryptedText);
    cout << "Decrypted test: " << m_chDecryptedText << "\n";
}

void CUser::addFriend()
{
    //Variables
    int wahl;
    string sName;

    //User input
    cout << "Name: ";
    m_getline(sName);
    char* chName = (char*)sName.c_str();

    do
    {
        cout << "1: Generate key \n";
        cout << "2: Enter key \n"; 
        cout << "> "; cin >> wahl;

        if(wahl == 1)
        {
            char* chKey = (char*)"ICHBINEINKLEINERPISSER";
            CFriend* newFriend = new CFriend(chName, chKey);
            m_listFriends->push_back(newFriend);
        }
        else if(wahl == 2)
        {
            string sKey;
            cout << "Enter Key: ";
            m_getline(sKey);
            char* chKey = (char*)sKey.c_str();
            CFriend* newFriend = new CFriend(chName, chKey);
            m_listFriends->push_back(newFriend);
        }

        else
            cout << "Wrong input! \n\n";
    }
    while(wahl != 1 && wahl != 2);

}

void CUser::showFriends()
{
    unsigned int counter = 1;

    for(auto it=m_listFriends->begin(); it!=m_listFriends->end(); it++)
    {
        cout << counter << ": " << (*it)->getName() << endl;
        counter++;
    }
}
    
    
void CUser::m_getline(string &var)
{
    for(;;)
    {
        cout.flush();
        getline(cin, var);
        if(var!="")
            break;
    }
}


