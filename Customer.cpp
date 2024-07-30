/* Customer.cpp
REVISION HISTORY:
Rev. 1 - 24/07/17 Original by Sanchit Jain
----------------------------------------------------------------------
This module, Customer.cpp, implements the Customer class and associated functions.
----------------------------------------------------------------------*/

#include "Customer.hpp"
#include "drivers.cpp"
#include "Globals.cpp"

// Constructor: Default
Customer::Customer() {
    custID[0] = '\0';
    name[0] = '\0';
    email[0] = '\0';
    phone[0] = '\0';
}

// Constructor: Parameterized
Customer::Customer(
    const char* custID,   // in
                          // Customer ID
    const char* name,     // in
                          // Customer name
    const char* email,    // in
                          // Customer email
    const char* phone     // in
                          // Customer phone number
) {
    if (custID && *custID) {
        safeStrCopy(this->custID, custID, sizeof(this->custID));
    } else {
        // Assuming IDGenerator returns a char*
        char* generatedID = IDGenerator('1', 10);
        safeStrCopy(this->custID, generatedID, sizeof(this->custID));
        delete[] generatedID;
    }
    safeStrCopy(this->name, name, sizeof(this->name));
    safeStrCopy(this->email, email, sizeof(this->email));
    safeStrCopy(this->phone, phone, sizeof(this->phone));
}
/*
Create Customer object using attrbibutes provided. 
No noticeable algorithm or data structure used.
--------------------------------------------------------------------*/

// Constructor: Copy
Customer::Customer(
    const Customer& other // in
                          // Another Customer object to copy from
) {
    safeStrCopy(this->custID, other.custID, sizeof(this->custID));
    safeStrCopy(this->name, other.name, sizeof(this->name));
    safeStrCopy(this->email, other.email, sizeof(this->email));
    safeStrCopy(this->phone, other.phone, sizeof(this->phone));
}

// Destructor
Customer::~Customer() {
    // No dynamic memory to clean up
}

// Operator: Assignment
Customer& Customer::operator=(
    const Customer& other // in
                          // Another Customer object to assign from
) {
    if (this != &other) {
        safeStrCopy(this->custID, other.custID, sizeof(this->custID));
        safeStrCopy(this->name, other.name, sizeof(this->name));
        safeStrCopy(this->email, other.email, sizeof(this->email));
        safeStrCopy(this->phone, other.phone, sizeof(this->phone));
    }
    return *this;
}

// Operator: Equality
bool Customer::operator==(
    const Customer& other // in
                          // Another Customer object to compare to
) const {
    return (strcmp(custID, other.custID) == 0 || strcmp(email, other.email) == 0 || strcmp(phone, other.phone) == 0);
}
/*
Checks if two Customer objects are equal based on custID or email or phone. 
No noticeable algorithm or data structure used.
--------------------------------------------------------------------*/
// DisplayDetails
void Customer::DisplayDetails(
    std::ostream& out  // in/out
                       // ostream object to handle calling with << operator
) const {
    if (name[0] == '\0' || email[0] == '\0' || phone[0] == '\0') {
        out << "Error: One or more attributes of customer do not have values." << std::endl;
    } else {
        out.width(15);
        out << std::left << custID;
        out.width(32);
        out << std::left << name;
        out.width(24);
        out << std::left << email;
        out.width(15);
        out << std::left << phone << std::endl;
    }
}
/*
Print the attribute details of the Customer object to the console.
No noticeable algorithm or data structure used.
--------------------------------------------------------------------*/
// CreateCustomer
Customer CreateCustomer(
    const char* name,  // in
                       // Customer name
    const char* email, // in
                       // Customer email
    const char* phone  // in
                       // Customer phone number
) {
    int validationResult = ValidateCustomer(name, email, phone);
    if (validationResult == 1) {
        // Generate a new customer ID
        char* generatedID = IDGenerator('0', 10);

        // Create the customer object
        Customer newCustomer(generatedID, name, email, phone);
       // Clean up the generated ID
        delete[] generatedID;

        return newCustomer;
    } else if (validationResult == 0) {
        throw std::runtime_error("FailedToCreateCustomer: Customer with same email or phone already exists!");
    } else {
        throw std::runtime_error("FailedToCreateCustomer: Invalid name, email, or phone");
    }
}
/*
Create new Customer object and also validates it.
No noticeable algorithm or data structure used.
--------------------------------------------------------------------*/

// CommitCustomer
void CommitCustomer(
    const Customer& customer, // in
                              // Customer to add in binary file
    std::streampos& startPos, // in/out
                              // File pointer of the binary file
    const std::string& FILENAME // in
                              // Location-name of file
) {
    std::ofstream file(FILENAME, std::ios::binary | std::ios::in | std::ios::out);
    if (!file) {
        throw std::runtime_error("Could not open file for writing");
    }
    file.seekp(startPos);
    file.write(reinterpret_cast<const char*>(&customer), sizeof(Customer));
    startPos = file.tellp();
}
/*
Writes a Customer object to a specified file at a given position.
Uses the unsorted records data structure to add the Complaint object.
--------------------------------------------------------------------*/
// GetCustomerDetails
Customer GetCustomerDetails(
    std::streampos& startPos,    // in/out
                                 // File pointer of the binary file
    const std::string& FILENAME  // in
                                 // Location-name of file
) {
    std::ifstream file(FILENAME, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Could not open file for reading");
    }
    file.seekg(startPos);
    Customer customer;
    file.read(reinterpret_cast<char*>(&customer), sizeof(Customer));
    startPos = file.tellg();
    return customer;
}
/*
Reads a Customer object from a specified file at a given position and returns it.
Uses the unsorted records data structure to read the Customer object.
--------------------------------------------------------------------*/
// PrintAllCustomers
void PrintAllCustomers(
    const std::string& FILENAME  // in
                                 // Location-name of file
) {
    std::ifstream file(FILENAME, std::ios::binary);
    if (!file) {
        std::cerr << "Error: Could not open file " << FILENAME << " for reading." << std::endl;
        return;
    }

    Customer customer;
    int recordCount = 0;

    std::cout << std::left
              << std::setw(12) << "Customer ID"
              << std::setw(31) << "Name"
              << std::setw(31) << "Email"
              << std::setw(15) << "Phone" << std::endl;
    std::cout << std::string(89, '-') << std::endl;

    while (file.read(reinterpret_cast<char*>(&customer), sizeof(Customer))) {
        std::cout << std::left
                  << std::setw(12) << customer.getCustID()
                  << std::setw(31) << customer.getName()
                  << std::setw(31) << customer.getEmail()
                  << std::setw(15) << customer.getPhone() << std::endl;
        recordCount++;
    }

    std::cout << std::string(89, '-') << std::endl;
    std::cout << "Total records: " << recordCount << std::endl;

    if (file.eof()) {
        file.clear();  // Clear EOF flag
    }
    else if (file.fail()) {
        std::cerr << "Error occurred while reading the file." << std::endl;
    }

    file.close();
}

// ValidateCustomer
int ValidateCustomer(
    const char* name,  // in
                       // Customer name
    const char* email, // in
                       // Customer email
    const char* phone  // in
                       // Customer phone number
) {
    if (strlen(name) == 0 || strlen(email) == 0 || strlen(phone) == 0)
        return -1;
    // Validate email
    const char* atSign = strchr(email, '@');
    if (atSign == nullptr)
        return -1;
    const char* dotSign = strchr(atSign, '.');
    if (dotSign == nullptr)
        return -1;
    if (atSign == email || !isalpha(email[0]))
        return -1;
    if (dotSign == atSign + 1 || dotSign == atSign + 2 || *(dotSign + 1) == '\0')
        return -1;
    for (const char* p = email; p < atSign; ++p) {
        if (!isalnum(*p) && *p != '.' && *p != '-' && *p != '_')
            return -1;
    }
    for (const char* p = atSign + 1; p < dotSign; ++p) {
        if (!isalnum(*p) && *p != '-' && *p != '_')
            return -1;
    }

    // Validate phone number [1]6041231234
    if (phone[0] != '1' || !isdigit(phone[1]) || !isdigit(phone[2]) || !isdigit(phone[3]) || !isdigit(phone[4]) || !isdigit(phone[5]) || !isdigit(phone[6]) || !isdigit(phone[7]) || !isdigit(phone[8]) || !isdigit(phone[9]) || !isdigit(phone[10]))
        return -1;

    // Check if record already exists
    std::ifstream file(FILENAMES[0], std::ios::binary);
    if (!file) {
        throw std::runtime_error("Could not open file for reading");
    }

    Customer temp;
    while (file.read(reinterpret_cast<char*>(&temp), sizeof(Customer))) {
        // read through the file
        if (strcmp(temp.getEmail(), email) == 0 || strcmp(temp.getPhone(), phone) == 0) {
            std::cout << "Record already exists :/" << std::endl;
            return 0;
        }
    }

    std::cout << "Record is valid!" << std::endl;
    return 1;
}

bool checkDup(const char *otherCustID){
    std::ifstream file(FILENAMES[0], std::ios::binary);
    if (!file) {
        throw std::runtime_error("Could not open file for reading");
        return 0;
    }
    Customer temp;
    while (file.read(reinterpret_cast<char*>(&temp), sizeof(Customer))){
        if (strcmp(temp.getCustID(), otherCustID) == 0) {
            std::cout << "Record already exists :/" << std::endl;
            return 1;
        }
    }
    return 0;
}

/*
Validates that the Customer object attributes are acceptable and makes sure no duplicate Customer records exists.
A linear search algorithm is used to iterate through the Customer records.
--------------------------------------------------------------------*/
// InitCustomer
int InitCustomer() {
    std::filesystem::create_directory(DIRECTORY);
    if (!std::filesystem::exists(FILENAMES[0])) {
        std::ofstream file(FILENAMES[0], std::ios::binary);
        if (!file) {
            return -1;
        } else {
            file.close();
            return 1;
        }
    } else {
        return 0;
    }
}
