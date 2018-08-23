#include "CFriends.h"

CFriend::CFriend(char* chName, char* chKey)
{
    CFunctions F;
    F.allocate(m_chName, chName);
    F.allocate(m_chKey, chKey);
}
