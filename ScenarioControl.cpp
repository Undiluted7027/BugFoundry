/* ScenarioControl.hpp
REVISION HISTORY:
Rev. 2 - 24/07/11 Functions skeletal implementations by Jason Lee
Rev. 1 - 24/07/03 Original by Jason Lee 
--------------------------------------------------------------------*/
#include <ScenarioControl.hpp>

int ScenarioControl(int choice, int subchoice)
{
    switch (choice)
    {
        case 0:
            break;

        case 1:
            if (subchoice == 1) NewCustomer();
            if (subchoice == 2) CreateNewComplaint();
            if (subchoice == 3) CreateNewProduct();
            if (subchoice == 4) CreateNewProductRel();
            break;
        
        case 2:
            if (subchoice == 1) UpdateSpecificChange();
            if (subchoice == 2) ListAndSelectChange();
            break;
        
        case 3:
            if (subchoice == 1) DisplayChangeReport();
            if (subchoice == 2) ProductOnChange();
            if (subchoice == 3) UserOnChange();
            break;
        
        default:
            cout << "Error message" << endl;
            break;
    }
}

Customer NewCustomer()
{
    char name[31];
    char email[25];
    char phone[12];

    cout << "===Creating a User===" << endl;
    cout << "Enter full name (30 max characters): ";
    // cin.getline(name, 30);
    cout << endl;
    cout << "Enter email (24 max characters): ";
    // cin.getline(email, 24);
    cout << "Enter phone (eg. [1]6047231023): ";
    // cin.getline(phone, 11);
    cout << endl;
    cout << "Enter department (software engineer, marketer, customer)" << endl;
    cout << "(S/M/∅): ";
    //
    cout << endl;
    return CreateCustomer(name, email, phone);
    // The new userID must be displayed when successful!
}

Complaint CreateNewComplaint()
{
    char userID[11];
    char relID[9];
    char desc[31];

    cout << "===Creating a Complaint===" << endl;
    cout << "Enter your UserID (9 digit): ";
    // cin.getline(userid ,9);
    cout << endl;
    cout << "Enter the Product the bug was found on: ";
    //
    cout << endl;
    cout << "Enter the Product ReleaseID that the bug was found on" << endl;
    cout << "(max 8 letters releaseID): ";
    // cin.getline(relID, 8);
    cout << "Enter Description of your complaint (30 max characters):" << endl;
    // cin.getline(desc, 30);
    return CreateComplaint(desc, "date", "changeID", 123, 123);
}   

Product CreateNewProduct()
{
    char product[11];
    cout << "===Create Product===" << endl;
    cout << "Enter the new product name (10 max characters): ";
    return CreateProduct(0, "date");
}

Product CreateNewProductRel()
{
    cout << "===Create Product Release===" << endl;
    cout << "Enter the product name (10 max characters): ";
    cout << "Enter the anticipated release date (YYYY-MM-DD): ";
    return CreateProduct(1, "date");
}

int UpdateSpecificChange()
{
    int changeID;
    cout << "===ChangeID===" << endl;
    cout << "Enter the ChangeID (6 Digit ID): ";
    
    UpdateChangeInfo(changeID);
    return 1;
}

int ListAndSelectChange()
{
    int changeID;
    cout << "LATEST CHANGES" << endl << endl;
    
    UpdateChangeInfo(changeID);
    return 1;
}

int UpdateChangeInfo(int changeID)
{
    cout << "Updating product " << " Product Name" << endl << endl;
    cout << "Update the description (Y/N)? ";
    cout << endl;
    cout << "Current state: ";
    cout << "Update the state (Y/N)? ";
    cout << endl;
    cout << "Current priority: ";
    cout << "Update the priority (Y/N)?";
    cout << endl;
    cout << "Current anticipated releaseID: ";
    cout << "Update anticipated releaseID (Y/N)";
    cout << endl;

    return 1;
}

int ProductOnChange()
{
    char relID[9];
    cout << "===ReleaseID===" << endl;
    cout << "Enter the ReleaseID (max 8 characters): ";
    cout << endl;

    DisplayProductChangeReport(relID);
    return 1;
}

int DisplayProductChangeReport(char* releaseID)
{
    cout << "ANTICIPATED CHANGES FOR " << "Product Name" << endl << endl;
}

int UserOnChange()
{
    char product[9];
    int changeID[10];
    cout << "===Product Name===" << endl;
    cout << "Enter the product name: ";
    cout << endl;

    cout << "List of changes" << endl;
}

int DisplayUsersOnUpdateChange(int changeID)
{
    cout << "List of users" << endl;
}