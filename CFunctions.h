//CFunction (header)
//Contains various functions, that might come in handy

#ifndef CFUNCTIONS
#define CFUNCTIONS


#include <iostream>
#include <math.h>
#include <string.h>
#include <string>

using namespace std;


//Fuctions
//Provides simple selfwrote functions
class CFunctions
{
public:
	void allocate(char *chText1, char *chText2);
	bool compare(char *chText1, char *chText);
    bool contains(char* chText, char* chContains);
	void clearMemory(char *chVar);
	char* createSpace(char *chText);
	char* convertIntChar(int y, int x);
    int charToInt(char* chInput);

    void m_getline(std::string &var);
	bool checkField(int ymax, int xmax, int y, int x);
};

#endif
