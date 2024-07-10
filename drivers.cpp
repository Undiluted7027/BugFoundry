#include <iostream>
#include <fstream>
#include <cstdlib> //for exit() function.
#include <string>
#include "Globals.cpp"
#include "Record.hpp"
#include "Customer.hpp"
using namespace std;

template <class T>
Record<T> readFile(const string &filename, const streampos &fileptr){
    fstream f("data/"+filename, ios::in);
    if (!f.good())
        exit(1);
    f.seekg(fileptr);
    Record<T> data;
    while(f.read(reinterpret_cast<char *>(&data), sizeof data)){
        cout << "Data read from file " << filename << " was " << data << endl;
    }
    f.close();
    return data;
}

template <typename T>
void writeFile(const string &filename, streampos &fileptr, const Record<T> &record){
    fstream f("data/"+filename, ios::out);
    if (!f.good())
        exit(1);
    f.seekp(fileptr);
    
    f.write(reinterpret_cast<char *>(&record), sizeof record);
    
    f.flush();
    fileptr = f.tellp(); // comment this for the test to work
    // cout << fileptr << endl;
    f.seekp(0);
    f.close();
}


