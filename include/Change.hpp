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
#include <iomanip>
#include <filesystem>

#include "Complaint.hpp"
#include "Customer.hpp"  // Include for handling Customers (assuming Customer class is defined here)
#include "Globals.hpp"   // Include necessary global constants and declarations
#include "Exceptions.hpp"
#include "Globals.hpp" // Include necessary global constants and declarations

class Change 
{
public:
    
    /*
    This is the default constructor of the Change class.
    ------------------------------------------------------------------------*/
    Change(

    );
    /*
    This is the parameterized constructor of the Change class.
    It takes all its attributes as the parameters and creates a new Change object. 
    ------------------------------------------------------------------------*/
    Change(
        const char* changeID,           // in: The changeID for this Change class.
        const char *description,        // in: The description of what this Change is about
        const char &status,             // in: The status level of this Change.
        const char &priority,           // in: The priority level of this Change.
        const char *releaseID,          // in: This Change is targeted on this releaseID.
        const char *lastUpdate = "",    // in: The anticipated release date of this Change.
        const char *productName = ""    // in: This Change is targeted on the product with this name.
    ); 
    /*
    This is the equality operator overloader for the Change class.
    ------------------------------------------------------------------------*/
    bool operator==(
        const Change &other     // Compares the Change class with the 'other' Change.          
    ) const; 
    /*
    This updates the detail of the Change object
    ------------------------------------------------------------------------*/
    void UpdateChange(
        const char *changeID,           // in: The changeID of Change object to change its detail
        const char *description,        // in: The new description to the Change object
        const char &status,             // in: The new status level of the Change object
        const char &priority,           // in: The new priority level of the Change object
        const char *releaseID,          // in: The new releaeID of the Change object 
        const char* lastUpdate          // in: The new anticipated release date of this Change object.
    ); 
    /*
    Displays the attributes detail of the Change object
    ------------------------------------------------------------------------*/
    void DisplayDetails(
        std::ostream &out               // in: The location of where the details are printed.
    ) const; 

    // Accessor for changeID
    const char *getChangeID() const;

    // Accessor for productName
    const char *change_displayProductName() const;

    // Accessor for description 
    const char *change_displayDesc() const;

    // Accessor for status 
    char change_displayStatus() const; 

    // Accessor for priority
    char change_displayPriority() const; 

    // Accessor for releaseID
    const char *change_displayRelID() const; 

private:

    char changeID[7];           // Change ID
    char description[31];       // Description of the change
    char status;                // Status of the change
    char priority;              // Priority of the change
    char lastUpdate[11];        // Last update date of the change
    char releaseID[9];          // Release ID associated with the change
    char productName[11];       // Product name associated with the change
};
/*
Creates a new Change object. It also runs validation for each attributes first before creating the Change object. 
------------------------------------------------------------------------------*/
Change CreateChange(
    const char *description,    // in: The description explaining what this Change object is for.
    const char &status,         // in: The status level of this Change object
    const char &priority,       // in: The priority level of this Change object
    const char *lastUpdate,     // in: The anticipated release date of this Change object
    const char *releaseID,      // in: This Change is targeting on this releaseID. 
    const char *changeID        // in: The changeID for this Change object.
); 
/*
Checks validation for each attributes of the Change attribute.
------------------------------------------------------------------------------*/
int ValidateChange(
    const char *description,    // in: The description of the Change object to check.
    const char &status,         // in: The status of the Change object to check.
    const char &priority,       // in: The priority level Change object to check.
    const char *lastUpdate,     // in: The anticipated release date of the Change object to check.
    const char *releaseID       // in: The releaseID of the Change object to check.
); 
/*
Updates the change that is most recently reported
------------------------------------------------------------------------------*/
void UpdateLatestChange(
    const char *description,    // The new description that explains what the Change object is for 
    const char &status,         // The new status level for this Change object
    const char &priority,       // The new priority level for this Change object
    const char *releaseID,      // The new releaseID level for thie Change object
    const char *lastUpdate      // The new anticipated release date for this Change object
); 
/*
Creates a list of Change object with all its attribute details
------------------------------------------------------------------------------*/
int CreateChangesReport(

); 
/*
Creates a list of Change object that targets on a specific product with a specific releaseID
------------------------------------------------------------------------------*/
void CreateAnticipatedChangesProduct(
    const char *releaseID
); 
/*
Creates a list of User objects who are associated / releated to the Change with this changeID
------------------------------------------------------------------------------*/
void CreateUsersInformedOnUpdateReport(
    const char *changeID    // in: All users who are associated / related with this changeID will be listed
);
/*
Write and store the Change object to the data file.
------------------------------------------------------------------------------*/
void CommitChange(
    const Change &change,                           // in: The Change object to write on the data file
    std::streampos &startPos = CHANGEFILEPOINTER,   // inout: The location (file descriptor) in data file to write the Change object on
    const std::string &FILENAME = FILENAMES[1]      // in: The data file for storing Change objects
);
/*
Fetch the Change object from the data file with all its attributes
------------------------------------------------------------------------------*/
Change GetChangeDetails(
    std::streampos startPos = CHANGEFILEPOINTER,    // in: The location (file descriptor) in data file to find the Change object
    const std::string &FILENAME = FILENAMES[1]      // in: The data file for storing Change objects
); // Retrieve Change details from file
/*

------------------------------------------------------------------------------*/
void CommitUpdatedChange(
    const Change &change, 
    const std::string &FILENAME
);
/*
Checks and initializes the Change data file and file descriptor
------------------------------------------------------------------------------*/
int InitChange(

);

#endif // CHANGE_HPP
