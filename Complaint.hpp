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

class Complaint {
private:
    char complaintID[7];
    char description[31];
    char dateOfComplaint[9];
    char changeID[6];
    char releaseID[9];
    char custID[11];  // Assuming custID is 10 characters + null terminator

public:
    Complaint();
    Complaint(const char* complaintID, const char* description, const char* dateOfComplaint, const char* changeID, 
              const char* releaseID, const char* custID);
    Complaint(const Complaint& other);
    Complaint& operator=(const Complaint& other);
    bool operator==(const Complaint& other) const;
    ~Complaint();

    void DisplayDetails(std::ostream& out) const;

    // Getters
    const char* getComplaintID() const { return complaintID; }
    const char* getDescription() const { return description; }
    const char* getDateOfComplaint() const { return dateOfComplaint; }
    const char* getChangeID() const { return changeID; }
    const char* getReleaseID() const { return releaseID; }
    const char* getCustID() const { return custID; }
};

// Function declarations
void safeStrCopy(char* dest, const char* src, size_t maxLen);
Complaint CreateComplaint(
    const char *description,    // in
                                // description of complaint
    const char *dateOfComplaint,// in
                                // date the complaint was created
    const char *changeID,       // in
                                // changeID of complaint
    const char *releaseID,      // in
                                // releaseID of product
    const char *custID          // in
                                // custID of customer
);
int ValidateComplaint(const char* description, const char* dateOfComplaint, const char* changeID, 
                      const char* releaseID, const char* custID);
Complaint CreateComplaint(const char* description, const char* dateOfComplaint, const char* changeID, 
                          const char* releaseID, const char* custID);
void CommitComplaint(const Complaint& complaint, std::streampos& startPos, const std::string& FILENAME);
Complaint GetComplaintDetails(std::streampos& startPos, const std::string& FILENAME);
void PrintAllComplaints(const std::string& FILENAME);
bool UpdateComplaint(const char* complaintID, const Complaint& updatedComplaint, const std::string& FILENAME);
int InitComplaint();

#endif // COMPLAINT_HPP