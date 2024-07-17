#ifndef GLOBALS_HPP
#define GLOBALS_HPP

/* Globals.hpp
REVISION HISTORY:
Rev. 1 - 24/07/03 Original by Sanchit Jain
----------------------------------------------------------------------
This module, Gloabls.hpp, hides the implementation of function and variables global to the entire system. 
Gloabls.hpp keeps its high cohesion by encapsulating all possible global variables and functions.
----------------------------------------------------------------------*/
#include <fstream>
#include <string>

using namespace std;
/*----------------------------------------------------------------------
Exported constants/types/variables
Constants:
    - DIRECTORY
    - NUMBER_OF_FILES
    - FILENAMES
Types:
    - streampos objects: CUSTOMERFILEPOINTER, CHANGEFILEPOINTER, COMPLAINTFILEPOINTER, PRODUCTFILEPOINTER
Functions:
    - T IDGenerator(const string &type, const int &precision)
----------------------------------------------------------------------*/
extern streampos CUSTOMERFILEPOINTER;   //  fstream file pointer for "Customers.bin" 
extern streampos CHANGEFILEPOINTER;     //  fstream file pointer for "Changes.bin"
extern streampos COMPLAINTFILEPOINTER;  //  fstream file pointer for "Complaints.bin"
extern streampos PRODUCTFILEPOINTER;    //  fstream file pointer for "Products.bin"
// ----------------------------------------------------------------------
#define DIRECTORY "data/"   // Directory where binary files will be stored
#define NUMBER_OF_FILES 4   // Number of binary files
// ----------------------------------------------------------------------
const string FILENAMES[NUMBER_OF_FILES] = 
{
        "Customers.bin",
        "Changes.bin",
        "Complaints.bin",
        "Products.bin"
};  // Array with names of binary files
// ----------------------------------------------------------------------
char *IDGenerator(
    const char &type,     // in
                            // type of entity that wants the ID (Product, Complaint, Customer, Change)
    const int &precision    // in
                            // Number of digits or characters in the ID
);
/* T IDGenerator(const string &type, const int &precision) generates a random ID for the entity that is passed in type parameter as string. The function returns a template value. It fails if type is null and/or precision is 0.
----------------------------------------------------------------------*/
void safeStrCopy(char* dest, const char* src, size_t maxLen);
#endif