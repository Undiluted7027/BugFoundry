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

#include "Change.hpp"
#include "Product.hpp"
#include "Exceptions.hpp"
#include "Globals.hpp"

/*----------------------------------------------------------------------
Exported constants/types/variables
Types:
 - Object of Class Complaint
----------------------------------------------------------------------*/

class Complaint 
{
public:

   /* 
   Complaint() is the default constructor for the Complaint class.
   It initializes all member variables to their default values.
   ----------------------------------------------------------------------*/ 
   Complaint(

   );
   /* 
   Complaint(const char* complaintID, const char* description, const char* dateOfComplaint,
   const char* changeID, const char* releaseID, const char* custID) is the non-default 
   constructor for the Complaint class. It takes in details of a complaint and creates the 
   complaint object.
   ----------------------------------------------------------------------*/    
   Complaint(
      const char* complaintID,       // in: Unique ID of complaint
      const char* description,       // in: Description of complaint
      const char* dateOfComplaint,   // in: Date the complaint was created
      const char* changeID,          // in: Change ID of complaint
      const char* releaseID,         // in: Release ID of product
      const char* custID             // in: Customer ID
   );
   /*
   Complaint(const Complaint& other) is the copy constructor for the Complaint class.
   It takes in a complaint object and makes a deep copy of it.
   ----------------------------------------------------------------------*/   
   Complaint(
      const Complaint& other  // in: Other complaint object to copy from
   );
   /* 
   Complaint& operator=(const Complaint& other) is an assignment operator overloader function 
   that deeply assigns the contents of one Complaint object to another.
   ----------------------------------------------------------------------*/   
   Complaint& operator=(
      const Complaint& other  // Other complaint object to assign from
   );
   /* 
   bool operator==(const Complaint& other) is an equality operator overloader function 
   that compares the calling object with another Complaint object.
   ----------------------------------------------------------------------*/   
   bool operator==(
      const Complaint& other  // Other complaint object to compare to
   ) const;
   /* 
   ~Complaint() is the destructor for the class and does not have anything in it since nothing 
   has been assigned/created on the heap memory.
   ----------------------------------------------------------------------*/
   ~Complaint();
   /* 
   void DisplayDetails(std::ostream& out) const is a helper function to display details of 
   a Complaint object using << operator. It fails to show the required output if any of the 
   member variables/C-strings have only null-character in them.
   ----------------------------------------------------------------------*/
   void DisplayDetails(
      std::ostream& out  // ostream object to handle calling with << operator
   ) const;
   
   // returns ID of complaint
   const char* getComplaintID() const { return complaintID; } 
   
   // returns description of complaint
   const char* getDescription() const { return description; } 
   
   // returns date of complaint
   const char* getDateOfComplaint() const { return dateOfComplaint; }
   
   // returns change ID of complaint 
   const char* getChangeID() const { return changeID; } 

   // returns release ID of product
   const char* getReleaseID() const { return releaseID; }
   
   // returns customer ID 
   const char* getCustID() const { return custID; } 
   
private:
   
   char complaintID[7];      // Unique ID of complaint
   char description[31];     // Description of complaint
   char dateOfComplaint[11];  // Date complaint was created (YYYY-MM-DD format)
   char changeID[7];         // Change ID associated with complaint
   char releaseID[9];        // Release ID of the product
   char custID[11];          // Customer ID (10 characters + null terminator)
};

/* 
void safeStrCopy(char* dest, const char* src, size_t maxLen) is a helper function to safely copy 
strings from src to dest ensuring no buffer overflow by limiting the copy to maxLen.
----------------------------------------------------------------------*/
void safeStrCopy(
   char* dest,          // in: Destination buffer to copy string to
   const char* src,     // in: Source string to copy from
   size_t maxLen        // in: Maximum length of the destination buffer
);
/* 
Complaint CreateComplaint(const char* description, const char* dateOfComplaint, const char* changeID, 
                           const char* releaseID, const char* custID) takes in details of the complaint, 
validates the input by calling ValidateComplaint, and returns a Complaint object.
----------------------------------------------------------------------*/
Complaint CreateComplaint(
   const char* description,     // in: Description of complaint
   const char* dateOfComplaint, // in: Date the complaint was created
   const char* changeID,        // in: Change ID of complaint
   const char* releaseID,       // in: Release ID of product
   const char* custID           // in: Customer ID
);
/* 
int ValidateComplaint(const char* description, const char* dateOfComplaint, const char* changeID, 
                        const char* releaseID, const char* custID) validates the inputs provided by the user. 
This function returns whether the input is valid or not. If invalid, returns -1; otherwise, returns 1.
----------------------------------------------------------------------*/
int ValidateComplaint(
   const char* description,     // in: Description of complaint
   const char* dateOfComplaint, // in: Date the complaint was created
   const char* changeID,        // in: Change ID of complaint
   const char* releaseID,       // in: Release ID of product
   const char* custID           // in: Customer ID
);
/* 
void CommitComplaint(const Complaint& complaint, std::streampos& startPos, const std::string& FILENAME) 
takes in a complaint object, file pointer, and name of file, and adds a record in the binary file.
This function fails if there is an error in writing to the file.
----------------------------------------------------------------------*/
void CommitComplaint(
   const Complaint& complaint,  // in: Complaint to add in binary file
   std::streampos& startPos,    // inout: File pointer of the binary file
   const std::string& FILENAME  // in: Location-name of file
);
/* 
Complaint GetComplaintDetails(std::streampos& startPos, const std::string& FILENAME) 
takes in a file pointer, reads the file, and returns the record at startPos by converting to Complaint object. 
This function fails if there is an error in reading the file or casting information.
----------------------------------------------------------------------*/
Complaint GetComplaintDetails(
   std::streampos& startPos,    // in: File pointer of the binary file
   const std::string& FILENAME  // in: Location-name of file
);
/* 
void PrintAllComplaints(const std::string& FILENAME) 
takes in location of binary file and prints all records in a tabulated form. 
This function fails if there is an error in reading the file or casting information.
----------------------------------------------------------------------*/
void PrintAllComplaints(
   const std::string& FILENAME  // in: Location-name of file
);
/* 
bool UpdateComplaint(const char* complaintID, const Complaint& updatedComplaint, const std::string& FILENAME) 
updates a complaint record in the binary file identified by complaintID with updatedComplaint. 
This function fails if there is an error in reading/writing to the file or if the complaintID is not found.
----------------------------------------------------------------------*/
bool UpdateComplaint(
   const char* complaintID,            // in: Unique ID of complaint
   const Complaint& updatedComplaint,  // in: Updated complaint object
   const std::string& FILENAME         // in: Location-name of file
);
/* 
int InitComplaint() uses the global variables streampos COMPLAINTFILEPOINTER and FILENAMES[1] 
to check if binary file "Complaints.bin" exists in the DIRECTORY to essentially check if the program 
is being run for the first time. If it does, then it returns 0; if it doesn't, then the file is created. 
If file was created successfully, it returns 1; else, -1. The function does not fail.
----------------------------------------------------------------------*/
int InitComplaint(

);


#endif // COMPLAINT_HPP
