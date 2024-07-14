#ifndef COMPLAINT_HPP
#define COMPLAINT_HPP

/* Complaint.hpp
REVISION HISTORY:
Rev. 1 - 24/07/03 Original by Seoyoung Kim
----------------------------------------------------------------------
This module, Complaint.hpp, hides the implementation of Complaint class. 
Complaint.hpp keeps its high cohesion by encapsulating all possible complaint entries in the system.
--------------------------------------------------------------------*/
#include <string> 
#include <iostream>
#include <filesystem>
#include "Globals.hpp"

/*--------------------------------------------------------------------
// Exported constants/types/variables
Types:
 - Object of Class Complaint

--------------------------------------------------------------------*/

class Complaint
{
    public:

        Complaint(
            const char *description,      // in  
                                            // description of complaint
            const char *dateOfComplaint,  // in 
                                            // date the complaint was created
            const char *changeID,         // in 
                                            // change id of complaint
            const char *releaseID,           // in  
                                            // release id of complaint
            const char *custID               // in  
                                            // customer id of complaint
        );
        /* Complaint(string &complaintID, string &description, string &dateOfComplaint, string &changeID, int &releaseID, int &custID) 
        is the non-default constructor for the Complaint class. 
        It takes in details of a complaint, and creates the complaint object. ComplaintID generation is automatic and handled by templated function T IDGenerator(string &type, int &precision) from Globals.hpp.
        ----------------------------------------------------------------------*/
        
        void DisplayDetails(
            ostream &out       // in/out
                               // ostream object to handle << operation
        ) const;
        /* void DisplayDetails(ostream &out) handles printing of Complaint type objects.
        The data of each complaint object is properly formatted, and indented with spaces. 
        This will come handy when displaying reports or details from the UI. 
        This function will fail if the calling Complaint object is a dangling pointer.
        ----------------------------------------------------------------------*/
    private:
        char complaintID[6];
        char description[31];
        char dateOfComplaint[9];
        char changeID[6];
        char releaseID[9];
        char custID[10];
};
//----------------------------------------------------------------------
int ValidateComplaint(
    const char *description = "",      // in
                                    // Description of complaint
    const char *dateOfComplaint = "",  // in
                                    // Date of Complaint
    const char *changeID = "",         // in
                                    // ChangeID the complaint is related to
    const char *releaseID = "",           // in
                                    // ReleaseID of the product the complaint concerns
    const char *custID = ""               // in
                                    // UserID of the user the complaint is related to
);
    
/* int ValidateComplaint(const string &description, const string &dateOfComplaint, const string &changeID, const int &releaseID, const int &custID) is a function used for validating the inputs provided by the user i.e; Customer Support Person. 
This function returns whether the user inputs are valid or not. 
If same data already exists in system it returns 0, if the format is invalid it returns -1 else 1.
This function performs checks on formats of complaint description, dateOfComplaint, among others. 
Call this function with details of the complaint to check whether the complaint info is valid.
----------------------------------------------------------------------*/
Complaint CreateComplaint(
    const char *description,      // in 
                                    // description of complaint
    const char *dateOfComplaint,  // in 
                                    // date the complaint was created
    const char *changeID,         // in 
                                    // changeID of complaint
    const char *releaseID,           // in 
                                    // releaseID of product
    const char *custID               //in 
                                    // custID of customer
);
/* void CreateComplaint(const string &description, const string &dateOfComplaint, const string &changeID, const int &releaseID, const int &custID) is a function used for creating new complaint.
If same data already exists in the system, the function prints "failed to add", else "successfully added"
This function creates new complaint with parameters of complaintID, description, dateOfComplaint, changeID, releaseID, and custID. ValidateComplaint is called inside this function. ComplaintID generation is automatic and handled by templated function T IDGenerator(string &type, int &precision) from Globals.hpp.
----------------------------------------------------------------------*/
void CommitComplaint(
    const Complaint &complaint,                 // in
                                                // Complaint object to be written into Complaints.bin
    streampos &startPos = COMPLAINTFILEPOINTER, // in
                                                // startPos is the position in Complaints.bin for writing into the file (COMPLAINTFILEPOINTER).
    const string &FILENAME = FILENAMES[2]       // in
                                                // FILENAME is the name of the file to read from. By default it is FILENAMES[2] which is "Complaints.bin"
);
/* void CommitComplaint(streampos &startPos, const string &FILENAME, const Complaint &complaint) uses the global variables streampos COMPLAINTFILEPOINTER, FILENAME, and a Complaint object to find the location to add Complaint record in Complaint binary file. If file does not exist, a new one is created and a confirmation message is shown to the user. If a record already exists, a message is displayed to the user saying that the record already exists. Further, if file I/O fails, an exception is raised:
FileWriteFailed: There was an error in writing to the file.
Otherwise, the Complaint object is added into the file. 
----------------------------------------------------------------------*/
Complaint GetComplaintDetails(
    streampos startPos = COMPLAINTFILEPOINTER,  // in
                                                // startPos is the position in Complaints.bin for reading the file (COMPLAINTFILEPOINTER).
    const string &FILENAME = FILENAMES[2]       // in
                                                // FILENAME is the name of the file to read from. By default it is FILENAMES[2] which is "Complaints.bin"
); 
/* Complaint GetDetails(streampos startPos, const string &FILENAME) uses the global variables streampos COMPLAINTFILEPOINTER and FILENAME to find the location to read records from. 
It reads the information to create a complaint object. 
This function will work only if there is atleast 1 record of a complaint in the binary file else an exception will be raised:
    FileReadFailed: There was an error in reading the file.
----------------------------------------------------------------------*/
int InitComplaint(){
    filesystem::create_directory(DIRECTORY);
    if (!filesystem::exists(DIRECTORY + FILENAMES[2]))
    {
        ofstream file(DIRECTORY + FILENAMES[2], ios::binary);
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
/* int InitComplaint() uses the global variables streampos COMPLAINTFILEPOINTER and FILENAMES[2] to check if binary file "Complaints.bin" exist in the DIRECTORY to essentially check if the program is being run for the first time. If it does, then it returns 0, if it doesn't then the file is created. If file was created successfully, it returns 1 else -1. The function does not fail.
----------------------------------------------------------------------*/
#endif
