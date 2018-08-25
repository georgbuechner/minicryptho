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
    
    
    
        
