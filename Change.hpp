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
#include "Record.hpp"

/*----------------------------------------------------------------------
Exported constants/types/variables
Types:
 - Object of Class Change
----------------------------------------------------------------------*/
class Change
{
    public: 
        Change (
            const char *description,      // in
                                            // description for change, description has to be less than 30 characters
            const char &status,           // in
                                            // status for change, status has to be "-", "X", or "P"
            const char &priority,         // in
                                            // priority for change, priority level range is 1-5
            const char *releaseID,           // in
                                            // release ID of the product for the change requested, release ID is 8 characters
            const char *lastUpdate = "",   // in
                                            // date for lastupdate, null by default
            const char *changeID = "",         // in
                                            // id for change, changeID has to be 6 digits with the first digit being 1
            const char *productName = ""
             
            ); 
        /* Change(const string& changeID, const string& description, const string& status, const string& priority, 
        const string& lastUpdate, const string& productName, const int &releaseID) is a non-default constructor to 
        intilize its variables and create a Change object This function fails when a variable inputted is invalid. ChangeID generation is automatic and handled by templated function T IDGenerator(string &type, int &precision) from Globals.hpp.
        ----------------------------------------------------------------------*/
        bool operator==(const Change &other) const;
        // Add comments for this fn
        /*----------------------------------------------------------------------*/
        void UpdateChange(
            const char *changeID,         // in
                                            // id for change, changeID has to be 6 digits with the first digit being 1
            const char *description,      // in
                                            // description for change, description has to be less than 30 characters
            const char &status,           // in
                                            // status for change, status has to be "-", "X", or "P"
            const char &priority,         // in
                                            // priority for change, priority level range is 1-5
            const char *releaseID         // in
                                         // release ID of the product for the change requested, release ID is 8 characters 
        );
        /* void UpdateChange(const string &changeID, const string &description, const string &status, const string &priority, const int &releaseID) is used to update any change object specified by the user through its changeID. 
        It can change the description, state, priority, and anticipated release ID of a change object. 
        ----------------------------------------------------------------------*/
        void DisplayDetails(
            ostream &out       // in/out
                               // ostream object to handle << operation
        ) const;
        /* void DisplayDetails(ostream &out) handles printing of change type objects. 
        The data of each customer object is properly formatted, and indented with spaces. 
        This will come handy when displaying reports or details from the UI. 
        This function will fail if the calling Customer object is a dangling pointer.
        ----------------------------------------------------------------------*/
        char *getChangeID() const;
        void change_displayProductName() const;
        void change_displayDesc() const;
        void change_displayStatus() const;
        void change_displayPriority() const;
        void change_displayRelID() const;

        
    private:
        char *changeID; 
        char description[31];
        char status;
        char priority;
        char lastUpdate[9];
        char releaseID[9];
        char productName[11];
};
// ----------------------------------------------------------------------
Change CreateChange(
    const char *description,   // in
                                // description for a particular change
    const char &status,        // in
                                // status of a particular change
    const char &priority,      // in
                                // priority level of a particular change
    const char *lastUpdate,    // in
                                // date when the change had its last update
    const char *releaseID,      // in
                                // specific releaseID that the change is targeting to
    const char *changeID
);
/* Change CreateChange(const string &description, const string &status, const string &priority, const string &lastUpdate, const int &releaseID) is used to create a new change with all the information given in the parameter. ValidateChange is called inside this function. For each attribute's restriction, please refer to the User Manual. ChangeID generation is automatic and handled by templated function T IDGenerator(string &type, int &precision) from Globals.hpp.
----------------------------------------------------------------------*/
int ValidateChange(
    const char *description,       // in
                                    // description for a particular change
    const char &status,            // in
                                    // status of a particular change
    const char &priority,          // in
                                    // priority level of a particular change
    const char *lastUpdate,        // in
                                    // date when the change had its last update
    const char *releaseID          // specific releaseID that the change is targeting to
);
/* int ValidateChange(const string &description, const string &status, const string &priority, const string &lastUpdate, const int &releaseID) is used to check if all the information given in the parameter has the correct format. If same data already exists in system it returns 0, if the format is invalid it returns -1 else 1.
For each attribute's restriction, please refer to the User Manual.
----------------------------------------------------------------------*/
void UpdateLatestChange(
    const char *description,      // in
                                    // description for change, description has to be less than 30 characters
    const char &status,           // in
                                    // status for change, status has to be "-", "X", or "P"
    const char &priority,         // in 
                                    // priority for change, priority level range is 1-5
    const char *releaseID,            // in
                                    // release ID of the product for the change requested, release ID is 8 characters 
    const char *lastUpdate        // in
                                    // lsatUpdate for change, has to be less than 30 characters

);
/* void UpdateLatestChanges(const string &description, const string &status, const string &priority, const int &releaseID) displays a list of all changes and is specified which change is to be updated
by the user choosing from the list. It will ask the user to change the description, state, priorty, and
anticipated release ID of the object 
----------------------------------------------------------------------*/
int CreateChangesReport();
/* int CreateChangesReport() loads 10 recent changes per page with the option of the user pressing "N" to
show the next 10 changes from the list or "0" to go back to the previous menus.
----------------------------------------------------------------------*/
void CreateAnticipatedChangesProduct(
    const char *releaseID  // in
                    // ReleaseID for change requested, ReleaseID is 4 characters or less

);
/* void CreateAnticipatedChangesProduct (const int &releaseID) displays all the changes proposed for a product that is specified by 
the product name from the user 
----------------------------------------------------------------------*/
void CreateUsersInformedOnUpdateReport(
    const char *changeID      // in
                          // id for change, changeID has to be 6 digits with the first digit being 1
    
);
/* void CreateUsersInformedOnUpdateReport(const string &changeID) takes a specific changeID from the user and displays all the people 
that should be informed if an update occurs on that change object
----------------------------------------------------------------------*/
void CommitChange(
    const Change &change,                   // in
                                            // Change object to be written into Changes.bin
    streampos &startPos = CHANGEFILEPOINTER,// in
                                            // startPos is the position in Changes.bin for writing into the file (CHANGEFILEPOINTER).
    const string &FILENAME = FILENAMES[1]   // in
                                            // FILENAME is the name of the file to read from. By default it is FILENAMES[1] which is "Changes.bin"
    
);
/* void CommitChange(streampos &startPos, const string &FILENAME, const Change &change) uses the global variables streampos CHANGEFILEPOINTER, FILENAME, and a Change object to find the location to add Change record in Change binary file. If file does not exist, a new one is created and a confirmation message is shown to the user. If a record already exists, a message is displayed to the user saying that the record already exists. Further, if file I/O fails, an exception is raised:
FileWriteFailed: There was an error in writing to the file.
Otherwise, the Change object is added into the file. 
----------------------------------------------------------------------*/
Change GetChangeDetails(
    streampos startPos = CHANGEFILEPOINTER, // in
                                            // startPos is the position in Changes.bin for reading the file (CHANGEFILEPOINTER).
    const string &FILENAME = FILENAMES[1]   // in
                                            // FILENAME is the name of the file to read from. By default it is FILENAMES[1] which is "Changes.bin"
); 
/* Change GetChangeDetails(streampos startPos, const string &FILENAME) uses the global variables streampos CHANGEFILEPOINTER and FILENAME to find the location to read records from. 
It reads the information to create a Change object.
This function will work only if there is atleast 1 record of a change in the binary file else an exception will be raised:
    FileReadFailed: There was an error in reading the file.
GetChangeDetails() returns the Change class object which includes all the class variables
----------------------------------------------------------------------*/
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