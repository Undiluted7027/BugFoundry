/* Change.cpp
REVISION HISTORY:
Rev. 1 - 24/07/15 Original by Nicholas Susanto
----------------------------------------------------------------------
This CPP file called Changes.cpp handles the changes of the program.
--------------------------------------------------------------------*/

#include "Change.hpp"
#include "Complaint.cpp" // Include for handling Complaints (assuming Complaint class is defined here)
#include "Customer.hpp" // Include for handling Customers (assuming Customer class is defined here)
#include "Globals.hpp" // Include necessary global constants and declarations
#include <cstring>
#include <iostream>
#include <set>

using namespace std;

// Default constructor for Change class
Change::Change(): status('-'), priority('1'){
    memset(changeID, 0, sizeof(changeID));
    memset(description, 0, sizeof(description));
    memset(lastUpdate, 0, sizeof(lastUpdate));
    memset(releaseID, 0, sizeof(releaseID));
    memset(productName, 0, sizeof(productName));
}

// Parameterized constructor for Change class
Change::Change(const char *changeID, const char* description, const char& status, const char& priority,
               const char* releaseID, const char* lastUpdate,
               const char* productName)
    : status(status), priority(priority) {
    
    // Generate a new changeID if not provided
    if (strlen(changeID) != 0) {
        safeStrCopy(this->changeID, changeID, sizeof(this->changeID));
    } else {
        char* generatedID = IDGenerator('3', 7); // Assuming IDGenerator function is used to generate IDs
        safeStrCopy(this->changeID, generatedID, sizeof(this->changeID));
        delete[] generatedID;
    }
    
    safeStrCopy(this->description, description, sizeof(this->description));
    safeStrCopy(this->releaseID, releaseID, sizeof(this->releaseID));
    safeStrCopy(this->lastUpdate, lastUpdate, sizeof(this->lastUpdate));
    safeStrCopy(this->productName, productName, sizeof(this->productName));
}


bool Change::operator==(const Change& other) const {
    return (strcmp(changeID, other.changeID) == 0 || strcmp(description, other.description) == 0);
}
/*
Checks if two Change objects are equal based on changeID or description. 
No noticeable algorithm or data structure used.
--------------------------------------------------------------------*/
// UpdateChange method to update existing change details
void Change::UpdateChange(const char* changeID, const char* description, const char& status,
                          const char& priority, const char* releaseID) {
    safeStrCopy(this->changeID, changeID, sizeof(this->changeID));
    safeStrCopy(this->description, description, sizeof(this->description));
    this->status = status;
    this->priority = priority;
    safeStrCopy(this->releaseID, releaseID, sizeof(this->releaseID));
}

// DisplayDetails method to display change details
void Change::DisplayDetails(std::ostream& out) const {
    out << std::left
        << std::setw(12) << productName
        << std::setw(32) << description
        << std::setw(10) << changeID
        << std::setw(12) << lastUpdate
        << std::setw(11) << status
        << std::setw(10) << priority
        << std::setw(9) << releaseID << std::endl;
}
/*
Print the attribute details of the Change object to the console.
No noticeable algorithm or data structure used.
--------------------------------------------------------------------*/
// Accessor methods for Change class attributes
const char* Change::getChangeID() const {
    return changeID;
}
/*
Get the changeID of a Change object.
No noticeable algorithm or data structure used.
--------------------------------------------------------------------*/

const char *Change::change_displayProductName() const {
    return productName;
}
/*
Print the productName of the Change object to the console.
No noticeable algorithm or data structure used.
--------------------------------------------------------------------*/
const char *Change::change_displayDesc() const {
    return description;
}

char Change::change_displayStatus() const {
    return status;
}
/*
Print the status of the Change object to the console.
No noticeable algorithm or data structure used.
--------------------------------------------------------------------*/
char Change::change_displayPriority() const {
    return priority;
}
/*
Print the priority of the Change object to the console.
No noticeable algorithm or data structure used.
--------------------------------------------------------------------*/
const char *Change::change_displayRelID() const {
    return releaseID;
}
/*
Print the releaseID of the Change object to the console.
No noticeable algorithm or data structure used.
--------------------------------------------------------------------*/
// CreateChange function to create a new Change object
Change CreateChange(const char* description, const char& status, const char& priority,
                    const char* lastUpdate, const char* releaseID, const char* changeID) {
    // Validate change data before creating a new Change object
    if (ValidateChange(description, status, priority, lastUpdate, releaseID) == 1) {
        return Change("", description, status, priority, releaseID, lastUpdate, changeID);
    } else {
        throw std::runtime_error("Could not create a new change!");
    }
}
/*
Create new Change object and also validates it.
No noticeable algorithm or data structure used.
--------------------------------------------------------------------*/
// ValidateChange function to validate change data
int ValidateChange(const char* description, const char& status, const char& priority,
                   const char* lastUpdate, const char* releaseID) {
    // Check each attribute for validity
    if (strlen(description) == 0 || strlen(description) > 30) {
        std::cout << "Invalid description length" << std::endl;
        return -1;
    }

    if (status != '-' && status != 'X' && status != 'P') {
        std::cout << "Invalid status" << std::endl;
        return -1;
    }

    if (priority < '1' || priority > '5') {
        std::cout << "Invalid priority" << std::endl;
        return -1;
    }

    if (strlen(lastUpdate) != 10) {
        std::cout << "Invalid lastUpdate format" << std::endl;
        return -1;
    }

    if (strlen(releaseID) > 8) {
        std::cout << "Invalid releaseID" << std::endl;
        return -1;
    }

    // Check for duplicate change in the file
    std::ifstream file( FILENAMES[1], std::ios::binary);
    if (!file) {
        std::cerr << "Error: Could not open file for reading" << std::endl;
        return -1;
    }

    // This part already gets done in complaint.cpp
    Change currentChange;
    while (file.read(reinterpret_cast<char*>(&currentChange), sizeof(Change))) {
        if (/*(trcmp(currentChange.change_displayRelID(), releaseID) == 0) && */(strcmp(currentChange.change_displayDesc(), description) == 0)) {
            std::cout << "Change already exists" << std::endl;
            file.close();
            return 0;
        }
    }

    file.close();
    std::cout << "Change is valid!" << std::endl;
    return 1;
}
/*
Validates that the Change object attributes are acceptable and makes sure no duplicate Change records exists.
A linear search algorithm is used to iterate through the Change records.
--------------------------------------------------------------------*/
void UpdateLatestChange(const char* description, const char& status, const char& priority,
                        const char* releaseID, const char* lastUpdate) {
    // Implementation depends on how you want to identify the latest change
    // This is a placeholder implementation
    std::cout << "UpdateLatestChange: Not implemented" << std::endl;
}

// CreateChangesReport function to create a report of all changes
int CreateChangesReport() {
    std::ifstream file( FILENAMES[1], std::ios::binary);
    if (!file) {
        std::cerr << "Error: Could not open file for reading" << std::endl;
        return -1;
    }

    Change change;
    int count = 0;
    while (file.read(reinterpret_cast<char*>(&change), sizeof(Change))) {
        change.DisplayDetails(std::cout);
        count++;
        if (count % 10 == 0) {
            char choice;
            std::cout << "Press 'N' for next 10 changes, '0' to exit: ";
            std::cin >> choice;
            if (choice == '0') break;
        }
    }
    file.close();
    return count;
}

// CreateAnticipatedChangesProduct function to create a report of anticipated changes for a product
void CreateAnticipatedChangesProduct(const char* releaseID) {
    std::ifstream file( FILENAMES[1], std::ios::binary);
    if (!file) {
        std::cerr << "Error: Could not open file for reading" << std::endl;
        return;
    }

    Change change;
    while (file.read(reinterpret_cast<char*>(&change), sizeof(Change))) {
        if (strcmp(change.change_displayRelID(), releaseID) == 0) {
            change.DisplayDetails(std::cout);
        }
    }

    file.close();
}

// void UpdateLatestChange(const char *description, const char &status, const char &priority, const char *releaseID, const char *lastUpdate){
//     Change lastChange = readRecord<Change>(FILENAMES[1], CHANGEFILEPOINTER);
//     char *latestChangeID = lastChange.getChangeID();
//     Change newChange(description, status, priority, releaseID, lastUpdate, latestChangeID);
//     updateRecord<Change>(FILENAMES[1], CHANGEFILEPOINTER, newChange, latestChangeID);
// }


// CreateUsersInformedOnUpdateReport function to create a report of users to be informed about an update on a change
void CreateUsersInformedOnUpdateReport(const char* changeID) {
    if (strlen(changeID) != 6 || changeID[0] != '1') {
        std::cerr << "Invalid changeID format. It should be 5 digits starting with 1." << std::endl;
        return;
    }

    // Find the Change object with given changeID
    std::ifstream changeFile( FILENAMES[1], std::ios::binary);
    if (!changeFile) {
        std::cerr << "Error: Could not open Changes file." << std::endl;
        return;
    }

    Change change;
    bool changeFound = false;
    while (changeFile.read(reinterpret_cast<char*>(&change), sizeof(Change))) {
        if (strcmp(change.getChangeID(), changeID) == 0) {
            changeFound = true;
            break;
        }
    }
    changeFile.close();

    if (!changeFound) {
        std::cout << "No Change found with ID: " << changeID << std::endl;
        return;
    }

    // Find all Complaints associated with this Change
    std::ifstream complaintFile( FILENAMES[2], std::ios::binary);
    if (!complaintFile) {
        std::cerr << "Error: Could not open Complaints file." << std::endl;
        return;
    }

    std::set<std::string> uniqueCustomerIDs;
    Complaint complaint;
    while (complaintFile.read(reinterpret_cast<char*>(&complaint), sizeof(Complaint))) {
        if (strcmp(complaint.getChangeID(), changeID) == 0) {
            uniqueCustomerIDs.insert(complaint.getCustID());
        }
    }
    complaintFile.close();

    if (uniqueCustomerIDs.empty()) {
        std::cout << "No customers found for Change ID: " << changeID << std::endl;
        return;
    }

    // Find and display Customer details associated with the Complaints
    std::ifstream customerFile( FILENAMES[0], std::ios::binary);
    if (!customerFile) {
        std::cerr << "Error: Could not open Customers file." << std::endl;
        return;
    }

    std::cout << "Customers to be informed about Change ID " << changeID << ":" << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    
    Customer customer;
    int count = 0;
    while (customerFile.read(reinterpret_cast<char*>(&customer), sizeof(Customer))) {
        if (uniqueCustomerIDs.find(customer.getCustID()) != uniqueCustomerIDs.end()) {
            customer.DisplayDetails(std::cout);
            count++;
        }
    }
    customerFile.close();

    std::cout << std::string(50, '-') << std::endl;
    std::cout << "Total customers to be informed: " << count << std::endl;
}

// CommitChange function to commit a Change object to file
void CommitChange(const Change& change, std::streampos& startPos, const std::string& FILENAME) {
    std::ofstream file( FILENAME, std::ios::binary | std::ios::in | std::ios::out);
    if (!file) {
        throw std::runtime_error("Could not open file for writing");
    }
    file.seekp(startPos);
    file.write(reinterpret_cast<const char*>(&change), sizeof(Change));
    startPos = file.tellp();
}
/*
Writes a Change object to a specified file at a given position.
Uses the unsorted records data structure to add the Change object.
--------------------------------------------------------------------*/
// GetChangeDetails function to retrieve Change details from file
Change GetChangeDetails(std::streampos startPos, const std::string& FILENAME) {
    std::ifstream file( FILENAMES[1], std::ios::binary);
    if (!file) {
        throw std::runtime_error("Could not open file for reading");
    }
    file.seekg(startPos);
    Change change;
    if (!file.read(reinterpret_cast<char*>(&change), sizeof(Change))) {
        throw std::runtime_error("FileReadFailed: There was an error in reading the file.");
    }
    return change;
}
/*
Reads a Change object from a specified file at a given position and returns it.
Uses the unsorted records data structure to read the Change object.
--------------------------------------------------------------------*/
int InitChange(){
    filesystem::create_directory(DIRECTORY);
    if (!filesystem::exists( FILENAMES[1]))
    {
        ofstream file( FILENAMES[1], ios::binary);
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
