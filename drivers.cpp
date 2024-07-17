/* Main.cpp
REVISION HISTORY:
Rev. 1 - 24/07/04 Original by Sanchit Jain
----------------------------------------------------------------------*/
#include <iostream>
#include <fstream>
#include <cstdlib> //for exit() function.
#include <string>

using namespace std;

template <class T>
T* readFile(const string &filename, streampos fileptr){
    int length = f.tell(g);
    fstream f("data/"+filename, ios::in);
    int length = f.tellg();
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


/*
Reads data of type 'T' from a specified file starting at a given position, 
returning a dynamically allocated array of the read data and resetting the file pointer to the beginning.
Uses the unsorted records data structure to read the file.
--------------------------------------------------------------------*/
template <class T>
T readRecord(const string &filename, streampos &fileptr)
{
    fstream f("data/"+filename, ios::in);
    if (!f.good())
        exit(1);
    f.seekg(fileptr);
    T data;
    f.read(reinterpret_cast<char *>(&data), sizeof(data));
    cout << "Data from file " << filename << " was " << data << endl;
    return data;
}

/*
Reads a single record of type 'T' from a specified file at a given position and outputs it to the console and returns it.
Uses the unsorted records data structure to read the records.
--------------------------------------------------------------------*/
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

/*
Writes a single record of type 'T' to a specified file at a given position and updating the file pointer after writing.
Uses the unsorted records data structure to write the records.
--------------------------------------------------------------------*/
template <class T, class Q>
void updateRecord(const string &filename, streampos fileptr, const T &newRecord, const Q *id)
{
    // work in progress
    fstream f("data/" + filename, ios::in || ios::out);
    if (!f.good())
        exit(1);
    T record;
    Q recordId;
    while (f.read(reinterpret_cast<char *>(&record), sizeof(T))){
        recordID = extractID(record);
        if (recordID == id){
            fileptr = file.tellg() - streampos(sizeof(T));
            f.seekp(fileptr);
            f.write(reinterpret_cast<const char *>(&newRecord), sizeof(T));
        }
        break;
    }
    f.flush();
    f.close();
}

/*
Updates a single record of type 'T' in a file by replacing record with matching ID with a new record.
Uses the unsorted records data structure to update the records.
--------------------------------------------------------------------*/
template <typename T, typename Q>
void deleteRecord(const string &filename, streampos fileptr, const Q *id){
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
    bool dound = true;
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
        if (remove((("data/"+filename).c_str()) != 0){
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
Deletes a record of type 'T' in a file by removing entries with matching ID and replacing it with a temp file containing remaining records.
Uses the unsorted records data structure to delete a record.
--------------------------------------------------------------------*/
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
Writes a record of type 'T' to a specified file starting at a given position and updates the file pointer afer writing.
Uses the unsorted records data structure to write a file.
--------------------------------------------------------------------*/