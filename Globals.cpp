// Globals.cpp
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
                id[i] = rand()%10;
            break;
        case '3':
            id[0] = '1';
            for (int i = 1; i < precision; i++)
                id[i] = rand()%10;
            break;
        default:
            for (int i = 0; i < precision; i++)
                id[i] = rand()%10;
    }
    return id;
}