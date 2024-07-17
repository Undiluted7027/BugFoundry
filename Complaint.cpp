/* Main.cpp
REVISION HISTORY:
Rev. 1 - 24/07/10 Original by Nicholas Susanto
----------------------------------------------------------------------
This CPP file called Complaint.cpp handles the complaints of the program.
--------------------------------------------------------------------*/

#include "Complaint.hpp"
#include "Change.hpp"
#include "Globals.hpp"
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

Complaint::~Complaint()
{
    // No dynamic allocation, so nothing to delete
}

void Complaint::DisplayDetails(std::ostream &out) const
{
    out << std::left
        << std::setw(10) << complaintID
        << std::setw(31) << description
        << std::setw(9) << dateOfComplaint
        << std::setw(10) << changeID
        << std::setw(9) << releaseID
        << std::setw(11) << custID << std::endl;
}

int ValidateComplaint(const char *description, const char *dateOfComplaint, const char *changeID, const char *releaseID, const char *custID)
{
    // Validate description
    if (strlen(description) == 0 || strlen(description) > 30)
    {
        std::cout << "Invalid description length" << std::endl;
        return -1;
    }

    // Validate dateOfComplaint
    if (strlen(dateOfComplaint) != 8)
    {
        std::cout << "Invalid date format" << std::endl;
        return -1;
    }
    if (dateOfComplaint[2] != '-' || dateOfComplaint[5] != '-')
    {
        std::cout << "Invalid date separator" << std::endl;
        return -1;
    }
    int year = (dateOfComplaint[0] - '0') * 10 + (dateOfComplaint[1] - '0');
    int month = (dateOfComplaint[3] - '0') * 10 + (dateOfComplaint[4] - '0');
    int day = (dateOfComplaint[6] - '0') * 10 + (dateOfComplaint[7] - '0');
    if (year < 24 || year > 99 || month < 1 || month > 12 || day < 1 || day > 31)
    {
        std::cout << "Invalid date values" << std::endl;
        return -1;
    }

    // Validate changeID
    if (strlen(changeID) != 5 || changeID[0] != '1')
    {
        std::cout << "Invalid changeID" << std::endl;
        return -1;
    }

    // Validate releaseID
    if (strlen(releaseID) != 8)
    {
        std::cout << "Invalid releaseID" << std::endl;
        return -1;
    }

    // Validate custID
    if (strlen(custID) != 10)
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
            strcmp(currentComplaint.getChangeID(), changeID) == 0 &&
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

Complaint CreateComplaint(const char *description, const char *dateOfComplaint,
                          const char *changeID, const char *releaseID, const char *custID)
{
    if (ValidateComplaint(description, dateOfComplaint, changeID, releaseID, custID) != 1)
    {
        throw std::runtime_error("Invalid complaint data");
    }

    // Check if a matching Change record exists
    bool changeExists = false;
    std::ifstream changeFile( FILENAMES[1], std::ios::binary);
    if (changeFile)
    {
        Change change;
        while (changeFile.read(reinterpret_cast<char *>(&change), sizeof(Change)))
        {
            if (strcmp(change.change_displayRelID(), releaseID) == 0 &&
                strcmp(change.change_displayDesc(), description) == 0)
            {
                changeExists = true;
                changeID = change.getChangeID();
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
        Change newChange("", description, status, priority, releaseID);

        std::streampos changePos = CHANGEFILEPOINTER;
        CommitChange(newChange, changePos, FILENAMES[1]);

        // Update changeID with the newly created Change's ID
        strcpy(const_cast<char *>(changeID), newChange.getChangeID());
    }

    // Create and return the new Complaint
    Complaint newComplaint("", description, dateOfComplaint, changeID, releaseID, custID);

    std::streampos complaintPos = COMPLAINTFILEPOINTER;
    CommitComplaint(newComplaint, complaintPos, FILENAMES[2]);

    return newComplaint;
}

void CommitComplaint(const Complaint &complaint, std::streampos &startPos, const std::string &FILENAME)
{
    std::ofstream file( FILENAMES[2], std::ios::binary | std::ios::in | std::ios::out);
    if (!file)
    {
        throw std::runtime_error("Could not open file for writing");
    }
    file.seekp(startPos);
    file.write(reinterpret_cast<const char *>(&complaint), sizeof(Complaint));
    startPos = file.tellp();
}

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
              << std::setw(9) << "Date"
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