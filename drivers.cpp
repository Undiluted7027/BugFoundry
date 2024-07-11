#include <iostream>
#include <fstream>
#include <cstdlib> //for exit() function.
#include <string>
#include "Globals.cpp"
#include "Record.hpp"
#include "Customer.hpp"
using namespace std;

template <class T>
T* readFile(const string &filename, streampos fileptr){
    int length = f.tell(g);
    fstream f("data/"+filename, ios::in);
    if (!f.good())
        exit(1);
    f.seekg(fileptr);
    T* dataptr = new T[length];
    T data;
    int i = 0;
    while(f.read(reinterpret_cast<char *>(&data), sizeof data)){
        cout << "Data read from file " << filename << " was " << data << endl;
        dataptr[i] = data;
        i++;
    }
    fileptr = 0;
    f.seekg(fileptr);
    f.close();
    return dataptr;
}

template <class T>
T readRecord(const string &filename, streampos &fileptr){
    fstream f("data/"+filename, ios::in);
    if (!f.good())
        exit(1);
    f.seekg(fileptr);
    T data;
    f.read(reinterpret_cast<char *>(&data), sizeof data);
    cout << "Data from file " << filename << " was " << data << end;
}

template <class T>
void writeRecord(const string &filename, streampos &fileptr, const T &record){
    fstream f("data/"+filename, ios::out);
    if (!f.good())
        exit(1);
    f.seekp(fileptr);
    f.write(reinterpret_cast<char *> (&record), sizeof record);
    f.flush();
    fileptr = f.tellp();
    f.close();
}

template <typename T>
void writeFile(const string &filename, streampos &fileptr, const T* &records){
    fstream f("data/"+filename, ios::out);
    if (!f.good())
        exit(1);
    f.seekp(fileptr);
    size_t size = sizeof(records)/sizeof(records[0]);
    for (int i = 0; i < size; i++)
        f.write(reinterpret_cast<char *>(&records[i]), sizeof records[i]);
    f.flush();
    fileptr = 0; // comment this for the test to work
    // cout << fileptr << endl;
    f.seekp(fileptr);
    f.close();
}


