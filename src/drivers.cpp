/* Main.cpp
REVISION HISTORY:
Rev. 1 - 24/07/04 Original by Sanchit Jain
----------------------------------------------------------------------*/
#include <iostream>
#include <fstream>
#include <cstdlib> //for exit() function.
#include <string>
#include <vector>

using namespace std;

/*
Reads all record from a file
----------------------------------------------------------------------------------*/
template <class T>
T* readFile(const string &filename, streampos fileptr)
{
    fstream f("data/"+filename, ios::in);
    int length = f.tellg();
    if (!f.good())
        exit(1);
    f.seekg(fileptr);
    T* dataptr = new T[length];
    cout << length << endl;
    T data;
    int i = 0;
    while(i != length && f.read(reinterpret_cast<char *>(&data), sizeof data))
    {
        cout << "Data read from file " << filename << " was: " << endl;
        cout << data << endl;
        dataptr[i] = data;
        i++;
    }
    fileptr = 0;
    f.seekg(fileptr);
    f.close();
    return dataptr;
}

/*
Reads and return a record from a file
----------------------------------------------------------------------------------*/
template <typename T>
T readRecord(const string &filename, streampos fileptr) 
{
    ifstream f("data/" + filename, ios::in | ios::binary);
    if (!f) {
        cerr << "Error opening file!" << endl;
        exit(1);
    }

    // Seek to the specified position
    f.seekg(fileptr);

    // Read data into T
    T data;
    f.read(reinterpret_cast<char*>(&data), sizeof(T));

    // Check for read errors
    if (!f) {
        cerr << "Error reading from file!" << endl;
        exit(1);
    }

    // Close the file
    f.close();

    cout << "Read data: " << data << endl;

    return data;
}

/*
Writes a record to a file
----------------------------------------------------------------------------------*/
template <typename T>
void writeRecord(const string &filename, streampos &fileptr, T record) {
    ofstream f("data/" + filename, ios::out | ios::binary);
    if (!f) {
        cerr << "Error opening file!" << endl;
        exit(1);
    }

    // Seek to the specified position
    f.seekp(fileptr);

    // Write record data
    f.write(reinterpret_cast<const char*>(&record), sizeof(T));

    // Check for write errors
    if (!f) {
        cerr << "Error writing to file!" << endl;
        exit(1);
    }

    // Flush and close the file
    f.flush();
    f.close();
}

/*
Updates information of a record with a specific id 
----------------------------------------------------------------------------------*/
template <class T>
void updateRecord(const string &filename, streampos fileptr, const T newRecord, const char *id)
{
    // work in progress
    fstream f("data/" + filename, ios::in || ios::out);
    if (!f.good())
        exit(1);
    T record;
    char *recordID;
    while (f.read(reinterpret_cast<char *>(&record), sizeof(T))){
        recordID = extractID(record);
        if (recordID == id){
            fileptr = f.tellg() - streampos(sizeof(T));
            f.seekp(fileptr);
            f.write(reinterpret_cast<const char *>(&newRecord), sizeof(T));
        }
        break;
    }
    f.flush();
    f.close();
}

/*
Deletes a record with a specific id from a file
----------------------------------------------------------------------------------*/
template <typename T, typename Q>
void deleteRecord(const string &filename, streampos fileptr, const Q *id){
    string fpath = "data/" + filename;
    fstream f("data/" + filename, ios::in || ios::out);
    fstream temp("data/temp_"+filename, ios::in||ios::out);
    if (!temp.is_open())
    {
        cerr << "Error opening file: " << filename << endl;
        exit(1);
    }
    if (!f.good())
        exit(1);
    T record;
    Q recordID;
    bool found = true;
    while (f.read(reinterpret_cast<char *>(&record), sizeof(T))){
        recordID = extractID(record);
        if (recordID == id)
            found = true;
        else
            temp.write(reinterpret_cast<const char*>(&record), sizeof(T));
    }
    temp.flush();
    f.close();
    temp.close();
    if (found){
        if (remove(fpath.c_str()) != 0){
            cerr << "Error deleting original file" << endl;
            exit(1);
        }
        if (rename(("data/temp_" + filename).c_str(), ("data/" + filename).c_str()) != 0) 
        {
            cerr << "Error renaming temporary file." << std::endl;
            exit(1);
        }
    } 
    else 
    {
        // If the record was not found, delete the temporary file
        remove(("data/temp_" + filename).c_str());
        cerr << "Record not found." << endl;
    }
}

/*
Write a record to a file
----------------------------------------------------------------------------------*/
template <typename T>
void writeFile(const string &filename, streampos &fileptr, const T* &records)
{
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

/*
Gets the file size
----------------------------------------------------------------------------------*/
size_t getFileSize(const string& filename) {
    fstream file(filename, ios::in|ios::ate);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return 0;
    }
    size_t fileSize = file.tellg();
    file.seekg(0, ios::beg);
    file.close();
    return fileSize;
}

/*
Displays a record file
----------------------------------------------------------------------------------*/
template <typename T>
void printRecords(T* arr, const int &size){
    for (int i = 0; i < size; i++)
        cout << arr[i] << endl;
}   