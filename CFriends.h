#pragma once 

#include <iostream>
#include "CFunctions.h"

class CFriend
{
    private:
        char m_chName[128];
        char m_chKey[5000];
    public:
        CFriend(char* chName, char* chKey) {
            CFunctions F;
            F.allocate(m_chName, chName);
            F.allocate(m_chKey, chKey);
        }

        char* getName() {
            return m_chName;
        }
        char* getKey() {
            return m_chKey;
        }

        void setKey(char* chKey) {
            CFunctions functions;
            functions.allocate(m_chKey, chKey);
        }
};
