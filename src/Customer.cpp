/* Customer.cpp
REVISION HISTORY:
Rev. 1 - 24/07/17 Original by Sanchit Jain
----------------------------------------------------------------------
This module, Customer.cpp, implements the Customer class and associated functions.
----------------------------------------------------------------------*/

#include "../include/Customer.hpp"

/*
Default constructor for the Customer class
------------------------------------------------------------------------------------*/
Customer::Customer()
{
    custID[0] = '\0';
    name[0] = '\0';
    email[0] = '\0';
    phone[0] = '\0';
}

/*
Parameterized constructor for the Customer class
Create Customer object using attrbibutes provided.
No algorithm or data structure used.
------------------------------------------------------------------------------------*/
Customer::Customer(const char *custID, const char *name, const char *email, const char *phone)
{
    if (custID && *custID)
    {
        safeStrCopy(this->custID, custID, sizeof(this->custID));
    }
    else
    {
        // Assuming IDGenerator returns a char*
        char *generatedID = IDGenerator('1', 10);
        safeStrCopy(this->custID, generatedID, sizeof(this->custID));
        delete[] generatedID;
    }

    safeStrCopy(this->name, name, sizeof(this->name));
    safeStrCopy(this->email, email, sizeof(this->email));
    safeStrCopy(this->phone, phone, sizeof(this->phone));
}


/*
Copy constructor for Customer class
------------------------------------------------------------------------------------*/
Customer::Customer(const Customer &other)
{
    safeStrCopy(this->custID, other.custID, sizeof(this->custID));
    safeStrCopy(this->name, other.name, sizeof(this->name));
    safeStrCopy(this->email, other.email, sizeof(this->email));
    safeStrCopy(this->phone, other.phone, sizeof(this->phone));
}

/*
Destructor for the Customer class
------------------------------------------------------------------------------------*/
Customer::~Customer()
{
    // No dynamic memory to clean up
}

/*
Assign operator overloader for the Customer class
------------------------------------------------------------------------------------*/
Customer &Customer::operator=(const Customer &other)
{
    if (this != &other)
    {
        safeStrCopy(this->custID, other.custID, sizeof(this->custID));
        safeStrCopy(this->name, other.name, sizeof(this->name));
        safeStrCopy(this->email, other.email, sizeof(this->email));
        safeStrCopy(this->phone, other.phone, sizeof(this->phone));
    }
    return *this;
}

/*
Equality operator overloader for the Customer class
Checks if two Customer objects are equal based on custID or email or phone.
No noticeable algorithm or data structure used.
------------------------------------------------------------------------------------*/
bool Customer::operator==(const Customer &other) const
{
    return (strcmp(custID, other.custID) == 0 || strcmp(email, other.email) == 0 || strcmp(phone, other.phone) == 0);
}

/*
Print the attribute details of the Customer object to the console.
No algorithm or data structure used.
--------------------------------------------------------------------*/
void Customer::DisplayDetails(std::ostream &out) const
{
    if (name[0] == '\0' || email[0] == '\0' || phone[0] == '\0')
    {
        throw InvalidDataException("One or more fields of Customer record has invalid data.");
    }
    else
    {
        out.width(15);
        out << std::left << custID;
        out << std::right << std::setw(10);
        out.width(20);
        out << std::left << name;
        out.width(24);
        out << std::left << email;
        out.width(15);
        out << std::left << phone << std::endl;
    }
}

/*
Create new Customer object and also validates it.
Performs linear search to look for a duplicate Customer in the Customer data file.
--------------------------------------------------------------------*/
Customer CreateCustomer(const char *name, const char *email, const char *phone)
{
    int validationResult = ValidateCustomer(name, email, phone);
    if (validationResult == 1)
    {
        // Generate a new customer ID
        char *generatedID = IDGenerator('0', 10);
        // Create the customer object
        Customer newCustomer(generatedID, name, email, phone);
        // Clean up the generated ID
        delete[] generatedID;

        return newCustomer;
    }
    else if (validationResult == 0)
    {
        throw DuplicateRecordException("FailedToCreateCustomer: Customer with same email or phone already exists!");
    }
    else
    {
        throw InvalidDataException("Invalid name, email, or phone for Customer record.");
    }
}

/*
Writes a Customer object to a specified file at a given position.
Uses the unsorted records data structure to add the Complaint object.
--------------------------------------------------------------------*/
void CommitCustomer(const Customer &customer, std::streampos &startPos, const std::string &FILENAME)
{
    std::ofstream file(FILENAME, std::ios::binary | std::ios::in | std::ios::out);
    if (!file)
    {
        throw FileException("Could not open file 'Customers.bin' for writing when adding a Customer record to the file.");
    }
    file.seekp(0, std::ios::end);
    startPos = file.tellp();
    file.write(reinterpret_cast<const char *>(&customer), sizeof(Customer));
    startPos = file.tellp();
}

/*
Reads a Customer object from a specified file at a given position and returns it.
Uses the unsorted records data structure to read the Customer object.
-------------------------------------------------------------------------------------------*/
Customer GetCustomerDetails(std::streampos &startPos, const std::string &FILENAME)
{
    std::ifstream file(FILENAME, std::ios::binary);
    if (!file)
    {
        throw FileException("Could not open file 'Customers.bin' for reading a record.");
    }
    file.seekg(startPos);
    Customer customer;
    file.read(reinterpret_cast<char *>(&customer), sizeof(Customer));
    startPos = file.tellg();
    return customer;
}

/*
Displays all Customers object with its attribute information.
Performs linear traversal through the Customer data file to get all Customer objects
-------------------------------------------------------------------------------------------*/
void PrintAllCustomers(const std::string &FILENAME)
{
    std::ifstream file(FILENAME, std::ios::binary);
    if (!file)
    {
        throw FileException("Could not open file 'Customers.bin' for printing records.");
    }

    Customer customer;
    int recordCount = 0;
    int batchSize = 10;
    char input[3];
    int choice = 1;

    std::cout << std::left
              << std::setw(12) << "Customer ID"
              << std::setw(31) << "Name"
              << std::setw(31) << "Email"
              << std::setw(15) << "Phone" << std::endl;
    std::cout << std::string(89, '-') << std::endl;

    while (file.read(reinterpret_cast<char *>(&customer), sizeof(Customer)))
    {
        std::cout << std::left
                  << std::setw(12) << customer.getCustID()
                  << std::setw(31) << customer.getName()
                  << std::setw(31) << customer.getEmail()
                  << std::setw(15) << customer.getPhone() << std::endl;
        recordCount++;

        if (recordCount % batchSize == 0)
        {
            std::cout << std::string(94, '-') << std::endl;
            std::cout << "Displayed 10 records." << std::endl;
            std::cout << "Do you want to view the next 10 customers? (1 for Yes, 0 for No): ";
            std::cin.getline(input, 3);
            choice = atoi(input);

            if (choice == 0)
            {
                break;
            }
            else if (choice)
            {
                std::cout << std::left
                          << std::setw(5) << " "

                          << std::setw(12) << "Customer ID"
                          << std::setw(31) << "Name"
                          << std::setw(31) << "Email"
                          << std::setw(15) << "Phone" << std::endl;
                std::cout << std::string(94, '-') << std::endl;
            }
        }
    }

    std::cout << std::string(94, '-') << std::endl;
    std::cout << "Total records Displayed: " << recordCount << std::endl;

    if (file.eof())
    {
        file.clear(); // Clear EOF flag
    }
    else if (file.fail())
    {
        throw FileException("Could not open file 'Customers.bin' for reading records.");
    }

    file.close();
}

// ValidateCustomer
int ValidateCustomer(const char *name, const char *email, const char *phone)
{
    if (strlen(name) == 0 || strlen(email) == 0 || strlen(phone) == 0)
        return -1;
    if (strlen(name) > 16)
        return -1;
    // Validate email
    const char *atSign = strchr(email, '@');
    if (atSign == nullptr)
        return -1;
    const char *dotSign = strchr(atSign, '.');
    if (dotSign == nullptr)
        return -1;
    if (atSign == email || !isalpha(email[0]))
        return -1;
    if (dotSign == atSign + 1 || dotSign == atSign + 2 || *(dotSign + 1) == '\0')
        return -1;
    for (const char *p = email; p < atSign; ++p)
    {
        if (!isalnum(*p) && *p != '.' && *p != '-' && *p != '_')
            return -1;
    }
    for (const char *p = atSign + 1; p < dotSign; ++p)
    {
        if (!isalnum(*p) && *p != '-' && *p != '_')
            return -1;
    }

    // Validate phone number [1]6041231234
    if ((strlen(phone) == 11 && phone[0] == '1') || (strlen(phone) == 10 && isdigit(phone[0])))
    {

        for (int i = 0; i < int(strlen(phone)); i++)
        {
            if (!isdigit(phone[i]))
                return -1;
        }
    }
    else
    {
        return -1;
    }

    // Check if record already exists
    std::ifstream file(FILENAMES[0], std::ios::binary);
    if (!file)
    {
        throw FileException("Could not open file 'Customers.bin' for reading records during validation.");
    }

    Customer temp;
    while (file.read(reinterpret_cast<char *>(&temp), sizeof(Customer)))
    {
        // read through the file
        if (strcmp(temp.getEmail(), email) == 0 || strcmp(temp.getPhone(), phone) == 0)
        {
            throw DuplicateRecordException("Duplicate Customer record found.");
        }
    }

    std::cout << "Validation of data for 'Customer' record succeeded!" << std::endl;
    return 1;
}

/*
Validates that the Customer object attributes are acceptable and makes sure no duplicate Customer records exists.
A linear search algorithm is used to iterate through the Customer records.
--------------------------------------------------------------------*/
bool checkDup(const char *otherCustID)
{
    std::ifstream file(FILENAMES[0], std::ios::binary);
    if (!file)
    {
        throw FileException("Could not open file 'Customers.bin' for checking duplicate customer ID.");
    }
    Customer temp;
    while (file.read(reinterpret_cast<char *>(&temp), sizeof(Customer)))
    {
        if (strcmp(temp.getCustID(), otherCustID) == 0)
        {
            return 1;
        }
    }
    return 0;
}

/*
Initialization for Customer class.
Creates data file for storing Customer objects and its file descriptor if they do not exists.
---------------------------------------------------------------------*/
int InitCustomer()
{
    std::filesystem::create_directory(DIRECTORY);
    if (!std::filesystem::exists(FILENAMES[0]))
    {
        std::ofstream file(FILENAMES[0], std::ios::binary);
        if (!file)
        {
            throw FileException("Startup failed while creating 'Customers.bin' file.");
        }
        else
        {
            file.close();
            return 1;
        }
    }
    return 0;
}
