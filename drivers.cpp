#include <iostream>
#include <fstream>
#include <cstdlib> //for exit() function.
#include <string>
#include "Globals.cpp"
using namespace std;


void readFile(const string &filename, const streampos &fileptr){
    fstream f("data/"+filename, ios::in);
    if (!f.good())
        exit(1);
    f.seekg(fileptr);
    char data;
    while(f.read(reinterpret_cast<char *>(&data), sizeof data)){
        cout << "Data read from file " << filename << " was " << data << endl;
    }
    f.close();
}

void writeFile(const string &filename, streampos &fileptr){
    char myString[5] = {'a', 'b', 'c', 'd', '\0'}; // data
    fstream f("data/"+filename, ios::out);
    if (!f.good())
        exit(1);
    f.seekp(fileptr);
    for (int i = 0; i <= 5; i++){
        f.write(reinterpret_cast<char *>(&myString[i]), sizeof myString[i]);
    }
    f.flush();
    fileptr = f.tellp(); // comment this for the test to work
    // cout << fileptr << endl;
    f.seekp(0);
    f.close();
}


int main()
{
    // streampos fileptr = 2;
    const string filename = "Customers.bin";
    
    for (int i = 0; i < 2; i++){
        if (i == 0){
            writeFile(filename, CUSTOMERFILEPOINTER);
        }
        else{
            readFile(filename, CUSTOMERFILEPOINTER);
        }
    }
            

    return 0;
}
