/* Main.cpp
REVISION HISTORY:
Rev. 1 - 24/07/10 Original by Nicholas Susanto
----------------------------------------------------------------------
This CPP file called Complaint.cpp handles the complaints of the program.
--------------------------------------------------------------------*/

#include "Complaint.hpp"
#include "Change.hpp"
#include "Globals.hpp"
#include "Product.hpp"
// #include "drivers.cpp"
#include <cstring>
#include <iostream>

Complaint::Complaint()
{
    memset(complaintID, 0, sizeof(complaintID));
    memset(description, 0, sizeof(description));
    memset(dateOfComplaint, 0, sizeof(dateOfComplaint));
    memset(changeID, 0, sizeof(changeID));
    memset(releaseID, 0, sizeof(releaseID));
    memset(custID, 0, sizeof(custID));
}

Complaint::Complaint(const char *complaintID, const char *description, const char *dateOfComplaint, const char *changeID,
                     const char *releaseID, const char *custID)
{
    if (strlen(complaintID) != 0)
    {
        safeStrCopy(this->complaintID, complaintID, sizeof(this->complaintID));
    }
    else
    {
        // Assuming IDGenerator returns a char*
        char *generatedID = IDGenerator('2', 7);
        safeStrCopy(this->complaintID, generatedID, sizeof(this->complaintID));
        delete[] generatedID;
    }

    safeStrCopy(this->description, description, sizeof(this->description));
    safeStrCopy(this->dateOfComplaint, dateOfComplaint, sizeof(this->dateOfComplaint));
    safeStrCopy(this->changeID, changeID, sizeof(this->changeID));
    safeStrCopy(this->releaseID, releaseID, sizeof(this->releaseID));
    safeStrCopy(this->custID, custID, sizeof(this->custID));
}
/*
Create Complaint object using attrbibutes provided. 
No noticeable algorithm or data structure used.
--------------------------------------------------------------------*/
Complaint::Complaint(const Complaint &other)
{
    *this = other;
}

Complaint &Complaint::operator=(const Complaint &other)
{
    if (this != &other)
    {
        if (other.complaintID != "" || other.complaintID != nullptr)
        
        {
            safeStrCopy(complaintID, other.complaintID, sizeof(this->complaintID));
        }
        else
        {
            // Assuming IDGenerator returns a char*

            char *generatedID = IDGenerator('1', 7);
            safeStrCopy(complaintID, generatedID, sizeof(this->complaintID));
            delete[] generatedID;
        }
        safeStrCopy(description, other.description, sizeof(description));
        safeStrCopy(dateOfComplaint, other.dateOfComplaint, sizeof(dateOfComplaint));
        safeStrCopy(changeID, other.changeID, sizeof(changeID));
        safeStrCopy(releaseID, other.releaseID, sizeof(releaseID));
        safeStrCopy(custID, other.custID, sizeof(custID));
    }
    return *this;
}

bool Complaint::operator==(const Complaint &other) const
{
    return (strcmp(complaintID, other.complaintID) == 0);
}
/* Checks if two Complaint objects are equal based on complaintID or description or dateOfComplaint. 
No noticeable algorithm or data structure used.
--------------------------------------------------------------------*/

Complaint::~Complaint()
{
    // No dynamic allocation, so nothing to delete
}

void Complaint::DisplayDetails(std::ostream &out) const
{
    out << std::left
        << std::setw(10) << complaintID
        << std::setw(31) << description
        << std::setw(12) << dateOfComplaint
        << std::setw(10) << changeID
        << std::setw(9) << releaseID
        << std::setw(11) << custID << std::endl;
}
/*
Print the attribute details of the Complaint object to the console.
No noticeable algorithm or data structure used.
--------------------------------------------------------------------*/
// char *Complaint::getCustID() const{
//     return custID;
// }

/*
Get the custID of a Complaint object.
No noticeable algorithm or data structure used.
--------------------------------------------------------------------*/
int ValidateComplaint(const char *description, const char *dateOfComplaint, const char *releaseID, const char *custID)
{
    if (!checkDup(custID)){
        cout << "Customer doesn't exist." << endl;
        return -1;
    }
    if (!checkDupProduct(releaseID)){
        cout << "Product doesn't exist." << endl;
        return -1;
    }
    // Validate description
    if (strlen(description) == 0 || strlen(description) > 30)
    {
        std::cout << "Invalid description length" << std::endl;
        return -1;
    }

    // Validate dateOfComplaint
    if (strlen(dateOfComplaint) != 10)
    {
        std::cout << "Invalid date format" << std::endl;
        return -1;
    }
    if (dateOfComplaint[4] != '-' || dateOfComplaint[7] != '-')
    {
        std::cout << "Invalid date separator" << std::endl;
        return -1;
    }
    int year = (dateOfComplaint[0] - '0') * 1000 + (dateOfComplaint[1] - '0') * 100 + (dateOfComplaint[2] - '0') * 10 + (dateOfComplaint[3] - '0');
    int month = (dateOfComplaint[5] - '0') * 10 + (dateOfComplaint[6] - '0');
    int day = (dateOfComplaint[8] - '0') * 10 + (dateOfComplaint[9] - '0');
    if (year < 2024 || year > 2099 || month < 1 || month > 12 || day < 1 || day > 31)
    {
        std::cout << "Invalid date values" << std::endl;
        return -1;
    }

    // Validate releaseID
    if (strlen(releaseID) > 8 && strlen(releaseID) <= 0)
    {
        std::cout << "Invalid releaseID" << std::endl;
        return -1;
    }

    // Validate custID: TODO need to check if customer exists
    if (strlen(custID) != 9)
    {
        std::cout << "Invalid custID" << std::endl;
        return -1;
    }


    // Check for duplicate complaint
    std::ifstream file( FILENAMES[2], std::ios::binary);
    if (!file)
    {
        std::cerr << "Error: Could not open file for reading" << std::endl;
        return -1;
    }
    
    Complaint currentComplaint;
    while (file.read(reinterpret_cast<char *>(&currentComplaint), sizeof(Complaint)))
    {
        if (strcmp(currentComplaint.getDescription(), description) == 0 &&
            strcmp(currentComplaint.getDateOfComplaint(), dateOfComplaint) == 0 &&
            strcmp(currentComplaint.getReleaseID(), releaseID) == 0 &&
            strcmp(currentComplaint.getCustID(), custID) == 0)
        {
            std::cout << "Record already exists" << std::endl;
            file.close();
            return 0;
        }
    }

    file.close();
    std::cout << "Record is valid!" << std::endl;
    return 1;
}
/*
Validates that the Complaint object attributes are acceptable and makes sure no duplicate Complaint records exists.
A linear search algorithm is used to iterate through the Complaint records.
--------------------------------------------------------------------*/
Complaint CreateComplaint(const char *description, const char *dateOfComplaint,
                          const char *releaseID, const char *custID, const char* productName)
{
    cout << "Date is: " << dateOfComplaint << endl;
    if (ValidateComplaint(description, dateOfComplaint, releaseID, custID) != 1)
    {
        throw std::runtime_error("Invalid complaint data");
    }
    // Check if a matching Change record exists
    bool changeExists = false;
    std::ifstream changeFile( FILENAMES[1], std::ios::binary);
    Change change;
    if (changeFile)
    {
        while (changeFile.read(reinterpret_cast<char *>(&change), sizeof(Change)))
        {
            if (strcmp(change.change_displayRelID(), releaseID) == 0 &&
                strcmp(change.change_displayDesc(), description) == 0)
            {
                changeExists = true;
                break;
            }
        }
        changeFile.close();
    }

    // Create a new Change if no matching record was found
    if (!changeExists)
    {
        char status = '-';   // Assuming '-' is the default status for a new change
        char priority = '3'; // Assuming '3' is the default priority
        Change newChange("", description, status, priority, releaseID, dateOfComplaint,productName);

        std::streampos changePos = CHANGEFILEPOINTER;
        CommitChange(newChange, changePos, FILENAMES[1]);

        // Update changeID with the newly created Change's ID
        strcpy(const_cast<char *>(newChange.getChangeID()), newChange.getChangeID());
        change = newChange;
    }
        cout << "ID of change: " << change.getChangeID() << endl;

    // Create and return the new Complaint
    Complaint newComplaint("", description, dateOfComplaint, change.getChangeID(), releaseID, custID);

    std::streampos complaintPos = COMPLAINTFILEPOINTER;
    CommitComplaint(newComplaint, complaintPos, FILENAMES[2]);

    return newComplaint;
}
/*
Create new Complaint object and also validates it.
No noticeable algorithm or data structure used.
--------------------------------------------------------------------*/
void CommitComplaint(const Complaint &complaint, std::streampos &startPos, const std::string &FILENAME)
{
    std::ofstream file( FILENAMES[2], std::ios::binary | std::ios::in | std::ios::out);
    if (!file)
    {
        throw std::runtime_error("Could not open file for writing");
    }
    file.seekp(0, std::ios::end);
    startPos = file.tellp();
    file.write(reinterpret_cast<const char *>(&complaint), sizeof(Complaint));
    startPos = file.tellp();
}
/*
Writes a Complaint object to a specified file at a given position.
Uses the unsorted records data structure to add the Complaint object.
--------------------------------------------------------------------*/
Complaint GetComplaintDetails(std::streampos &startPos, const std::string &FILENAME)
{
    std::ifstream file(FILENAMES[2], std::ios::binary);
    if (!file)
    {
        throw std::runtime_error("Could not open file for reading");
    }
    file.seekg(startPos);
    Complaint complaint;
    file.read(reinterpret_cast<char *>(&complaint), sizeof(Complaint));
    startPos = file.tellg();
    return complaint;
}
/*
Reads a Complaint object from a specified file at a given position and returns it.
Uses the unsorted records data structure to read the Complaint object.
--------------------------------------------------------------------*/
void PrintAllComplaints(const std::string &FILENAME)
{
    std::ifstream file(FILENAMES[2], std::ios::binary);
    if (!file)
    {
        std::cerr << "Error: Could not open file " << FILENAME << " for reading." << std::endl;
        return;
    }

    Complaint complaint;
    int recordCount = 0;

    std::cout << std::left
              << std::setw(10) << "ID"
              << std::setw(31) << "Description"
              << std::setw(12) << "Date"
              << std::setw(10) << "Change"
              << std::setw(9) << "Release"
              << std::setw(11) << "Customer" << std::endl;
    std::cout << std::string(72, '-') << std::endl;

    while (file.read(reinterpret_cast<char *>(&complaint), sizeof(Complaint)))
    {
        complaint.DisplayDetails(std::cout);
        recordCount++;
    }

    std::cout << std::string(72, '-') << std::endl;
    std::cout << "Total records: " << recordCount << std::endl;

    file.close();
}

bool UpdateComplaint(const char *complaintID, const Complaint &updatedComplaint, const std::string &FILENAME)
{
    std::fstream file(FILENAMES[2], std::ios::binary | std::ios::in | std::ios::out);
    if (!file)
    {
        std::cerr << "Error: Could not open file " << FILENAME << " for reading and writing." << std::endl;
        return false;
    }

    Complaint currentComplaint;
    bool found = false;
    std::streampos position;

    while (file.read(reinterpret_cast<char *>(&currentComplaint), sizeof(Complaint)))
    {
        // read Complaints file
        if (strcmp(currentComplaint.getComplaintID(), complaintID) == 0)
        {
            found = true;
            position = file.tellg() - static_cast<std::streampos>(sizeof(Complaint));
            break;
        }
    }

    if (found)
    {
        file.seekp(position);
        file.write(reinterpret_cast<const char *>(&updatedComplaint), sizeof(Complaint));

        if (file.fail())
        {
            std::cerr << "Error: Failed to write updated complaint data." << std::endl;
            file.close();
            return false;
        }

        std::cout << "Complaint record updated successfully." << std::endl;
        file.close();
        return true;
    }
    else
    {
        std::cout << "Complaint with ID " << complaintID << " not found." << std::endl;
        file.close();
        return false;
    }
}

int InitComplaint()
{
    std::filesystem::create_directory(DIRECTORY);
    if (!std::filesystem::exists( FILENAMES[2]))
    {
        std::ofstream file( FILENAMES[2], std::ios::binary);
        if (!file)
        {
            return -1;
        }
        file.close();
        return 1;
    }
    return 0;
}
