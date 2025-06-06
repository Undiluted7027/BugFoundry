/* Main.cpp
REVISION HISTORY:
Rev. 1 - 24/07/10 Original by Nicholas Susanto
----------------------------------------------------------------------
This CPP file called Complaint.cpp handles the complaints of the program.
--------------------------------------------------------------------*/

#include <cstring>
#include <iostream>

#include "../include/Complaint.hpp"

/*
Default constructor for Complaint class
-----------------------------------------------------------------------------------------------------------------------*/
Complaint::Complaint()
{
    memset(complaintID, 0, sizeof(complaintID));
    memset(description, 0, sizeof(description));
    memset(dateOfComplaint, 0, sizeof(dateOfComplaint));
    memset(changeID, 0, sizeof(changeID));
    memset(releaseID, 0, sizeof(releaseID));
    memset(custID, 0, sizeof(custID));
}

/*
Create Complaint object using attrbibutes provided.
No algorithm or data structure used.
-----------------------------------------------------------------------------------------------------------------------*/
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
Copy constructor for Complaint class
-----------------------------------------------------------------------------------------------------------------------*/
Complaint::Complaint(const Complaint &other)
{
    safeStrCopy(this->complaintID, other.complaintID, sizeof(this->complaintID));
    safeStrCopy(this->description, other.description, sizeof(this->description));
    safeStrCopy(this->dateOfComplaint, other.dateOfComplaint, sizeof(this->dateOfComplaint));
    safeStrCopy(this->changeID, other.changeID, sizeof(this->changeID));
    safeStrCopy(this->releaseID, other.releaseID, sizeof(this->releaseID));
    safeStrCopy(this->custID, other.custID, sizeof(this->custID));
}

/*
Assign operator overloader for the Complaint class
-----------------------------------------------------------------------------------------------------------------------*/
Complaint &Complaint::operator=(const Complaint &other)
{
    if (this != &other)
    {
        if (strlen(other.complaintID) != 0)
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

/* 
Equality operator overloader for Complaint class.
Checks if two Complaint objects are equal based on complaintID or description or dateOfComplaint.
No algorithm or data structure used.
-----------------------------------------------------------------------------------------------------*/
bool Complaint::operator==(const Complaint &other) const
{
    return (strcmp(complaintID, other.complaintID) == 0);
}

/*
Deconstructor for the Complaint class
-----------------------------------------------------------------------------------------------------*/
Complaint::~Complaint()
{
    // No dynamic allocation, so nothing to delete
}

/*
Print the attribute details of the Complaint object to the console.
No algorithm or data structure used.
-----------------------------------------------------------------------------------------------------*/
void Complaint::DisplayDetails(std::ostream &out) const
{
    out << std::left
        << std::setw(10) << complaintID
        << std::setw(31) << description
        << std::setw(12) << dateOfComplaint
        << std::setw(10) << changeID
        << std::setw(10) << releaseID
        << std::setw(11) << custID << std::endl;
}

// char *Complaint::getCustID() const{
//     return custID;
// }

/*
Validates that the Complaint object attributes are acceptable and makes sure no duplicate Complaint records exists.
A linear search algorithm is used to iterate through the Complaint records.
---------------------------------------------------------------------------------------------------------------------*/
int ValidateComplaint(const char *description, const char *dateOfComplaint, const char *releaseID, const char *custID)
{
    if (strlen(custID) != 9)
    {
        throw InvalidDataException("Customer ID field can only be of 9 characters at max.");
    }
    if (!checkDup(custID))
    {
        throw NoRecordFound("No record found matching the customer ID: " + std::string(custID));
    }
    if (!checkDupProduct(releaseID))
    {
        throw NoRecordFound("No record found matching the releaseID: " + std::string(releaseID));
    }
    // Validate description
    if (strlen(description) == 0 || strlen(description) > 30)
    {
        throw InvalidDataException("Description field can be of 30 characters at max.");
    }

    // Validate dateOfComplaint
    if (strlen(dateOfComplaint) != 10)
    {
        throw InvalidDataException("DateOfComplaint field can only have value in the format of YYYY-MM-DD.");
    }
    if (dateOfComplaint[4] != '-' || dateOfComplaint[7] != '-')
    {
        throw InvalidDataException("DateOfComplaint field can only have value in the format of YYYY-MM-DD.");
    }
    int year = (dateOfComplaint[0] - '0') * 1000 + (dateOfComplaint[1] - '0') * 100 + (dateOfComplaint[2] - '0') * 10 + (dateOfComplaint[3] - '0');
    int month = (dateOfComplaint[5] - '0') * 10 + (dateOfComplaint[6] - '0');
    int day = (dateOfComplaint[8] - '0') * 10 + (dateOfComplaint[9] - '0');
    if (year < 2024 || year > 2099 || month < 1 || month > 12 || day < 1 || day > 31)
    {
        throw InvalidDataException("DateOfComplaint field can only have value in the format of YYYY-MM-DD.");
    }

    if ((year % 4 != 0 && month == 02 && day > 30) || (year % 4 == 0 &&month == 2 && day > 29)){
        throw InvalidDataException("Invalid date");
    }
    if (day > 30){
        switch (month){
            case 4:
            case 6:
            case 9:
            case 11:
                throw InvalidDataException("Invalid date");
        }
    }

    // Validate releaseID
    if (strlen(releaseID) > 8 && strlen(releaseID) <= 0)
    {
        throw InvalidDataException("ReleaseID field can be of 8 characters at max.");
    }

    // Validate custID: TODO need to check if customer exists

    // Check for duplicate complaint
    std::ifstream file(FILENAMES[2], std::ios::binary);
    if (!file)
    {
        throw FileException("Could not open file 'Complaints.bin' for reading during validation.");
    }

    Complaint currentComplaint;
    while (file.read(reinterpret_cast<char *>(&currentComplaint), sizeof(Complaint)))
    {
        if (strcmp(currentComplaint.getDescription(), description) == 0 &&
            strcmp(currentComplaint.getDateOfComplaint(), dateOfComplaint) == 0 &&
            strcmp(currentComplaint.getReleaseID(), releaseID) == 0 &&
            strcmp(currentComplaint.getCustID(), custID) == 0)
        {
            throw DuplicateRecordException("Duplicate Complaint record found.");
            break;
        }
    }

    file.close();
    std::cout << std::endl << "Validation of data for 'Complaint' record succeeded!" << std::endl;
    return 1;
}

/*
Create new Complaint object and also validates it.
No noticeable algorithm or data structure used.
--------------------------------------------------------------------*/
Complaint CreateComplaint(const char *description, const char *dateOfComplaint,
                          const char *releaseID, const char *custID, const char *productName)
{
    ValidateComplaint(description, dateOfComplaint, releaseID, custID);
    bool changeExists = false;
    std::ifstream changeFile(FILENAMES[1], std::ios::binary);

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
        Change newChange("", description, status, priority, releaseID, dateOfComplaint, productName);

        std::streampos changePos = CHANGEFILEPOINTER;
        CommitChange(newChange, changePos, FILENAMES[1]);

        // Update changeID with the newly created Change's ID
        strcpy(const_cast<char *>(newChange.getChangeID()), newChange.getChangeID());
        change = newChange;
        Complaint newComplaint("", description, dateOfComplaint, change.getChangeID(), releaseID, custID);

        std::streampos complaintPos = COMPLAINTFILEPOINTER;
        CommitComplaint(newComplaint, complaintPos, FILENAMES[2]);

        return newComplaint;
    }
    return Complaint();
}

/*
Writes a Complaint object to a specified file at a given position.
Uses the unsorted records data structure to add the Complaint object.
-------------------------------------------------------------------------------------------*/
void CommitComplaint(const Complaint &complaint, std::streampos &startPos, const std::string &FILENAME)
{
    std::ofstream file(FILENAMES[2], std::ios::binary | std::ios::in | std::ios::out);
    if (!file)
    {
        throw FileException("Could not open file 'Complaints.bin' for writing when adding a Complaint record to the file.");
    }
    file.seekp(0, std::ios::end);
    startPos = file.tellp();
    file.write(reinterpret_cast<const char *>(&complaint), sizeof(Complaint));
    startPos = file.tellp();
}

/*
Reads a Complaint object from a specified file at a given position and returns it.
Uses the unsorted records data structure to read the Complaint object.
------------------------------------------------------------------------------------------*/
Complaint GetComplaintDetails(std::streampos & startPos, const std::string &FILENAME)
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
Displays all Complaints objects with their attributes information.
Uses the unsorted records data structure to read the Complaint object.
------------------------------------------------------------------------------------------*/
void PrintAllComplaints(const std::string &FILENAME)
{
    std::ifstream file(FILENAMES[2], std::ios::binary);
    if (!file)
    {
        throw FileException("Could not open file 'Complaints.bin' during reading.");
    }

    Complaint complaint;
    int recordCount = 0;
    int batchSize = 10;
    char input[3];
    int choice = 1;

    std::cout << std::left
            << std::setw(6) << " "
            << std::setw(10) << "ID"
            << std::setw(31) << "Description"
            << std::setw(12) << "Date"
            << std::setw(10) << "Change"
            << std::setw(10) << "Release"
            << std::setw(11) << "Customer" << std::endl;
    std::cout << std::string(77, '-') << std::endl;

    while (file.read(reinterpret_cast<char *>(&complaint), sizeof(Complaint)))
    {
            std::cout << std::setw(6) << recordCount + 1 << " ";
        complaint.DisplayDetails(std::cout);
        recordCount++;

        if (recordCount % batchSize == 0 && recordCount > 0)
        {
            std::cout << std::string(72, '-') << std::endl;
            std::cout << "Displayed 10 records." << std::endl;
            std::cout << "Do you want to view the next 10 complaints? (1 for Yes, 0 for No): ";
            std::cin.getline(input, 3);
            choice = atoi(input);

            if (choice == 0)
            {
                break;
            }

            std::cout << std::left
                    << std::setw(10) << "ID"
                    << std::setw(31) << "Description"
                    << std::setw(12) << "Date"
                    << std::setw(10) << "Change"
                    << std::setw(10) << "Release"
                    << std::setw(11) << "Customer" << std::endl;
            std::cout << std::string(77, '-') << std::endl;
        }
    }

    std::cout << std::string(77, '-') << std::endl;
    std::cout << "Total Records Displayed: " << recordCount + 1 << std::endl;

    if (file.eof())
    {
        file.clear(); // Clear EOF flag
    }
    else if (file.fail())
    {
        throw FileException("Could not read file 'Complaints.bin' during printing.");
    }

    file.close();
}

/*
Updates the attribute information for a specific Complaint object
---------------------------------------------------------------------------------------------------------------------*/
bool UpdateComplaint(const char *complaintID, const Complaint &updatedComplaint, const std::string &FILENAME)
{
    std::fstream file(FILENAMES[2], std::ios::binary | std::ios::in | std::ios::out);
    if (!file)
    {
        throw FileException("Could not open file 'Complaints.bin' for reading when updating a change.");
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
            throw FileException("Could not open file 'Complaints.bin' for writing when updating a Change record in the file.");
            file.close();
            return false;
        }

        std::cout << "Complaint record updated successfully." << std::endl;
        file.close();
        return true;
    }
    else
    {
        throw NoRecordFound("No record found matching the complaintID: " + std::string(complaintID));
        file.close();
        return false;
    }
}

/*
Initialization for Complaint class.
Creates the data file and its file descriptor if they haven't been initialized before
--------------------------------------------------------------------------------------------------------*/
int InitComplaint()
{
    std::filesystem::create_directory(DIRECTORY);
    if (!std::filesystem::exists(FILENAMES[2]))
    {
        std::ofstream file(FILENAMES[2], std::ios::binary);
        if (!file)
        {
            throw FileException("Startup failed while creating 'Complaints.bin' file.");
        }
        file.close();
        return 1;
    }
    return 0;
}