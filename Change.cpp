/* Change.cpp
REVISION HISTORY:
Rev. 1 - 24/07/15 Original by Nicholas Susanto
----------------------------------------------------------------------
This CPP file called Changes.cpp handles the changes of the program.
--------------------------------------------------------------------*/

#include "Change.hpp"
#include "Globals.hpp"
#include "drivers.cpp"
#include<cstring>
#include<iostream>

using namespace std;

Change::Change(const char *description, const char &status, const char &priority, const char *releaseID, const char *lastUpdate, const char *changeID="", const char *productName){
    if (changeID == nullptr || changeID == ""){
        const char *generatedID = IDGenerator('1', 6); // idk what the type should be help me
        strcpy(this->changeID, generatedID);
    }
    else{
        strcpy(this->changeID, changeID);
    }
    this->changeID[sizeof(this->changeID)-1] = '\0';
    strcpy(this->description, description);
    this->description[sizeof(this->description) - 1] = '\0';

    this->status = status;
    this->priority = priority;
    
    strcpy(this->releaseID, releaseID);
    this->releaseID[sizeof(this->releaseID)-1] = '\0';

    strcpy(this->lastUpdate, lastUpdate);
    this->lastUpdate[sizeof(this->lastUpdate)-1] = '\0';

    strcpy(this->productName, productName);
    this->productName[sizeof(this->productName)-1] = '\0';
}

/*
Create Change object using attrbibutes provided. 
No noticeable algorithm or data structure used.
--------------------------------------------------------------------*/
bool Change::operator==(const Change &other) const{
    return (changeID == other.changeID || description == other.description);
}

/*
Checks if two Change objects are equal based on changeID or description. 
No noticeable algorithm or data structure used.
--------------------------------------------------------------------*/
void Change::UpdateChange(const char *changeID, const char *description, const char &status, const char &priority, const char *releaseID){

}

char *Change::getChangeID() const{
    return changeID;
}

/*
Get the changeID of a Change object.
No noticeable algorithm or data structure used.
--------------------------------------------------------------------*/
void Change::change_displayProductName() const{
    cout << productName;
}

/*
Print the productName of the Change object to the console.
No noticeable algorithm or data structure used.
--------------------------------------------------------------------*/
void Change::change_displayStatus() const{
    cout << status;
} 

/*
Print the status of the Change object to the console.
No noticeable algorithm or data structure used.
--------------------------------------------------------------------*/
void Change::change_displayPriority() const{
    cout << priority;
} 

/*
Print the priority of the Change object to the console.
No noticeable algorithm or data structure used.
--------------------------------------------------------------------*/
void Change::change_displayRelID() const{
    cout << releaseID;
} 

/*
Print the releaseID of the Change object to the console.
No noticeable algorithm or data structure used.
--------------------------------------------------------------------*/
void Change::DisplayDetails(ostream &out) const
{
    if (strlen(changeID) == 0 || strlen(description) == 0 || status == ' ' || priority == ' ' || strlen(releaseID) == 0)
        out << "Error in reading Complaint information. One or more attributes of complaint do not have value(s)" << endl;
        // RAISE ERROR
        // exit(1);
    else{
        cout.width(12); cout << left << productName;
        cout.width(32); cout << left << description;
        cout.width(10); cout << left << changeID;
        cout.width(12); cout << left << lastUpdate;
        cout.width(11); cout << left << status;
        cout.width(10); cout << left << priority;
        cout.width(9); cout << left << releaseID << endl;
    }
}

/*
Print the attribute details of the Change object to the console.
No noticeable algorithm or data structure used.
--------------------------------------------------------------------*/
int ValidateChange(const char *description, const char &status, const char &priority, const char *releaseID, const char *lastUpdate){
    if (strlen(description) > 30){
        return -1;
    }
    if (status != '-' || status != 'X' || status != 'P' || status != 'O'){
        return -1;
    }
    if (priority != '1' ||  priority != '2' ||  priority != '3' ||  priority != '4' ||  priority != '5'){
        return -1;
    }
    if (strlen(releaseID) != 8){
        return -1;
    }
    if (strlen(lastUpdate) > 30){
        return -1;
    }
    Change *dataptr = readFile<Change>(FILENAMES[1], CHANGEFILEPOINTER); // same is it 1?
    Change dummy(description, status, priority, releaseID, lastUpdate);
    size_t size = sizeof(dataptr)/sizeof(dataptr[0]);
    for (int i = 0; i < size; i++){
        if (dataptr[i] == dummy){
            delete [] dataptr;
            cout << "Record already exists :/" << endl;
            return 0;
        }
    }
    delete [] dataptr;
    cout << "Record is valid!" << endl;
    return 1;
}

/*
Validates that the Change object attributes are acceptable and makes sure no duplicate Change records exists.
A linear search algorithm is used to iterate through the Change records.
--------------------------------------------------------------------*/
Change CreateChange(const char *description, const char &status, const char &priority, const char *releaseID, const char *lastUpdate){
    if (ValidateChange(description, status, priority, releaseID, lastUpdate) == 1){
        Change newChange(description, status, priority, releaseID, lastUpdate);
        return newChange;
    }
    else{
        // RAISE EXCEPTION
        cout << "Could not create a new change!" << endl;
    }
}

/*
Create new Change object and also validates it.
No noticeable algorithm or data structure used.
--------------------------------------------------------------------*/
void UpdateLatestChange(const char *description, const char &status, const char &priority, const char *releaseID, const char *lastUpdate){
    Change lastChange = readRecord<Change>(FILENAMES[1], CHANGEFILEPOINTER);
    char *latestChangeID = lastChange.getChangeID();
    Change newChange(description, status, priority, releaseID, lastUpdate, latestChangeID);
    updateRecord<Change>(FILENAMES[1], CHANGEFILEPOINTER, newChange, latestChangeID);
}

/*
Print the status of the Change object to the console.
Uses the unsorted records data structure to retrieve the latest change.
--------------------------------------------------------------------*/
int CreateChangesReport(){
// DONE IN SCENARIO CONTROL
}

void CreateAnticipatedChangesProduct(const char *releaseID){
 // DONE IN SCENARIO CONTROL
}

void CreateUsersInformedOnUpdateReport(const char *changeID){
 // DONE IN SCENARIO CONTROL
}

void CommitChange(const Change &change, streampos &startPos = CHANGEFILEPOINTER, const string &FILENAME = FILENAMES[1]){
    writeRecord(FILENAME, startPos, change);
}

/*
Writes a Change object to a specified file at a given position.
Uses the unsorted records data structure to add the Change object.
--------------------------------------------------------------------*/
Change GetChangeDetails(streampos &startPos = CHANGEFILEPOINTER, const string &FILENAME = FILENAMES[1]){
    Change newChange = readRecord<Change>(FILENAME, startPos);
    return newChange;
}

/*
Reads a Change object from a specified file at a given position and returns it.
Uses the unsorted records data structure to read the Change object.
--------------------------------------------------------------------*/