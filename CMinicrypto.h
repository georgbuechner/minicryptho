#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <dirent.h>
#include <cstdlib>
#include <unistd.h>
#include "CUser.h"
#include "CFunctions.h"

class CMinicrypto
{
private:
    CUser* m_user;  //Logged in user

public:

    /**
    * programmStart: User can selct between login with an existing account or registering
    * with a new account. Function then calls login/ register. Afterwars programmRunning 
    * will be called.
    **/
    void programmStart();

    /**
    * registerUser: register as a new user
    */
    bool registerUser();

    /**
    * loginUser: log in with an existing user 
    **/
    bool loginUser();

    /**
    * programmRunning: main loop of the programm after the user is logged in. User can choose 
    * between 1. encrypt message, 2. decrypt message, 3. add friend, 4. delete friend, 5. change 
    * key, 6. show friends, 7. show friend's key, 8. leave programm. 
    **/
    void programmRunning();
};
    
    
/**
* programmStart: user can decide between login or register as a new user
* function then calls login/ register and afterwards goes into programmRunning
*/
void CMinicrypto::programmStart() 
{
    //Variabels
    CFunctions function;

    //Loop, for player input: 1. register new user; 2. login with exiting user; 3. close programm
    for(;;)
    {
        //User options:
        std::cout << "--- Minicrypto --- \n";
        std::cout << "1. Register        \n";
        std::cout << "2. Login           \n";
        std::cout << "3. Leave           \n";
        std::cout << "> "; 

        //User input (number or content):
        std::string sInput;
        function.m_getline(sInput);
        char* chInput = (char*)sInput.c_str();

        //Select user input

        //Register with new account
        if(function.compare(chInput, (char*) "1") == true ||
            function.compare(chInput, (char*)"Register") == true)
        {
            //Call registerUser(), if return is falls, close programm
            if(registerUser() == false)
            {
                std::cout << "Programm closed due to error. We're sorry. \n";
                return;
            }

            //if true, then call programmRunning() to enter main loop
            programmRunning();
        }

        //Log in with existing account
        else if(function.compare(chInput, (char*)"2") == true ||
            function.compare(chInput, (char*)"Login") == true)
        {
            //Call loginUser(), if return is falls, close program
            if(loginUser() == false)
            {
                std::cout << "Programm closed due to error. We're sorry. \n";
                return;
            }

            //if true, then call programmRunning() to enter main loop
            programmRunning();
        }

        //Close programm
        else if(function.compare(chInput, (char*)"3") == true ||
            function.compare(chInput, (char*)"Leave") == true)
        {
            std::cout << "Closing programm...\n";
            return; 
        }

        //Wrong input
        else
            std::cout << "Wrong input!\n";

        std::cout << "\n";
    } 

    //End message
    std::cout << "Thank you for using \"MINI CRYPTO\"\n";
}

/**
* registerUser: register a new user
**/
bool CMinicrypto::registerUser()
{
    //Variables
    CFunctions function;

    //Open directory
    DIR *dir_allUsers;
    struct dirent* e_user;

    dir_allUsers = opendir("users");

    //Check whether directory could be opened
    if(!dir_allUsers)
    {
        std::cout << "Fatal error! Dictionary not found!\n";
        return false;
    }

    //Loop, till user registered or quit the programm
    for(;;)
    {
        //User input: user name
        std::cout << "User name (no space): ";
        std::string sUserName;
        function.m_getline(sUserName);
        char* chUserName = (char*)sUserName.c_str();
        
        //Check whether user already exists
        bool nameUsed = false;
        while((e_user = readdir(dir_allUsers)) != NULL)
        {
            std::string sCurUser = e_user->d_name;
            if(function.compare(chUserName, (char*)sCurUser.c_str()) == true)
            {
                nameUsed = true;
                break;
            }
        }

        //Exit progrmm
        if(function.compare(chUserName, (char*)"exit") == true)
            return false;

        //Name not used -> create user
        if(nameUsed == false)
        {
            //Ask whether user name is corret
            std::cout << "Register as " << chUserName << "?\n";
            std::cout << "(Y)es/(N)o? ";
            std::string sInput;
            function.m_getline(sInput);
            char* chInput = (char*)sInput.c_str();
            
            //Username correct -> create user
            if(function.compare(chInput, (char*)"Y") == true || sInput.compare("y") == true)
            {
                //Create path to directory
                std::string sPath = "mkdir -p users/";
                sPath.append(sUserName);
                sPath.append("/");
                
                //Create directory
                const int dir_err = system(sPath.c_str());
                if(-1 == dir_err)
                {
                    std::cout << "Error creating directory!\n";
                    exit(1);
                    return false;
                }
                
                //Create user
                m_user = new CUser(chUserName);
                std::cout << chUserName << " created succsessfully!\n";
                return true;
            }

            //Username incorrect -> return to beginning of loop & information about exiting programm
            else
                std::cout << "Try again. To exit programm enter \"exit\"\n";
        }

        //Name already user -> return to beginning of loop (user input)
        else
        {
            std::cout << "Name already used. Try again with a different name.\n";
            std::cout << "to exit programm enter: \"exit\"\n";
        }
    } 
}

/** 
* loginUser: user logs in with his or her user name (later password)
**/
bool CMinicrypto::loginUser()
{
    std::cout << "In login user...\n";

    //Variables
    CFunctions function;
        bool userExists = false;

    for(;;)
    {
        std::string sUserName;
        std::cout << "User name (no space): ";
        function.m_getline(sUserName);
        char* chUserName = (char*)sUserName.c_str();

        if(function.compare(chUserName, (char*)"exit"))
            return false;

        DIR *dir_allUsers;
        struct dirent* e_user;

        dir_allUsers = opendir("users");
        if(!dir_allUsers)
        {
            std::cout << "Fatal error! Dictionary not found!\n";
            return false;
        }

        while((e_user = readdir(dir_allUsers)) != NULL)
        {
            std::string sCurUser = e_user->d_name;
            if(function.compare(chUserName, (char*)sCurUser.c_str()))
            {
                m_user = new CUser(chUserName);
                return true;
            }
        }

        if(userExists == false)
            std::cout << "User name does not exist. Enter \"exit\" to quit programm.\n";

    }while(userExists == false);
}

/**
* programmRunning: main loop of the programm, user can decrypt or encrypt messages
* add friends, view friend details or edit friend list
**/
void CMinicrypto::programmRunning()
{
    //Variables
    CFunctions function;
    std::string sInput;
    char chInput[128];

    do
    {
        std::cout << "--- MINI CRYPTO --- (logged in as " << m_user->getName() << ")\n";
        std::cout << "1. Encrypt message \n";
        std::cout << "2. Decrypt message \n";
        std::cout << "3. Add friend      \n";
        std::cout << "4. Delete friend   \n";
        std::cout << "5. Change key      \n";
        std::cout << "6. Show friends    \n";
        std::cout << "7. Show friends key\n";
        std::cout << "8. Log out         \n";
        std::cout << "> ";

        function.m_getline(sInput);
        function.allocate(chInput, (char*)sInput.c_str());

        //Encrypt message
        if(function.compare(chInput, (char*)"1"))
        { 
            m_user->encryptMessage();
            std::cout << endl;
        }
    
        //Decrpt message
        else if(function.compare(chInput, (char*)"2"))
        {
            m_user->decryptMessage();
            std::cout << endl;
        }

        //Add friend
        else if(function.compare(chInput, (char*)"3"))
        {
            m_user->addFriend();
            std::cout << endl;
        }

        //Delete friend
        else if(function.compare(chInput, (char*)"4"))
        {
            m_user->deleteFriend();
            std::cout << "\n";
        }

        //Change key of a friend
        else if(function.compare(chInput, (char*)"5"))
        {
            m_user->changeKey();
            std::cout << "\n";
        }

        //Show all friends
        else if(function.compare(chInput, (char*)"6"))
        {
            m_user->showFriends();
            std::cout << endl;
        }

        //Show key
        else if(function.compare(chInput, (char*)"7"))
        {
            m_user->showKey();
            std::cout << endl;
        }

        //Close programm
        else if(function.compare(chInput, (char*)"8"))
                std::cout << "Logging out...\n";

        //Wrong input
        else
            std::cout << "Worng input! \n\n";

    }while(function.compare(chInput, (char*)"8") == false);

    //Safe friends list
    m_user->safe();
}
   
        
