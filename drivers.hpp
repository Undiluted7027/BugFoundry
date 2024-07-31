#ifndef DRIVERS_HPP
#define DRIVERS_HPP

/* drivers.hpp
REVISION HISTORY:
Rev. 1 - 24/07/04 Original by Sanchit Jain
-----------------------------------------------------------------------
This module, drivers.hpp, hides the implementation of drivers module.
drivers.hpp keeps its high cohesion by encapsulating all possible drivers usage in the system.
----------------------------------------------------------------------*/
#include <iostream>
#include <fstream>
#include <string>
#include "drivers.cpp"
using namespace std;

template <class T>
T* readFile(
    const string &filename,     // in: the file to open
    streampos fileptr           // in out: the location in the file
);
/*
readFile is used to read the file content of any type 
in the file called filename at its location specified by the fileptr and
fill them into an array.
----------------------------------------------------------------------*/
template <class T>
T readRecord(
    const string &filename,     // in: the file to open
    streampos fileptr           // in out: the location in the file
);
/*
readRecord is used read the Reord content of any type 
in the file called filename at its location specified by the fileptr and
retrieve a single Record.
----------------------------------------------------------------------*/
template <class T>
void writeRecord(
    const string &filename,     // in: the file to open
    streampos &fileptr,         // in out: the location in the file
    const T &record             // in: the record to be written in the file
);
/*
writeRecord takes any type of record and write it into the file called filename
at the location specified by fileptr
----------------------------------------------------------------------*/
// Template function to update a record in a file
template <class T, class Q>
void updateRecord(
    const string &filename,     // in: the file to open
    streampos fileptr,          // in out: the location in the file
    const T &newRecord,         // in: the newrecord to be used in updating
    const Q *id                 // in: the id to get updated
);
/*
updateRecord updates a record with id in a file with the newRecord object
----------------------------------------------------------------------*/
// Template function to delete a record from a file
template <typename T, typename Q>
void deleteRecord(
    const string &filename,     // in: the file to open
    streampos fileptr,          // in out: the location in the file
    const Q *id                 // in out: the record to be deleted
);
/*
deleteRecord deletes a record in a file specified with its id
----------------------------------------------------------------------*/
// Template function to write an array of records to a file
template <typename T>
void writeFile(
    const string &filename,     // in: the file to open
    streampos &fileptr,         // in out: the location in the file
    const T* &records           // in: the record to write 
);
/*
writeFile writes an array of records to a file called filename
----------------------------------------------------------------------*/
size_t getFileSize(
    const string& filename      // in: the file to measure the size
);
/*
getFileSize returns a size of file called filename
----------------------------------------------------------------------*/
template <typename T>
void printRecords(
    T* arr,             // in: the array of records
    const int &size     // in: the size of the record type that the array is holding
);
/*
printRecords displays the records provided by an array called arr
----------------------------------------------------------------------*/
#endif // DRIVERS_HPP
