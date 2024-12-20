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
<<<<<<< HEAD:Complaint.cpp
/*
Default constructor for Complaint class
No noticeable algorithm or data structure used.
--------------------------------------------------------------------------*/
=======

/*
Create Complaint object using attrbibutes provided.
No algorithm or data structure used.
-----------------------------------------------------------------------------------------------------------------------*/
>>>>>>> pr/64:src/Complaint.cpp
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
        char *generatedID = IDGenerator('2', FILENAMES[2], 7);
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
<<<<<<< HEAD:Complaint.cpp
/*
Copy constructor for Complaint class
No noticeable algorithm or data structure used.
--------------------------------------------------------------------------*/
=======

/*
Assign operator overloader for the Complaint class
-----------------------------------------------------------------------------------------------------------------------*/
>>>>>>> pr/64:src/Complaint.cpp
Complaint &Complaint::operator=(const Complaint &other)
{
    if (this != &other)
    {
<<<<<<< HEAD:Complaint.cpp
        if (other.complaintID[0] != '\0' || other.complaintID != nullptr)

=======
        if (strlen(other.complaintID) != 0)
>>>>>>> pr/64:src/Complaint.cpp
        {
            safeStrCopy(complaintID, other.complaintID, sizeof(this->complaintID));
        }
        else
        {
            // Assuming IDGenerator returns a char*
<<<<<<< HEAD:Complaint.cpp

            char *generatedID = IDGenerator('2', FILENAMES[2], 7);
=======
            char *generatedID = IDGenerator('1', 7);
>>>>>>> pr/64:src/Complaint.cpp
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
<<<<<<< HEAD:Complaint.cpp
/*
Assigning operator overload for Complaint
Assign the other complaint to this complaint.
No noticeable algorithm or data structure used. 
--------------------------------------------------------------------------*/
=======

/* 
Equality operator overloader for Complaint class.
Checks if two Complaint objects are equal based on complaintID or description or dateOfComplaint.
No algorithm or data structure used.
-----------------------------------------------------------------------------------------------------*/
>>>>>>> pr/64:src/Complaint.cpp
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
<<<<<<< HEAD:Complaint.cpp
/*
Default destructor for Complaint class
No noticeable algorithm or data structure used.
--------------------------------------------------------------------------*/
=======

/*
Print the attribute details of the Complaint object to the console.
No algorithm or data structure used.
-----------------------------------------------------------------------------------------------------*/
>>>>>>> pr/64:src/Complaint.cpp
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

    if ((year % 4 != 0 && month == 02 && day > 30) || (year % 4 == 0 && month == 2 && day > 29))
    {
        throw InvalidDataException("ReleaseDate field has invalid YYYY-MM-DD.");
    }
    if (day > 30)
    {
        switch (month)
        {
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
    file.seekg(sizeof(int), std::ios::beg);

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
    std::cout << "Validation of data for 'Complaint' record succeeded!" << std::endl;
    return 1;
}

/*
Create new Complaint object and also validates it.
No noticeable algorithm or data structure used.
--------------------------------------------------------------------*/
Complaint CreateComplaint(const char *description, const char *dateOfComplaint,
                          const char *releaseID, const char *custID, const char *productName)
{
<<<<<<< HEAD:Complaint.cpp

    ValidateComplaint(description, dateOfComplaint, releaseID, custID);
    bool changeExists = false;
    std::ifstream changeFile(FILENAMES[1], std::ios::binary);
    changeFile.seekg(sizeof(int), std::ios::beg);
=======
    ValidateComplaint(description, dateOfComplaint, releaseID, custID);
    bool changeExists = false;
    std::ifstream changeFile(FILENAMES[1], std::ios::binary);
>>>>>>> pr/64:src/Complaint.cpp

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
<<<<<<< HEAD:Complaint.cpp
/*
Create new Complaint object and also validates it.
No noticeable algorithm or data structure used.
--------------------------------------------------------------------*/
void CommitComplaint(const Complaint &complaint, std::streampos &startPos, const std::string &FILENAME)
{
    std::fstream file(FILENAMES[2], std::ios::binary | std::ios::in | std::ios::out);
=======

/*
Writes a Complaint object to a specified file at a given position.
Uses the unsorted records data structure to add the Complaint object.
-------------------------------------------------------------------------------------------*/
void CommitComplaint(const Complaint &complaint, std::streampos &startPos, const std::string &FILENAME)
{
    std::ofstream file(FILENAMES[2], std::ios::binary | std::ios::in | std::ios::out);
>>>>>>> pr/64:src/Complaint.cpp
    if (!file)
    {
        throw FileException("Could not open file 'Complaints.bin' for writing when adding a Complaint record to the file.");
    }
<<<<<<< HEAD:Complaint.cpp
    int recordCount;
    file.read(reinterpret_cast<char *>(&recordCount), sizeof(int));
    file.seekp(0, std::ios::end);
    startPos = file.tellp();
    file.write(reinterpret_cast<const char *>(&complaint), sizeof(Complaint));
    if (file.fail())
    {
        throw FileException("Could not write complaint to 'Complaints.bin'.");
    }
    startPos = file.tellp();
    recordCount++;
    file.seekp(0, std::ios::beg);
    file.write(reinterpret_cast<const char *>(&recordCount), sizeof(int));

    file.close();
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
    startPos += sizeof(int);
=======
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
>>>>>>> pr/64:src/Complaint.cpp
    file.seekg(startPos);
    Complaint complaint;
    file.read(reinterpret_cast<char *>(&complaint), sizeof(Complaint));
    startPos = file.tellg();
    return complaint;
}
<<<<<<< HEAD:Complaint.cpp
/*
Reads a Complaint object from a specified file at a given position and returns it.
Uses the unsorted records data structure to read the Complaint object.
--------------------------------------------------------------------*/
=======

/*
Displays all Complaints objects with their attributes information.
Uses the unsorted records data structure to read the Complaint object.
------------------------------------------------------------------------------------------*/
>>>>>>> pr/64:src/Complaint.cpp
void PrintAllComplaints(const std::string &FILENAME)
{
    std::ifstream file(FILENAMES[2], std::ios::binary);
    if (!file)
    {
        throw FileException("Could not open file 'Complaints.bin' during reading.");
    }
    file.seekg(sizeof(int), std::ios::beg);
    Complaint complaint;
    int recordCount = 0;
    int batchSize = 10;
    char input[3];
    int choice = 1;

    std::cout << std::left
            << std::setw(5) << " "
            << std::setw(10) << "ID"
            << std::setw(31) << "Description"
            << std::setw(12) << "Date"
            << std::setw(10) << "Change"
            << std::setw(9) << "Release"
            << std::setw(11) << "Customer" << std::endl;
    std::cout << std::string(77, '-') << std::endl;

    while (file.read(reinterpret_cast<char *>(&complaint), sizeof(Complaint)))
    {
        std::cout << std::setw(5) << recordCount + 1 << " ";
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
                    << std::setw(9) << "Release"
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
<<<<<<< HEAD:Complaint.cpp
/*
Prints all complaint objects
Uses the unsorted records data structure to read the Complaint object.
--------------------------------------------------------------------------*/
=======

/*
Updates the attribute information for a specific Complaint object
---------------------------------------------------------------------------------------------------------------------*/
>>>>>>> pr/64:src/Complaint.cpp
bool UpdateComplaint(const char *complaintID, const Complaint &updatedComplaint, const std::string &FILENAME)
{
    std::fstream file(FILENAMES[2], std::ios::binary | std::ios::in | std::ios::out);
    if (!file)
    {
        throw FileException("Could not open file 'Complaints.bin' for reading when updating a change.");
        return false;
    }
<<<<<<< HEAD:Complaint.cpp
    file.seekg(sizeof(int), std::ios::beg);
=======

>>>>>>> pr/64:src/Complaint.cpp
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
<<<<<<< HEAD:Complaint.cpp
/*
Update the complaint in file by writing the new complaint over the old complaint.
Uses the unsorted records data structure to check the Complaint object.
--------------------------------------------------------------------------*/
=======

/*
Initialization for Complaint class.
Creates the data file and its file descriptor if they haven't been initialized before
--------------------------------------------------------------------------------------------------------*/
>>>>>>> pr/64:src/Complaint.cpp
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
<<<<<<< HEAD:Complaint.cpp
        int initialCount = 0;
        file.write(reinterpret_cast<const char *>(&initialCount), sizeof(int)); // Reserve space for the record count
=======
>>>>>>> pr/64:src/Complaint.cpp
        file.close();
        return 1;
    }
    return 0;
}
<<<<<<< HEAD:Complaint.cpp
/*
Initializes the complaint module with the complaint file and complaint file pointer
--------------------------------------------------------------------------*/
=======
>>>>>>> pr/64:src/Complaint.cpp
