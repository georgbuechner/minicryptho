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
    CUser* m_user;

public:
    void programmStart();
    bool registerUser();
    bool loginUser();
    void programmRunning();
};
    
    
    
        
