#pragma once 

#include <iostream>
#include "CFunctions.h"

class CFriend
{
    private:
        char m_chName[128];
        char m_chKey[128];
    public:
        CFriend(char* chName, char* chKey);
        char* getName() {
            return m_chName;
        }
        char* getKey() {
            return m_chKey;
        }
};
