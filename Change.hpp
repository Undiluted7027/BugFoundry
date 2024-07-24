#ifndef CHANGE_HPP
#define CHANGE_HPP

/* Change.hpp
Revision History:
Rev. 2 - 2024/07/10 Revised by Sanchit Jain
Rev. 1 - 2024/07/01 Original by Nicholas Susanto
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
#include "Globals.hpp" // Include necessary global constants and declarations

class Change {
public:
    Change(); // Default constructor
    Change(const char* changeID, const char *description, const char &status, const char &priority,
           const char *releaseID, const char *lastUpdate = "",
           const char *productName = ""); // Parameterized constructor

    bool operator==(const Change &other) const; // Equality operator overload

    void UpdateChange(const char *changeID, const char *description,
                      const char &status, const char &priority,
                      const char *releaseID); // Update change details

    void DisplayDetails(std::ostream &out) const; // Display change details

    const char *getChangeID() const; // Accessor for changeID
    const char *change_displayProductName() const; // Accessor for productName
    const char *change_displayDesc() const; // Accessor for description
    char change_displayStatus() const; // Accessor for status
    char change_displayPriority() const; // Accessor for priority
    const char *change_displayRelID() const; // Accessor for releaseID

private:
    char changeID[7]; // Change ID
    char description[31]; // Description of the change
    char status; // Status of the change
    char priority; // Priority of the change
    char lastUpdate[9]; // Last update date of the change
    char releaseID[9]; // Release ID associated with the change
    char productName[11]; // Product name associated with the change
};

Change CreateChange(const char *description, const char &status,
                    const char &priority, const char *lastUpdate,
                    const char *releaseID, const char *changeID); // Create a new Change object

int ValidateChange(const char *description, const char &status,
                   const char &priority, const char *lastUpdate,
                   const char *releaseID); // Validate change data

void UpdateLatestChange(const char *description, const char &status,
                        const char &priority, const char *releaseID,
                        const char *lastUpdate); // Update the latest change

int CreateChangesReport(); // Create a report of all changes

void CreateAnticipatedChangesProduct(const char *releaseID); // Create a report of anticipated changes for a product from releaseID

void CreateUsersInformedOnUpdateReport(const char *changeID); // Create a report of users to be informed on update from changeID

void CommitChange(const Change &change, std::streampos &startPos = CHANGEFILEPOINTER,
                  const std::string &FILENAME = FILENAMES[1]); // Commit a Change object to file

Change GetChangeDetails(std::streampos startPos = CHANGEFILEPOINTER,
                        const std::string &FILENAME = FILENAMES[1]); // Retrieve Change details from file

int InitChange(); // Initialize the Change module

#endif // CHANGE_HPP
