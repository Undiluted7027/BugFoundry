#ifndef COMPLAINT_HPP
#define COMPLAINT_HPP

/* Complaint.hpp
REVISION HISTORY:
Rev. 1 - 24/07/03 Original by Seoyoung Kim
----------------------------------------------------------------------
This module, Complaint.hpp, hides the implementation of Complaint class. 
Complaint.hpp keeps its high cohesion by encapsulating all possible complaint entries in the system.
----------------------------------------------------------------------*/

#include <string> 
#include <iostream>
#include <filesystem>
#include "Globals.hpp"

/*----------------------------------------------------------------------
Exported constants/types/variables
Types:
 - Object of Class Complaint
----------------------------------------------------------------------*/

class Complaint {
public:
    Complaint();
    /* Complaint() is the default constructor for the Complaint class.
       It initializes all member variables to their default values.
    ----------------------------------------------------------------------*/
    
    Complaint(
        const char* complaintID,   // Unique ID of complaint
        const char* description,   // Description of complaint
        const char* dateOfComplaint,// Date the complaint was created
        const char* changeID,      // Change ID of complaint
        const char* releaseID,     // Release ID of product
        const char* custID         // Customer ID
    );
    /* Complaint(const char* complaintID, const char* description, const char* dateOfComplaint,
                 const char* changeID, const char* releaseID, const char* custID) is the non-default 
       constructor for the Complaint class. It takes in details of a complaint and creates the 
       complaint object.
    ----------------------------------------------------------------------*/
    
    Complaint(
        const Complaint& other  // Other complaint object to copy from
    );
    /* Complaint(const Complaint& other) is the copy constructor for the Complaint class.
       It takes in a complaint object and makes a deep copy of it.
    ----------------------------------------------------------------------*/
    
    Complaint& operator=(
        const Complaint& other  // Other complaint object to assign from
    );
    /* Complaint& operator=(const Complaint& other) is an assignment operator overloader function 
       that deeply assigns the contents of one Complaint object to another.
    ----------------------------------------------------------------------*/
    
    bool operator==(
        const Complaint& other  // Other complaint object to compare to
    ) const;
    /* bool operator==(const Complaint& other) is an equality operator overloader function 
       that compares the calling object with another Complaint object.
    ----------------------------------------------------------------------*/
    
    ~Complaint();
    /* ~Complaint() is the destructor for the class and does not have anything in it since nothing 
       has been assigned/created on the heap memory.
    ----------------------------------------------------------------------*/

    void DisplayDetails(
        std::ostream& out  // ostream object to handle calling with << operator
    ) const;
    /* void DisplayDetails(std::ostream& out) const is a helper function to display details of 
       a Complaint object using << operator. It fails to show the required output if any of the 
       member variables/C-strings have only null-character in them.
    ----------------------------------------------------------------------*/

    // Getters
    const char* getComplaintID() const { return complaintID; } // returns ID of complaint
    const char* getDescription() const { return description; } // returns description of complaint
    const char* getDateOfComplaint() const { return dateOfComplaint; } // returns date of complaint
    const char* getChangeID() const { return changeID; } // returns change ID of complaint
    const char* getReleaseID() const { return releaseID; } // returns release ID of product
    const char* getCustID() const { return custID; } // returns customer ID
    private:
    char complaintID[7];      // Unique ID of complaint
    char description[31];     // Description of complaint
    char dateOfComplaint[9];  // Date complaint was created (YYYYMMDD format)
    char changeID[6];         // Change ID associated with complaint
    char releaseID[9];        // Release ID of the product
    char custID[11];          // Customer ID (10 characters + null terminator)
};
// ----------------------------------------------------------------------
void safeStrCopy(
    char* dest,          // Destination buffer to copy string to
    const char* src,     // Source string to copy from
    size_t maxLen        // Maximum length of the destination buffer
);
/* void safeStrCopy(char* dest, const char* src, size_t maxLen) is a helper function to safely copy 
   strings from src to dest ensuring no buffer overflow by limiting the copy to maxLen.
----------------------------------------------------------------------*/

Complaint CreateComplaint(
    const char* description,     // Description of complaint
    const char* dateOfComplaint, // Date the complaint was created
    const char* changeID,        // Change ID of complaint
    const char* releaseID,       // Release ID of product
    const char* custID           // Customer ID
);
/* Complaint CreateComplaint(const char* description, const char* dateOfComplaint, const char* changeID, 
                             const char* releaseID, const char* custID) takes in details of the complaint, 
   validates the input by calling ValidateComplaint, and returns a Complaint object.
----------------------------------------------------------------------*/

int ValidateComplaint(
    const char* description,     // Description of complaint
    const char* dateOfComplaint, // Date the complaint was created
    const char* changeID,        // Change ID of complaint
    const char* releaseID,       // Release ID of product
    const char* custID           // Customer ID
);
/* int ValidateComplaint(const char* description, const char* dateOfComplaint, const char* changeID, 
                         const char* releaseID, const char* custID) validates the inputs provided by the user. 
   This function returns whether the input is valid or not. If invalid, returns -1; otherwise, returns 1.
----------------------------------------------------------------------*/

void CommitComplaint(
    const Complaint& complaint,  // Complaint to add in binary file
    std::streampos& startPos,    // File pointer of the binary file
    const std::string& FILENAME  // Location-name of file
);
/* void CommitComplaint(const Complaint& complaint, std::streampos& startPos, const std::string& FILENAME) 
   takes in a complaint object, file pointer, and name of file, and adds a record in the binary file.
   This function fails if there is an error in writing to the file.
----------------------------------------------------------------------*/

Complaint GetComplaintDetails(
    std::streampos& startPos,    // File pointer of the binary file
    const std::string& FILENAME  // Location-name of file
);
/* Complaint GetComplaintDetails(std::streampos& startPos, const std::string& FILENAME) 
   takes in a file pointer, reads the file, and returns the record at startPos by converting to Complaint object. 
   This function fails if there is an error in reading the file or casting information.
----------------------------------------------------------------------*/

void PrintAllComplaints(
    const std::string& FILENAME  // Location-name of file
);
/* void PrintAllComplaints(const std::string& FILENAME) 
   takes in location of binary file and prints all records in a tabulated form. 
   This function fails if there is an error in reading the file or casting information.
----------------------------------------------------------------------*/

bool UpdateComplaint(
    const char* complaintID,     // Unique ID of complaint
    const Complaint& updatedComplaint, // Updated complaint object
    const std::string& FILENAME  // Location-name of file
);
/* bool UpdateComplaint(const char* complaintID, const Complaint& updatedComplaint, const std::string& FILENAME) 
   updates a complaint record in the binary file identified by complaintID with updatedComplaint. 
   This function fails if there is an error in reading/writing to the file or if the complaintID is not found.
----------------------------------------------------------------------*/

int InitComplaint();
/* int InitComplaint() uses the global variables streampos COMPLAINTFILEPOINTER and FILENAMES[1] 
   to check if binary file "Complaints.bin" exists in the DIRECTORY to essentially check if the program 
   is being run for the first time. If it does, then it returns 0; if it doesn't, then the file is created. 
   If file was created successfully, it returns 1; else, -1. The function does not fail.
----------------------------------------------------------------------*/

#endif // COMPLAINT_HPP
