#ifndef DRIVERS_HPP
#define DRIVERS_HPP

#include <iostream>
#include <fstream>
#include <string>
#include "drivers.cpp"
using namespace std;

// Template function to read data from a file into an array
template <class T>
T* readFile(const string &filename, streampos fileptr);

// Template function to read a single record from a file
template <class T>
T readRecord(const string &filename, streampos fileptr);

// Template function to write a single record to a file
template <class T>
void writeRecord(const string &filename, streampos &fileptr, const T &record);

// Template function to update a record in a file
template <class T, class Q>
void updateRecord(const string &filename, streampos fileptr, const T &newRecord, const Q *id);

// Template function to delete a record from a file
template <typename T, typename Q>
void deleteRecord(const string &filename, streampos fileptr, const Q *id);

// Template function to write an array of records to a file
template <typename T>
void writeFile(const string &filename, streampos &fileptr, const T* &records);

size_t getFileSize(const string& filename);
template <typename T>
void printRecords(T* arr, const int &size);

#endif // DRIVERS_HPP
