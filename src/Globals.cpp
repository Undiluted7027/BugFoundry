/* Globals.cpp
REVISION HISTORY:
Rev. 1 - 24/07/03 Original by Sanchit Jain
----------------------------------------------------------------------*/

#include <ctime>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include "Exceptions.hpp"

#include "../include/Globals.hpp"

//--------------------------------------------------------------------

streampos CUSTOMERFILEPOINTER = 0;
streampos COMPLAINTFILEPOINTER = 0;
streampos CHANGEFILEPOINTER = 0;
streampos PRODUCTFILEPOINTER = 0;

//--------------------------------------------------------------------

/*
Generates a random ID of a specific length based on a type character, intializing the ID with a leading digit 
depending on the type and filling the rest with random digits.
--------------------------------------------------------------------*/
char* IDGenerator(const char &type, const int &precision)
{
    srand(static_cast<unsigned int>(time(nullptr)));
    char* id = new char[precision + 1];
    switch (type) { 
        case '2':
            id[0] = '0';
            for (int i = 1; i < precision; i++)
                id[i] = '0' + (rand() % 10);;
            break;
        case '3': // Example: 'co' (2 characters)
            id[0] = '1';
            for (int i = 1; i < precision; i++)
                id[i] = '0' + (rand() % 10);;
            break;
        default:
            for (int i = 0; i < precision; i++)
                id[i] = '0' + (rand() % 10);;
    }
    id[precision] = '\0';
    return id;
}

/*
String copy function.
Includes a terminating character at the end of the string.
--------------------------------------------------------------------*/
void safeStrCopy(char* dest, const char* src, size_t maxLen) 
{
    std::strncpy(dest, src, maxLen - 1);
    dest[maxLen - 1] = '\0';
}
