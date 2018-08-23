#include "CMinicrypto.h"

using namespace std;

/**
* programmStart: user can decide between login or register as a new user
* function then calls login/ register and afterwards goes into programmRunning
*/
void CMinicrypto::programmStart() 
{
    //Variables
    CFunctions function;

    for(;;)
    {
        char chWahl;
        cout << "--- Minicrypto --- \n";
        cout << "1. Register        \n";
        cout << "2. Login           \n";
        cout << "3. Leave           \n";
        cout << "> "; cin >> chWahl;

        if(chWahl == '1')
        {
            if(registerUser() == false)
            {
                cout << "Programm closed due to error. We're sorry. \n";
                return;
            }
            break;
        }
        else if(chWahl == '2')
        {
            if(loginUser() == false)
            {
                cout << "Programm closed due ti error. We're sorry. \n";
                return;
            }
            break;
        }

        else if(chWahl == '3')
        {
            cout << "Closing programm...\n";
            return; 
        }

        else
            cout << "Wrong input!\n";

        cout << "\n";
    } 

    programmRunning();

    //Save user | safe friends names and keys in a .txt file
    m_user->safe();
}

/**
* registerUser: register a new user
**/
bool CMinicrypto::registerUser()
{
    //Variables
    CFunctions function;
    DIR *dir_allUsers;
    struct dirent* e_user;

    dir_allUsers = opendir("/home/leonce/MiniCrypto");
    if(!dir_allUsers)
    {
        cout << "Fatal error! Dictionary not found!\n";
        return false;
    }

    for(;;)
    {
        //User input: user name
        cout << "User name: ";
        string sUserName;
        function.m_getline(sUserName);
        char* chUserName = (char*)sUserName.c_str();
        
        bool nameUsed = false;
        while((e_user = readdir(dir_allUsers)) != NULL)
        {
            string sCurUser = e_user->d_name;
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
            cout << "Register as " << chUserName << "?\n";
            cout << "(Y)es/(N)o? ";
            string sInput;
            function.m_getline(sInput);
            char* chInput = (char*)sInput.c_str();
            
            //Username correct -> create user
            if(function.compare(chInput, (char*)"Y") == true || sInput.compare("y") == true)
            {
                //Create path to directory
                string sPath = "mkdir -p home/leonce/Minicrypto/";
                sPath.append(sUserName);
                sPath.append("/");
                
                //Create directory
                const int dir_err = system(sPath.c_str());
                if(-1 == dir_err)
                {
                    cout << "Error creating directory!\n";
                    exit(1);
                    return false;
                }
                
                //Create user
                m_user = new CUser(chUserName);
                cout << chUserName << " created succsessfully!\n";
                return true;
            }

            //Username incorrect -> return to beginning of loop & information about exiting programm
            else
                cout << "Try again. To exit programm enter \"exit\"\n";
        }

        //Name already user -> return to beginning of loop (user input)
        else
        {
            cout << "Name already used. Try again with a different name.\n";
            cout << "to exit programm enter: \"exit\"\n";
        }
    } 
}

/** 
* loginUser: user logs in with his or her user name (later password)
**/
bool CMinicrypto::loginUser()
{
    cout << "In login user...\n";

    //Variables
    CFunctions function;
        bool userExists = false;
    for(;;)
    {
        string sUserName;
        cout << "User name: ";
        function.m_getline(sUserName);
        char* chUserName = (char*)sUserName.c_str();

        if(function.compare(chUserName, (char*)"exit"))
            return false;

        DIR *dir_allUsers;
        struct dirent* e_user;

        dir_allUsers = opendir("/home/leonce/MiniCrypto");
        if(!dir_allUsers)
        {
            cout << "Fatal error! Dictionary not found!\n";
            return false;
        }

        while((e_user = readdir(dir_allUsers)) != NULL)
        {
            string sCurUser = e_user->d_name;
            if(function.compare(chUserName, (char*)sCurUser.c_str()))
            {
                m_user = new CUser(chUserName);
                return true;
            }
        }

        if(userExists == false)
            cout << "User name does not exist. Enter \"exit\" to quit programm.\n";

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
    string sInput;
    char chInput[128];

    do
    {
        cout << "--- MINI CRYPTO --- (logged in as " << m_user->getName() << ")\n";
        cout << "1. Encrypt message \n";
        cout << "2. Decrypt message \n";
        cout << "3. Add friend      \n";
        cout << "4. Delete friend   \n";
        cout << "5. Show friends    \n";
        cout << "6. Show friends key\n";
        cout << "7. Leeve programm  \n";
        cout << "> ";

        function.m_getline(sInput);
        function.allocate(chInput, (char*)sInput.c_str());

        //Encrypt message
        if(function.compare(chInput, (char*)"1"))
        { 
            m_user->encryptMessage();
            cout << endl;
        }
    
        //Decrpt message
        else if(function.compare(chInput, (char*)"2"))
        {
            m_user->decryptMessage();
            cout << endl;
        }

        //Add friend
        else if(function.compare(chInput, (char*)"3"))
        {
            m_user->addFriend();
            cout << endl;
        }

        //Delete friend
        else if(function.compare(chInput, (char*)"4"))
        {
            m_user->deleteFriend();
            cout << "\n";
        }

        //Show all friends
        else if(function.compare(chInput, (char*)"5"))
        {
            m_user->showFriends();
            cout << endl;
        }

        //Show key
        else if(function.compare(chInput, (char*)"6"))
        {
            m_user->showKey();
            cout << endl;
        }

        //Close programm
        else if(function.compare(chInput, (char*)"7"))
                cout << "Programm closing...\n\n";

        //Wrong input
        else
            cout << "Worng input! \n\n";

    }while(function.compare(chInput, (char*)"7") == false);
}

   
     
    
    
    
