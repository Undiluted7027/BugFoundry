/* unitTestMain.cpp 
REVISION HISTORY:
Rev. 1 - 24/07/03 Original by Jason Lee
--------------------------------------------------------------------*/
#include <iostream>
#include <string.h>
#include "Customer.hpp"
#include "Change.hpp"
#include "Complaint.hpp"
#include "Product.hpp"

int main()
{
    /* Test case for validating a Product.
    If the test passes, the system recognizes correct format of product
    If not, the system does not recognizes.*/
    int anID = 12345;
    char* aDate = "24-04-02";
    char* badDate = "141241";

    if (ValidateProduct(anID, aDate))
    {
        cout << "Test Passed: Detected Valid product" << endl;
    }
    else
    {
        cout << "Test Failed: Did not detect Valid product" << endl;
    }
    if (ValidateProduct(anID, badDate))
    {
        cout << "Test Failed: Did not detect Invalid product" << endl;
    }
    else
    {
        cout << "Test Passed: Detected Invalid product" << endl;
    }

    /* Test case for validating a Customer.
    If the test passes, the system recognizes correct format of customer
    If not, the system does not recognizes.*/
    string aName = "Bob";
    string anEmail = "Bob@gmail.com";
    string aPhone = "1-778-123-4567";
    string badEmail = "abcdefg";

    if (ValidateCustomer(aName, anEmail, aPhone))
    {
        cout << "Test Passed: Detected Valid customer" << endl;
    }
    else
    {
        cout << "Test Failed: Did not detect sValid customer" << endl;
    }
    if (ValidateCustomer(aName, badEmail, aPhone))
    {
        cout << "Test Failed: Did not detect Invalid customer" << endl;
    }
    else
    {
        cout << "Test Passed: Detected Invalid customer" << endl;
    }

    /* Test case for validating a Complaint.
    If the test passes, the system recognizes correct format of customer
    If not, the system does not recognizes.*/
    string userID = "123456789";

    if (ValidateComplaint(userID))
    {
        cout << "Test Passed: Detected Invalid Complaint" << endl;
    }
    else
    {
        cout << "Test Failed: Did not detect Invalid Complaint" << endl;
    }

    /* Test case for validating a Change.
    If the test passes, the system recognizes correct format of change
    If not, the system does not recognizes.*/
    string aStatus = "P";
    string aPriority = "1";
    int releaseID = 1111;
    string aDesc = "NOT WORKING";
    string badDesc = "NOT WORKING!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";

    if (ValidateChange(aDesc, aStatus, aPriority, aDate, releaseID))
    {
        cout << "Test Passed: Detected Valid Change" << endl;
    }
    else
    {
        cout << "Test Failed: Did not detect Valid Change" << endl;
    }
    if (ValidateChange(badDesc, aStatus, aPriority, aDate, releaseID))
    {
        cout << "Test Failed: Did not detect Invalid Change" << endl;
    }
    else
    {
        cout << "Test Passed: Detected Invalid Change" << endl;
    }
    
}