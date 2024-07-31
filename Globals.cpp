/* Globals.cpp
REVISION HISTORY:
Rev. 1 - 24/07/03 Original by Sanchit Jain
----------------------------------------------------------------------*/
#include "Globals.hpp"
#include <ctime>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include "Exceptions.hpp"

streampos CUSTOMERFILEPOINTER = 0;
streampos COMPLAINTFILEPOINTER = 0;
streampos CHANGEFILEPOINTER = 0;
streampos PRODUCTFILEPOINTER = 0;

int GetRecordCount(const std::string &FILENAME)
{
    std::ifstream file(FILENAME, std::ios::binary);
    if (!file)
    {
        throw FileException("Could not open file 'Products.bin' for reading.");
    }

    int recordCount;
    file.read(reinterpret_cast<char*>(&recordCount), sizeof(int));
    file.close();

    return recordCount;
}

char* IDGenerator(const char &type, const std::string &FILENAME, int precision) {
    if (precision < 4) {
        throw std::invalid_argument("Precision must be at least 4.");
    }

    // Function to get the record count, ensure this is implemented elsewhere
    int recordCount = GetRecordCount(FILENAME);
    std::cout << recordCount << std::endl;

    // Determine the number of leading characters based on the type
    int leadingChars = 0;
    std::string leadingStr;
    switch (type) {
        case '1': // Example: 'ch' (2 characters)
            leadingChars = 2;
            leadingStr = "ch";
            break;
        case '2': // Example: 'co' (2 characters)
            leadingChars = 2;
            leadingStr = "co";
            break;
        default:
            leadingChars = 0;
            leadingStr = "";
    }

    // Ensure precision accommodates the leading characters and the number itself
    if (precision <= leadingChars) {
        throw std::invalid_argument("Precision must be greater than the number of leading characters.");
    }

    // Calculate the starting number
    int numberPrecision = precision - leadingChars;
    int startNumber = 1;
    for (int i = 0; i < numberPrecision - 1; ++i) {
        startNumber *= 10;
    }

    // Generate the ID number
    int idNumber = startNumber + recordCount;

    // Convert idNumber to string with leading zeros if necessary
    std::ostringstream idNumberStream;
    // idNumberStream.fill('0');
    idNumberStream.width(numberPrecision);
    idNumberStream << idNumber;
    std::string idNumberStr = idNumberStream.str();

    // Allocate memory for the ID
    char* id = new char[precision];

    // Copy leading characters if any
    std::copy(leadingStr.begin(), leadingStr.end(), id);

    // Copy the ID number part
    std::copy(idNumberStr.begin(), idNumberStr.end(), id + leadingChars);
    cout << id << endl;
    // Null-terminate the string
    id[precision] = '\0';

    return id;
}
/*
Generates a random ID of a specific length based on a type character, intializing the ID with a leading digit 
depending on the type and filling the rest with random digits.
--------------------------------------------------------------------*/
void safeStrCopy(char* dest, const char* src, size_t maxLen) {
    std::strncpy(dest, src, maxLen-1);
    dest[maxLen] = '\0';
}
