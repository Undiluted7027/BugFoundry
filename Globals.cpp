/* Globals.cpp
REVISION HISTORY:
Rev. 1 - 24/07/03 Original by Sanchit Jain
----------------------------------------------------------------------*/
#include "Globals.hpp"
#include <ctime>
#include <fstream>
#include <cstring>
#include <cstdlib>

streampos CUSTOMERFILEPOINTER = 0;
streampos COMPLAINTFILEPOINTER = 0;
streampos CHANGEFILEPOINTER = 0;
streampos PRODUCTFILEPOINTER = 0;

char* IDGenerator(const char &type, const int &precision){
    srand(static_cast<unsigned int>(time(nullptr)));
    char* id = new char[precision + 1];
    switch(type){
        case '2':
            id[0] = '0';
            for (int i = 1; i < precision; i++)
                id[i] = '0' + (rand() % 10);;
            break;
        case '3':
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

void copyString(char *&dest, const char *src, size_t length = 0)
{
    if (src)
    {
        size_t srcLength = strlen(src);
        dest = new char[length];
        strncpy(dest, src, length);  // Copy up to 'length' characters
        dest[length] = '\0';         // Ensure null termination
        if (srcLength < length)
        {
            // Fill the remaining space with null characters
            memset(dest + srcLength, '\0', length - srcLength);
        }
    }
    else
    {
        dest = new char[length + 1];
        memset(dest, '\0', length + 1);  // Fill entire buffer with null characters
    }
}