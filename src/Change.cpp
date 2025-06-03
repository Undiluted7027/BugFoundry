/* Change.cpp
REVISION HISTORY:
Rev. 1 - 24/07/15 Original by Nicholas Susanto
----------------------------------------------------------------------
This CPP file called Changes.cpp handles the changes of the program.
--------------------------------------------------------------------*/

#include <cstring>
#include <iostream>
#include <set>

#include "../include/Change.hpp"

using namespace std;

//--------------------------------------------------------------------------------

/*
Default constructor for Change class
--------------------------------------------------------------------------------*/
Change::Change() : status('-'), priority('1')
{
    memset(changeID, 0, sizeof(changeID));
    memset(description, 0, sizeof(description));
    memset(lastUpdate, 0, sizeof(lastUpdate));
    memset(releaseID, 0, sizeof(releaseID));
    memset(productName, 0, sizeof(productName));
}

/*
Parameterized constructor for Change class
--------------------------------------------------------------------------------*/ 
Change::Change(const char *changeID, const char *description, const char &status, const char &priority,
               const char *releaseID, const char *lastUpdate, const char *productName) 
               : status(status), priority(priority)
{
    // Case where changeID is provided
    if (strlen(changeID) != 0)
    {
        safeStrCopy(this->changeID, changeID, sizeof(this->changeID));
    }
    // Generate a new changeID if not provided
    else
    {
        char *generatedID = IDGenerator('1', 7); // Assuming IDGenerator function is used to generate IDs
        safeStrCopy(this->changeID, generatedID, sizeof(this->changeID));
        delete[] generatedID;
    }

    safeStrCopy(this->description, description, sizeof(this->description));
    safeStrCopy(this->releaseID, releaseID, sizeof(this->releaseID));
    safeStrCopy(this->lastUpdate, lastUpdate, sizeof(this->lastUpdate));
    safeStrCopy(this->productName, productName, sizeof(this->productName));
}

/*
Checks if two Change objects are equal based on changeID or description.
No algorithm or data structure used.
--------------------------------------------------------------------*/
bool Change::operator==(const Change &other) const
{
    return (strcmp(changeID, other.changeID) == 0 || strcmp(description, other.description) == 0);
}

/*
UpdateChange method to update existing change details
--------------------------------------------------------------------*/
void Change::UpdateChange(const char *changeID, const char *description, const char &status,
                          const char &priority, const char *releaseID, const char *lastUpdate)
{
    safeStrCopy(this->changeID, changeID, sizeof(this->changeID));
    safeStrCopy(this->description, description, sizeof(this->description));
    this->status = status;
    this->priority = priority;
    safeStrCopy(this->releaseID, releaseID, sizeof(this->releaseID));
    safeStrCopy(this->lastUpdate, lastUpdate, sizeof(this->lastUpdate));

    // cout << "Updated change class" << endl;
}


/*
DisplayDetails method to display change details
--------------------------------------------------------------------*/
void Change::DisplayDetails(std::ostream &out) const
{
    out << std::left
        << std::setw(10) << changeID
        << std::setw(15) << productName
        << std::setw(32) << description
        << std::setw(12) << lastUpdate
        << std::setw(7) << status
        << std::setw(10) << priority
        << std::setw(32) << releaseID << std::endl;
}

/*
Print the attribute details of all Change objects to the console.
No algorithm or data structure used.
--------------------------------------------------------------------*/
int PrintAllChanges(const std::string &FILENAME)
{
    std::ifstream file(FILENAME, std::ios::binary);
    if (!file)
    {
        throw FileException("Could not open file '" + FILENAME + "' during reading.");
    }
    file.seekg(sizeof(int), std::ios::beg);
    Change change;
    int recordCount = 0;
    int batchSize = 10;
    char input[3];
    int choice = 1;

    std::cout << std::left
              << std::setw(5) << " "
              << std::setw(10) << "ChangeID"
              << std::setw(15) << "Product Name"
              << std::setw(32) << "Description"
              << std::setw(12) << "Last Update"
              << std::setw(7) << "Status"
              << std::setw(10) << "Priority"
              << std::setw(32) << "ReleaseID" << std::endl;
    std::cout << std::string(123, '-') << std::endl;

    while (file.read(reinterpret_cast<char *>(&change), sizeof(change)))
    {
        std::cout << std::setw(5) << recordCount + 1 << " ";

        change.DisplayDetails(std::cout);
        recordCount++;

        if (recordCount % batchSize == 0 && recordCount + 1 > 0)
        {
            std::cout << std::string(118, '-') << std::endl;
            std::cout << "Displayed 10 records." << std::endl;
            std::cout << "Do you want to view the next 10 changes? (1 for Yes, 0 for No): ";
            do
            {
                std::cin.getline(input, 3);
                choice = atoi(input);
            } while (choice != 0 || choice != 1);

            if (choice == 0)
            {
                break;
            }
            else if (choice == 1)
            {
                std::cout << std::endl;
                std::cout << std::left
                          << std::setw(5) << " "
                          << std::setw(10) << "ChangeID"
                          << std::setw(15) << "Product Name"
                          << std::setw(32) << "Description"
                          << std::setw(12) << "Last Update"
                          << std::setw(7) << "Status"
                          << std::setw(10) << "Priority"
                          << std::setw(32) << "ReleaseID" << std::endl;
                std::cout << std::string(123, '-') << std::endl;
            }
        }
    }

    std::cout << std::string(123, '-') << std::endl;
    std::cout << "Total Records Displayed: " << recordCount << std::endl << std::endl;

    if (file.eof())
    {
        file.clear(); // Clear EOF flag
    }
    else if (file.fail())
    {
        throw FileException("Could not read file '" + FILENAME + "' during printing.");
    }

    file.close();
    return recordCount;
}

/*
Accessor methods for Change class attributes.
Gets the changeID of a Change object.
No algorithm or data structure used.
--------------------------------------------------------------------*/
const char *Change::getChangeID() const
{
    if (changeID[0] == 0)
        throw InvalidDataException("ChangeID field is null");
    return changeID;
}

/*
Print the productName of the Change object to the console.
No algorithm or data structure used.
--------------------------------------------------------------------*/
const char *Change::change_displayProductName() const
{
    if (productName[0] == 0)
        throw InvalidDataException("ProductName field is null");
    return productName;
}

/*
Print the description of the Change object to the console.
No algorithm or data structure used.
--------------------------------------------------------------------*/
const char *Change::change_displayDesc() const
{
    if (description[0] == 0)
        throw InvalidDataException("Description field is null");
    return description;
}

/*
Print the status of the Change object to the console.
No algorithm or data structure used.
--------------------------------------------------------------------*/
char Change::change_displayStatus() const
{
    if (status == '\0')
        throw InvalidDataException("Status field is null");
    return status;
}

/*
Print the priority of the Change object to the console.
No algorithm or data structure used.
--------------------------------------------------------------------*/
char Change::change_displayPriority() const
{
    if (priority == '\0')
        throw InvalidDataException("Priority field is null");
    return priority;
}

/*
Print the releaseID of the Change object to the console.
No algorithm or data structure used.
--------------------------------------------------------------------*/
const char *Change::change_displayRelID() const
{
    if (releaseID[0] == 0)
        throw InvalidDataException("ReleaseID field is empty");
    return releaseID;
}

/*
Create new Change object and also validates it.
No -algorithm or data structure used.
--------------------------------------------------------------------*/
Change CreateChange(const char *description, const char &status, const char &priority,
                    const char *lastUpdate, const char *releaseID, const char *changeID)
{
    // Validate change data before creating a new Change object
    ValidateChange(description, status, priority, lastUpdate, releaseID);
    return Change("", description, status, priority, releaseID, lastUpdate, changeID);
}

/*
Validates that the Change object attributes are acceptable and makes sure no duplicate Change records exists.
A linear search algorithm is used to iterate through the Change records.
--------------------------------------------------------------------*/
int ValidateChange(const char *description, const char &status, const char &priority,
                   const char *lastUpdate, const char *releaseID)
{
    // Check each attribute for validity
    if (strlen(description) == 0 || strlen(description) > 30)
    {
        throw InvalidDataException("Description field can be of 30 characters at max and cannot be empty");
    }

    if (status != '-' && status != 'X' && status != 'P')
    {
        throw InvalidDataException("Status field can only have '-' or 'X' or 'P' as a value.");
    }

    if (priority < '1' || priority > '5')
    {
        throw InvalidDataException("Priority field can only have values between 1 and 5.");
    }

    if (strlen(lastUpdate) != 10)
    {
        throw InvalidDataException("LastUpdate field can only have value in the format of YYYY-MM-DD.");
    }

    if (strlen(releaseID) > 8)
    {
        throw InvalidDataException("ReleaseID field can be of 8 characters at max.");
    }

    // Check for duplicate change in the file
    std::ifstream file(FILENAMES[1], std::ios::binary);
    if (!file)
    {
        throw FileException("Could not open file 'Changes.bin' for reading during validation.");
    }

    file.seekg(sizeof(int), std::ios::beg);
    Change currentChange;
    while (file.read(reinterpret_cast<char *>(&currentChange), sizeof(Change)))
    {
        if (strcmp(currentChange.change_displayDesc(), description) == 0)
        {
            throw DuplicateRecordException("Duplicate Change record found.");
            break;
        }
    }

    file.close();
    std::cout << "Validation of data for 'Change' record succeeded!" << std::endl;
    return 1;
}

/*
Creates a report of all changes by displaying a list of Change objects
------------------------------------------------------------------------------------------------*/
int CreateChangesReport()
{
    std::ifstream file(FILENAMES[1], std::ios::binary);
    if (!file)
    {
        throw FileException("Could not open file 'Changes.bin' for reading when creating changes report.");
    }

    return PrintAllChanges(FILENAMES[1]);
}

/*
Creates a report of all changes that are associated with a product with a particular releaseID
by displaying all Changes that are targeted to this releaseID.
------------------------------------------------------------------------------------------------*/
void CreateAnticipatedChangesProduct(const char *releaseID)
{
    std::ifstream file(FILENAMES[1], std::ios::binary);
    if (!file)
    {
        throw FileException("Could not open file 'Changes.bin' for reading when creating anticipated changes for product report.");
    }
    std::cout << std::endl;
    std::cout << std::left
              << std::setw(5) << " "
              << std::setw(10) << "ChangeID"
              << std::setw(15) << "Product Name"
              << std::setw(32) << "Description"
              << std::setw(12) << "Last Update"
              << std::setw(7) << "Status"
              << std::setw(10) << "Priority"
              << std::setw(32) << "ReleaseID" << std::endl;
    std::cout << std::string(123, '-') << std::endl;

    Change change;
    int recordCount = 0;
    int batchSize = 10;
    char input[3];
    int choice = 1;

    while (file.read(reinterpret_cast<char *>(&change), sizeof(Change)))
    {
        if (strcmp(change.change_displayRelID(), releaseID) == 0 && change.change_displayStatus() != 'X')
        {
            std::cout << std::setw(5) << recordCount + 1 << " ";
            change.DisplayDetails(std::cout);
            recordCount++;

            if (recordCount % batchSize == 0 && recordCount + 1 > 0)
            {
                std::cout << std::string(118, '-') << std::endl;
                std::cout << "Displayed 10 records." << std::endl;
                std::cout << "Do you want to view the next 10 changes? (1 for Yes, 0 for No): ";
                do
                {
                    std::cin.getline(input, 3);
                    choice = atoi(input);
                } while (choice != 0 || choice != 1);

                if (choice == 0)
                {
                    break;
                }
                else if (choice == 1)
                {
                    std::cout << std::endl;
                    std::cout << std::left
                              << std::setw(5) << " "
                              << std::setw(10) << "ChangeID"
                              << std::setw(15) << "Product Name"
                              << std::setw(32) << "Description"
                              << std::setw(12) << "Last Update"
                              << std::setw(7) << "Status"
                              << std::setw(10) << "Priority"
                              << std::setw(32) << "ReleaseID/Anticipated ReleaseID" << std::endl;
                    std::cout << std::string(123, '-') << std::endl;
                }
            }
        }
    }

    std::cout << std::string(123, '-') << std::endl;
    std::cout << "Total Records Displayed: " << recordCount << std::endl << std::endl;

    if (file.eof())
    {
        file.clear(); // Clear EOF flag
    }
    else if (file.fail())
    {
        throw FileException("Could not read file 'Changes.bin' during report creation.");
    }

    file.close();
}
/*
CreateAnticipatedChangesProduct displays 10 latest reported change for a specific product
Displays 10 changes at a time. User can make a choice to display the next 10 changes.
--------------------------------------------------------------*/

// void UpdateLatestChange(const char *description, const char &status, const char &priority, const char *releaseID, const char *lastUpdate){
//     Change lastChange = readRecord<Change>(FILENAMES[1], CHANGEFILEPOINTER);
//     char *latestChangeID = lastChange.getChangeID();
//     Change newChange(description, status, priority, releaseID, lastUpdate, latestChangeID);
//     updateRecord<Change>(FILENAMES[1], CHANGEFILEPOINTER, newChange, latestChangeID);
// }

/*
Creates a report of all users who are associated with a particular changeID 
by displaying all users who reported an info regarding this changeID 
------------------------------------------------------------------------------------------------------------------------------*/
void CreateUsersInformedOnUpdateReport(const char *changeID)
{
    if (strlen(changeID) != 6 || changeID[0] != '1')
    {
        throw InvalidDataException("ChangeID must be 6 characters long and start with '1'.");
    }

    // Find the Change object with the given changeID
    std::ifstream changeFile(FILENAMES[1], std::ios::binary);
    if (!changeFile)
    {
        throw FileException("Could not open file 'Changes.bin' for reading.");
    }
    changeFile.seekg(sizeof(int), std::ios::beg);
    Change change;
    bool changeFound = false;
    while (changeFile.read(reinterpret_cast<char *>(&change), sizeof(Change)))
    {
        if (strcmp(change.getChangeID(), changeID) == 0)
        {
            changeFound = true;
            break;
        }
    }
    changeFile.close();

    if (!changeFound)
    {
        throw NoRecordFound("No record found matching the changeID: " + std::string(changeID));
    }

    // Find all Complaints associated with this Change
    std::ifstream complaintFile(FILENAMES[2], std::ios::binary);
    if (!complaintFile)
    {
        throw FileException("Could not open file 'Complaints.bin' for reading.");
    }
    complaintFile.seekg(sizeof(int), std::ios::beg);

    std::set<std::string> uniqueCustomerIDs;
    Complaint complaint;
    while (complaintFile.read(reinterpret_cast<char *>(&complaint), sizeof(Complaint)))
    {
        if (strcmp(complaint.getChangeID(), changeID) == 0)
        {
            uniqueCustomerIDs.insert(complaint.getCustID());
        }
    }
    complaintFile.close();

    if (uniqueCustomerIDs.empty())
    {
        throw NoRecordFound("No customers found relating to the changeID: " + std::string(changeID));
    }

    // Find and display Customer details associated with the Complaints
    std::ifstream customerFile(FILENAMES[0], std::ios::binary);
    if (!customerFile)
    {
        throw FileException("Could not open file 'Customers.bin' for reading.");
    }
    std::cout << std::endl;
    std::cout << "Customers to be informed about Change ID " << changeID << ":" << std::endl;
    std::cout << std::string(91, '-') << std::endl;
    customerFile.seekg(sizeof(int), std::ios::beg);

    Customer customer;
    int count = 0;
    int batchSize = 10;
    char input[3];
    int choice = 1;
    std::cout << std::left
              << std::setw(5) << " "
              << std::setw(15) << "Customer ID"
              << std::right

              << std::setw(10) << "Name"
              << std::setw(24) << "Email"
              << std::right
              << std::setw(5) << " "
              << std::setw(15) << "Phone" << std::endl;
    std::cout << std::string(91, '-') << std::endl;
    while (customerFile.read(reinterpret_cast<char *>(&customer), sizeof(Customer)))
    {
        if (uniqueCustomerIDs.find(customer.getCustID()) != uniqueCustomerIDs.end())
        {
            std::cout << std::setw(5) << count + 1 << " ";

            customer.DisplayDetails(std::cout);
            count++;

            if (count % batchSize == 0 && count + 1 > 0)
            {
                std::cout << std::string(50, '-') << std::endl;
                std::cout << "Displayed 10 records." << std::endl;
                std::cout << "Do you want to view the next 10 customers? (1 for Yes, 0 for No): ";
                do
                {
                    std::cin.getline(input, 3);
                    choice = atoi(input);
                } while (choice != 0 || choice != 1);

                if (choice == 0)
                {
                    break;
                }
                else if (choice == 1)
                {
                    std::cout << std::left
                              << std::setw(5) << " "
                              << std::setw(15) << "Customer ID"
                              << std::right
                              << std::setw(10) << "Name"
                              << std::setw(24) << "Email"
                              << std::right
                              << std::setw(5) << " "
                              << std::setw(15) << "Phone" << std::endl;
                    std::cout << std::string(91, '-') << std::endl;
                }
            }
        }
    }
    customerFile.close();

    std::cout << std::string(91, '-') << std::endl;
    std::cout << "Total customers to be informed: " << count << std::endl << std::endl;
}

/*
Apply the update made to a Change attributes by
overwriting the information on the data file
------------------------------------------------------------------------------------------------------------------------*/
void CommitUpdatedChange(const Change &change, const std::string &FILENAME)
{
    std::fstream file(FILENAME, std::ios::binary | std::ios::in | std::ios::out);
    if (!file)
    {
        throw FileException("Could not open file 'Changes.bin' for writing when updating a Change record in the file.");
    }

    Change temp;
    while (file.read(reinterpret_cast<char *>(&temp), sizeof(Change)))
    {
        if (strcmp(temp.getChangeID(), change.getChangeID()) == 0)
        {
            file.seekp(file.tellg() - static_cast<std::streamoff>(sizeof(Change)));
            file.write(reinterpret_cast<const char *>(&change), sizeof(Change));
            break;
        }
    }
    file.close();
}

/*
Writes a Change object to a specified file at a given position.
Uses the unsorted records data structure to add the Change object.
--------------------------------------------------------------------------------------------------------------------*/
void CommitChange(const Change &change, std::streampos &startPos, const std::string &FILENAME)
{
    std::ofstream file(FILENAME, std::ios::binary | std::ios::in | std::ios::out);
    if (!file)
    {
        throw FileException("Could not open file 'Changes.bin' for writing when adding a Change record to the file.");
    }
    file.seekp(0, std::ios::end);
    startPos = file.tellp();
    file.write(reinterpret_cast<const char *>(&change), sizeof(Change));
    startPos = file.tellp();
}

/*
Reads a Change object from a specified file at a given position and returns it.
Uses the unsorted records data structure to read the Change object.
--------------------------------------------------------------------*/
Change GetChangeDetails(std::streampos startPos, const std::string &FILENAME)
{
    std::ifstream file(FILENAMES[1], std::ios::binary);
    if (!file)
    {
        throw FileException("Could not open file for reading");
    }
    // startPos += sizeof(int);
    file.seekg(startPos);
    Change change;
    if (!file.read(reinterpret_cast<char *>(&change), sizeof(Change)))
    {
        throw NoRecordFound("FileReadFailed: There was an error in reading the file.");
    }
    return change;
}

/* int InitChange() uses the global variables streampos CHANGEFILEPOINTER and FILENAMES[1] 
to check if binary file "Changes.bin" exist in the DIRECTORY to essentially check if the program is being run for the first time. 
If it does, then it returns 0, if it doesn't then the files is created. If file was created successfully, it returns 1 else -1. The function does not fail.
----------------------------------------------------------------------*/
int InitChange()
{
    filesystem::create_directory(DIRECTORY);
    if (!filesystem::exists(FILENAMES[1]))
    {
        ofstream file(FILENAMES[1], ios::binary);
        if (!file)
        {
            throw FileException("Startup failed while creating 'Changes.bin' file.");
        }
        int initialCount = 0;
        file.write(reinterpret_cast<const char*>(&initialCount), sizeof(int)); // Reserve space for the record count

        file.close();
        return 1;
    }
    return 0;
}
