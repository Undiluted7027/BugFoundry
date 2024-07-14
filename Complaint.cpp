/* Main.cpp
REVISION HISTORY:
Rev. 1 - 24/07/10 Original by Nicholas Susanto
----------------------------------------------------------------------
This CPP file called Complaint.cpp handles the complaints of the program.
--------------------------------------------------------------------*/

#include "Complaint.hpp"
#include "Globals.hpp"
#include "drivers.cpp"
#include<cstring>
#include<iostream>

using namespace std;

Complaint::Complaint(const char *description, const char *dateOfComplaint, const char *changeID, const char *releaseID, const char *custID){
    const char *generatedID = IDGenerator<const char *>('2', 6);
    strcpy(this->complaintID, generatedID);
    this->complaintID[sizeof(this->complaintID)-1] = '\0';
    strcpy(this->description, description);
    this->description[sizeof(this->description) - 1] = '\0';
    strcpy(this->dateOfComplaint, dateOfComplaint);
    this->dateOfComplaint[sizeof(this->dateOfComplaint) - 1] = '\0';
    strcpy(this->changeID, changeID);
    this->changeID[sizeof(this->changeID) - 1] = '\0';
    strcpy(this->releaseID, releaseID);
    this->releaseID[sizeof(this->releaseID)-1] = '\0';
    strcpy(this->custID, custID);
    this->custID[sizeof(this->custID)-1] = '\0';
}

void Complaint::DisplayDetails(ostream &out) const{
    if (strlen(description) == 0 || strlen(dateOfComplaint) == 0 || strlen(changeID) == 0 || releaseID == nullptr || custID == nullptr)
        out << "Error in reading Complaint information. One or more attributes of complaint do not have value(s)" << endl;
        // RAISE ERROR
        // exit(1);
    else{
        out << "complaintID: " << complaintID << endl;
        out << "description: " << description << endl;
        out << "dateOfComplaint: " << dateOfComplaint << endl;
        out << "changeID: " << changeID << endl;
        out << "releaseID: " << releaseID << endl;
        out << "custID: " << custID << endl;
    }
}

int ValidateComplaint(const char *description, const char *dateOfComplaint, const char *changeID, const char *releaseID, const char *custID){
    if (strlen(description) > 30){
        return -1;
    }
    if (strlen(dateOfComplaint) != 8){
        return -1;
    }
    if (dateOfComplaint[2] != '-' ||  dateOfComplaint[5] != '-'){
        return -1;
    }
    int year = (dateOfComplaint[0] - '0') * 10 + (dateOfComplaint[1] - '0');
    if (year < 24 || year > 99){
        return -1;
    }

    int month = (dateOfComplaint[3] - '0') * 10 + (dateOfComplaint[4] - '0');
    if (month < 1 || month > 12){
        return -1;
    }
    int day = (dateOfComplaint[6] - '0') * 10 + (dateOfComplaint[7] - '0');
    if (day < 1 || day > 31){
        return -1;
    }
    if (strlen(changeID) != 6){
        return -1;
    }
    if(changeID[0] != '1'){
        return -1;
    }
    if (releaseID < 10000000 || releaseID > 99999999){
        return -1;
    }
    if (custID < 100000000 || custID > 999999999){
        return -1;
    }
    return 1;
    // how to check if this complaint is a duplicate?
}


Complaint CreateComplaint (const char *description, const char *dateOfComplaint, const char *changeID, const char *releaseID, const char *custID){
    if (ValidateComplaint(description, dateOfComplaint, changeID, releaseID, custID) == 1){
        Complaint newComplaint(description, dateOfComplaint, changeID, releaseID, custID);
        return newComplaint;
    }
    else{
        // RAISE EXCEPTION
        cout << "Could not create a new complaint!" << endl;
    }
}

void CommitComplaint(const Complaint &complaint, streampos &startPos = COMPLAINTFILEPOINTER, const string &FILENAME = FILENAMES[2]){
    writeRecord(FILENAME, startPos, complaint);
}

Complaint GetComplaintDetails(streampos &startPos = COMPLAINTFILEPOINTER, const string &FILENAME = FILENAMES[2]){
    Complaint newComplaint = readRecord<Complaint>(FILENAME, startPos);
    return newComplaint;
}

