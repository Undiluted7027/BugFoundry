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

class Change 
{
    public:
        Change();
        /*
        This is the default constructor for the Change class.
        It initializes all member variables to their default values.
        --------------------------------------------------------------------*/
        Change(
            const char* changeID,           // in: unique change ID for a change
            const char *description,        // in: description of a change detail
            const char &status,             // in: represent the status of a change
            const char &priority,           // in: priority level of a change
            const char *releaseID,          // in: unique release ID for a change. May hold null if not assigned yet. 
            const char *lastUpdate = "",    // in: year, month, day of a change created.
            const char *productName = ""    // in: the product name that a change is targeting to
        ); 
        /*
        This is the non-default constructor for the Change class. 
        It takes in details of a Change and creates the Change object.
        --------------------------------------------------------------------*/
        bool operator==(
            const Change &other     // in: other Change object to compare to
        ) const; 
        /* 
        bool operator==(const Change& other) is an equality operator overloader function 
        that compares the calling object with another Complaint object.
        ----------------------------------------------------------------------*/
        void UpdateChange(
            const char *changeID,           // in: unique change ID for a change
            const char *description,        // in: a new description of a change detail
            const char &status,             // in: a new status of a change
            const char &priority,           // in: a new priority level of a change
            const char *releaseID           // in: a new unique release ID for a change.
        );
        /*
        UpdateChange is used to update a change with the matching changeID included in the parameter.
        Some parameter may be blank, as the user might want to remain some attributes unchanged.
        -------------------------------------------------------------------------*/
        void DisplayDetails(
            std::ostream &out   // in: location to display the detail of a change
        ) const; // Display change details
        /*
        DisplayDetails is used to display all the information of a change.
        --------------------------------------------------------------------------*/
        const char *getChangeID() const;                // Accessor for changeID
        const char *change_displayProductName() const;  // Accessor for productName
        const char *change_displayDesc() const;         // Accessor for description
        char change_displayStatus() const;              // Accessor for status
        char change_displayPriority() const;            // Accessor for priority
        const char *change_displayRelID() const;        // Accessor for releaseID
        
    private:
        char changeID[7];       // Change ID
        char description[31];   // Description of the change
        char status;            // Status of the change
        char priority;          // Priority of the change
        char lastUpdate[9];     // Last update date of the change
        char releaseID[9];      // Release ID associated with the change
        char productName[11];   // Product name associated with the change
};

Change CreateChange(
    const char *description,    // in: description of the change
    const char &status,         // in: status of the change
    const char &priority,       // in: priority of the change
    const char *lastUpdate,     // in: year, month, day of the date when the change is created
    const char *releaseID,      // in: unique release ID for the change. May hold null if not assigned yet.
    const char *changeID        // in: unique change ID for the change
); 
/*
Create a new Change object with provided attributes in the paraamter
and returns the newly created Change object.
--------------------------------------------------------------*/
int ValidateChange(
    const char *description,    // in: description of the change
    const char &status,         // in: status of the change
    const char &priority,       // in: priority of the change
    const char *lastUpdate,     // in: year, month, day of the date when the change is created
    const char *releaseID     // in: unique release ID for the change. May hold null if not assigned yet.
); 
/*
Validate change data by checking the format 
of provided attributes provided in function parameter 
If valid, returns 1. If invalid, returns -1 or 0
---------------------------------------------------------------*/
void UpdateLatestChange(
    const char *description,    // in: description of the change
    const char &status,         // in: status of the change
    const char &priority,       // in: priority of the change
    const char *lastUpdate,     // in: year, month, day of the date when the change is created
    const char *releaseID       // in: unique release ID for the change. May hold null if not assigned yet.
); 
/*
UpdateLatestChange displays 10 recently reported changes.
User chooses one of the displayed changes to update or display the next 10 recently reported changes.
---------------------------------------------------------------*/
int CreateChangesReport(); 
/*
Displays the latest 10 reported changes.
User can choose to display the next 10 changes.
------------------------------------------------------------------*/
void CreateAnticipatedChangesProduct(
    const char *releaseID   // in: the releaseID targeted to display its changes 
);
/*
Displays the Changes that are related to the releaseID provided in the function parameter
that are in status of InProgress 
-------------------------------------------------------------------*/
void CreateUsersInformedOnUpdateReport(
    const char *changeID    // in: the changeID targeted to display users who are related to that change
);
/*
Displays the users that needs to be informed on update from changeID provided in the function parameter
-------------------------------------------------------------------*/
void CommitChange(
    const Change &change,                           // in: the change to be commited to the file
    std::streampos &startPos = CHANGEFILEPOINTER,   // in: the file pointer that holds location of the end of file
    const std::string &FILENAME = FILENAMES[1]      // in: the file that holds all the changes
); 
/*
Writes the change provided in function provided into the end of the Change file.
-------------------------------------------------------------------*/
Change GetChangeDetails(
    std::streampos startPos = CHANGEFILEPOINTER,    // in: the file pointer that holds location of the end of file
    const std::string &FILENAME = FILENAMES[1]      // in: the file that holds all the changes
);
/*
Retrieve Change details from file
-------------------------------------------------------------------*/
int InitChange(); 
/*
Initialize the Change module
--------------------------------------------------------------------*/
#endif // CHANGE_HPP
