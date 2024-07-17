#ifndef CHANGE_HPP
#define CHANGE_HPP

/* Change.hpp
Revision History:
Rev. 1 - 2024/07/01 Original by Nicholas Susanto
Rev. 2 - 2024/07/10 Revised by Sanchit Jain
---------------------------------------------------------------------------------------
This module provides an interface between the user interface and handling Changes in the system. 
The exported functions for Changes allow it to update a specific change, update one of the latest changes,
create a report of all changes, create a report for anticipated changes for a specific product and 
create a report of users to be informed on update on a change. Change.h is high in cohesion by encapsulating
all change attributes, its helper functions, and related functions. 
----------------------------------------------------------------------*/
#include <string>
#include <iostream>
#include <filesystem>
#include "Globals.hpp"
#include "Change.hpp"

class Change {
public:
    Change();
    Change(const char* changeID, const char *description, const char &status, const char &priority,
           const char *releaseID, const char *lastUpdate = "",
           const char *productName = "");

    bool operator==(const Change &other) const;

    void UpdateChange(const char *changeID, const char *description,
                      const char &status, const char &priority,
                      const char *releaseID);

    void DisplayDetails(std::ostream &out) const;

    const char *getChangeID() const;
    const char *change_displayProductName() const;
    const char *change_displayDesc() const;
    char change_displayStatus() const;
    char change_displayPriority() const;
    const char *change_displayRelID() const;

private:
    char changeID[7];
    char description[31];
    char status;
    char priority;
    char lastUpdate[9];
    char releaseID[9];
    char productName[11];
};

Change CreateChange(const char *description, const char &status,
                    const char &priority, const char *lastUpdate,
                    const char *releaseID, const char *changeID);

int ValidateChange(const char *description, const char &status,
                   const char &priority, const char *lastUpdate,
                   const char *releaseID);

void UpdateLatestChange(const char *description, const char &status,
                        const char &priority, const char *releaseID,
                        const char *lastUpdate);

int CreateChangesReport();

void CreateAnticipatedChangesProduct(const char *releaseID);

void CreateUsersInformedOnUpdateReport(const char *changeID);

void CommitChange(const Change &change, std::streampos &startPos = CHANGEFILEPOINTER,
                  const std::string &FILENAME = FILENAMES[1]);

Change GetChangeDetails(std::streampos startPos = CHANGEFILEPOINTER,
                        const std::string &FILENAME = FILENAMES[1]);

int InitChange(){
    filesystem::create_directory(DIRECTORY);
    if (!filesystem::exists(DIRECTORY + FILENAMES[1]))
    {
        ofstream file(DIRECTORY + FILENAMES[1], ios::binary);
        if (!file)
        {
            return -1;
        } else
        {
            return 1;
        } 
        file.close();
    } 
    else
    {
        return 0;
    }
    return -1;
}
/* int InitChange() uses the global variables streampos CHANGEFILEPOINTER and FILENAMES[1] to check if binary file "Changes.bin" exist in the DIRECTORY to essentially check if the program is being run for the first time. If it does, then it returns 0, if it doesn't then the files is created. If file was created successfully, it returns 1 else -1. The function does not fail.
----------------------------------------------------------------------*/
#endif