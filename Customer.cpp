#include "Customer.hpp"
#include "Globals.hpp"
#include "drivers.cpp"
#include <cstring>
#include <iostream>

using namespace std;

Customer::Customer(const char *name, const char *email, const char *phone)
{ // using a dummy ID
    const char *generatedID = IDGenerator<const char *>('1', 10);
    strcpy(this->custID, generatedID);
    this->custID[sizeof(this->custID) - 1] = '\0';
    strcpy(this->name, name);
    this->name[sizeof(this->name) - 1] = '\0';
    strcpy(this->email, email);
    this->email[sizeof(this->email) - 1] = '\0';
    strcpy(this->phone, phone);
    this->phone[sizeof(this->phone) - 1] = '\0';
}

bool Customer::operator==(const Customer &other) const{
    return (custID == other.custID || email == other.email || phone == other.phone);
}

void Customer::DisplayDetails(ostream &out) const
{
    if (strlen(name) == 0 || strlen(email) == 0 || strlen(phone) == 0)
        out << "Error in reading Customer information. One or more attributes of customer do not have value(s)" << endl;
    // RAISE ERROR
    // exit(1);
    else
    {
        out << "CustID: " << custID << endl;
        out << "name: " << name << endl;
        out << "email: " << email << endl;
        out << "phone: " << phone << endl;
    }
}

bool Customer::operator==(const Customer &other) const
{
    return name == other.name && email == other.email && phone == other.phone;
}

Customer CreateCustomer(const char *name, const char *email, const char *phone)
{

    if (ValidateCustomer(name, email, phone))
    {
        Customer newCust(name, email, phone);
        return newCust;
    }
    else
    {
        // RAISE EXCEPTION
        cout << "Could not create a new customer!" << endl;
    }
}

void CommitCustomer(const Customer &customer, streampos &startPos = CUSTOMERFILEPOINTER, const string &FILENAME = FILENAMES[0])
{
    writeRecord(FILENAME, startPos, customer);
}

Customer GetCustomerDetails(streampos &startPos = CUSTOMERFILEPOINTER, const string &FILENAME = FILENAMES[0])
{
    Customer newCust = readRecord<Customer>(FILENAME, startPos);
    return newCust;
}

int ValidateCustomer(const char *name, const char *email, const char *phone)
{

    if (email == nullptr || *email == '\0' || name == nullptr || *name == '\0' || phone == nullptr || *phone == '\0')
        return -1;
    else
    {
        // validate email
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
            if (!std::isalnum(*p) && *p != '.' && *p != '-' && *p != '_')
            {
                return -1; // Invalid character found
            }
        }

        // Check for invalid characters in the domain part (after '@')
        for (const char *p = atSign + 1; p < dotSign; ++p)
        {
            if (!std::isalnum(*p) && *p != '-' && *p != '_')
            {
                return -1; // Invalid character found
            }
        }

        // validate phone num
        if (phone[0] != '1' || phone[1] != ' ' || !isdigit(phone[2]) || isdigit(phone[3]) || !isdigit(phone[4]) || phone[5] != '-'|| !isdigit(phone[6]) || isdigit(phone[7]) || !isdigit(phone[8]) || phone[9] != '-'|| !isdigit(phone[10]) || isdigit(phone[11]) || !isdigit(phone[12]) ||!isdigit(phone[13]) || phone[14]!='\0')
            return -1;
        
    }

    // check if record already exists
    Customer *dataptr = readFile<Customer>(FILENAMES[0], CUSTOMERFILEPOINTER);
    Customer dummy(name, email, phone);

    size_t size = sizeof(dataptr) / sizeof(dataptr[0]);
    for (int i = 0; i < size; i++)
    {
        if (dataptr[i] == dummy)
        {
            delete [] dataptr;
            cout << "Record already exists :/" << endl;
            return 0;
            // break;
        }
    }
    delete [] dataptr;
    cout << "Record is valid!" << endl;
    return 1;
    
}