#include <iostream>
#include "CVigenere.h"
#include "CFriends.h"
#include "CUser.h"

using namespace std;


int main()
{
    //Variables
    char chName[128];
    int wahl;
    

    cout << "Create user...\n";
    cout << "Enter name: ";
    cin.getline(chName, 127);
    CUser user(chName);

    cout << "Logged in as " << user.getName() << endl;
    
    do
    {
        cout << "--- MINI CRYPTO ---" << endl;
        cout << "1: Encrypt Message " << endl;
        cout << "2: Decrypt Message " << endl;
        cout << "3: Add friend      " << endl;
        cout << "4: Show friends    " << endl;
        cout << "5: Leave Programm  " << endl;
        cout << ">"; cin>>wahl;

        switch(wahl)
        {
            case(1):
            {
                user.encryptMessage();
                cout << endl;
            }break;

            case(2):
            {
                user.decryptMessage();
                cout << endl;
            }break;

            case(3):
            {
                user.addFriend();
                cout << endl;
            }break;

            case(4):
            {
                user.showFriends();
                cout << endl;
            }break;

            case(5):
            {
                cout << "Programm closing...\n\n";
            }break;

            default:
            {
                cout << "Worng input! \n\n";
            }
        }
    }while(wahl != 5);
    
}
