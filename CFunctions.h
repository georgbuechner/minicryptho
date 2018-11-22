//CFunction (header)
//Contains various functions, that might come in handy

#pragma once

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


//Funktion: allocate 
//Aufgabe: T1 mit T2 füllen
void CFunctions::allocate(char* chT1, char* chT2)
{
	for (unsigned int i = 0; i<strlen(chT2) + 1; i++)
		chT1[i] = chT2[i];
}


//Funktion: Compare
//Aufgabe: Zwei Strings vergleichen
bool CFunctions::compare(char* chT1, char* chT2)
{
	if (strlen(chT1) != strlen(chT2))
		return false;

	for (unsigned int i = 0; i<strlen(chT1); i++)
	{
		if (chT1[i] != chT2[i])
			return false;
	}

	return true;
}

//contains:
//Functions: checks, whether string1 conains sring two
bool CFunctions::contains(char* chText, char* chContains)
{
    for(unsigned int i=0; i<strlen(chText); i++)
    {
        unsigned int counter = 0;

        for(unsigned int j=0; j<strlen(chContains); j++)
        {
    
            if(chText[i+j] == chContains[j])
            {
                counter++;
                if(counter == strlen(chContains)-1)
                    return true;
            }

            else
                break;
        }
    }    

    return false;
}

//Funktion: ClearMemory
//Aufgabe: Einen String leeren
void CFunctions::clearMemory(char* chT)
{
	for (unsigned int i = 0; i<sizeof(chT); i++)
		chT[i] = '\0';
}

//m_getline: custom keyboard input for strings
void CFunctions::m_getline(std::string &var)
{
    for(;;)
    {
        std::cout.flush();
        getline(cin, var);
        if(var!="")
            break;
    }
}

/**
* charToInt: convert char* to int. return -1 if input is not a number
* @parameter char* (input as char array)
* @return int (return integer. Return -1 if input is not a number)
**/
int CFunctions::charToInt(char* chInput)
{
    int num = 0;
    std::cout << strlen(chInput) << "\n";
    for(unsigned int i=0; i<strlen(chInput); i++)
    {
        int elem = (int)chInput[i] -48;

        if(elem >= 0 && elem <= 9)
            num += elem*pow((double)10, (double)strlen(chInput)-1-i);
        else
            return -1;
    }

    return num;
} 
        
        

//Functions: checkField
//Check if the outlines of the Field are reached
bool CFunctions::checkField(int ymax, int xmax, int y, int x)
{

	if (y > ymax || y < 0)
		return false;
	else if (x > xmax || x < 0)
		return false;
	else
		return true;
}
