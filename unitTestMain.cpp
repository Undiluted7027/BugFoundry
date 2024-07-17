/* unitTestMain.cpp 
REVISION HISTORY:
Rev. 2 - 24/07/14 Revised by Seoyoung Kim
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
    char *aProduct = "SmartLight";
    char *aReleaseID = "12345678"; // releaseID
    char* aDate = "2024-04-02"; //date
    char* badDate = "141241";
    char *aCID = "12345"; //changeid

    if (ValidateProduct(aProduct, aReleaseID, aDate))
    {
        cout << "Test Passed: Detected Valid product" << endl;
    }
    else
    {
        cout << "Test Failed: Did not detect Valid product" << endl;
    }
    if (ValidateProduct(aProduct, aReleaseID, badDate))
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
    char* aName = "Bob";
    char* anEmail = "Bob@gmail.com";
    char* aPhone = "1-778-123-4567";
    char* badEmail = "abcdefg";

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
    char *userID = "123456789"; // userid
    char* aDesc = "NOT WORKING"; //desc
    char* badDesc = "NOT WORKING!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";


    if (ValidateComplaint(aDesc, aDate, aCID, aReleaseID, userID))
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
    char aStatus = 'P';
    char aPriority = '1';
    
    if (ValidateChange(aDesc, aStatus, aPriority, aDate, aReleaseID))
    {
        cout << "Test Passed: Detected Valid Change" << endl;
    }
    else
    {
        cout << "Test Failed: Did not detect Valid Change" << endl;
    }
    if (ValidateChange(badDesc, aStatus, aPriority, aDate, aReleaseID))
    {
        cout << "Test Failed: Did not detect Invalid Change" << endl;
    }
    else
    {
        cout << "Test Passed: Detected Invalid Change" << endl;
    }
    
}