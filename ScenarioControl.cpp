/* ScenarioControl.hpp
REVISION HISTORY:
Rev. 2 - 24/07/11 Functions skeletal implementations by Jason Lee
Rev. 1 - 24/07/03 Original by Jason Lee 
--------------------------------------------------------------------*/
#include "ScenarioControl.hpp"

/*

--------------------------------------------------------------------*/
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
    return 1;
}

int NewCustomer()
{
    char name[31];
    char email[25];
    char phone[12];
    char dept;

    cout << "===Creating a User===" << endl;
    cout << "Enter full name (30 max characters): ";
    cin.getline(name, 30);
    if (NameError(name)) return 0;
    cout << endl;

    cout << "Enter email (24 max characters): ";
    cin.getline(email, 24);
    if (EmailError(email)) return 0;
    cout << endl;

    cout << "Enter phone (eg. [1]6047231023): ";
    cin.getline(phone, 11);
    if (PhoneError(phone)) return 0;
    cout << endl;

    cout << "Enter department (software engineer, marketer, customer)" << endl;
    cout << "(S/M/∅): ";
    cin >> dept;
    if (DeptError(dept)) return 0;
    cout << endl;

    char choice;
    cout << "Confirm to create user (Y/N): ";
    cin >> choice;
    if (choice == 'N') 
    {
        cout << "User Creation Canceled" << endl;
        return 0;
    }

    // if (ValidateCustomer(name, email, phone)) 
    // {
    //     CommitCustomer(CreateCustomer(name, email, phone), CUSTOMERFILEPOINTER, FILENAMES[0]);
    //     cout << "New UserID: " << endl;
    //     cout << "User Successfully Created" << endl;
    //     return 1;
    // }
    cout << "User already exists!" << endl;
    return 0;
}

int CreateNewComplaint()
{
    char userID[11];
    char relID[9];
    char desc[31];
    char product[11];

    cout << "===Creating a Complaint===" << endl;
    cout << "Enter your UserID (9 digit): ";
    cin.getline(userID ,9);
    // UserID exist check
    cout << endl;

    cout << "Enter the Product the bug was found on: ";
    cin.getline(product, 10);
    // Product exist check
    cout << endl;

    cout << "Enter the Product ReleaseID that the bug was found on" << endl;
    cout << "(max 8 letters releaseID): ";
    cin.getline(relID, 8);
    // ReleaseID exist check
    cout << endl;

    // Check if releaseID and Product match

    cout << "Enter Description of your complaint (30 max characters):" << endl;
    cin.getline(desc, 30);
    if (DescError(desc)) return 0;
    cout << endl;
    
    char choice;
    cout << "Confirm to create complaint (Y/N): ";
    cin >> choice;
    if (choice == 'N') 
    {
        cout << "Complaint Creation Canceled" << endl;
        return 0;
    }

    if (ValidateComplaint(desc, "date", NULL, relID, atoi(userID)))
    {
        CommitComplaint(CreateComplaint(desc, "date", NULL, relID, atoi(userID)));
        cout << "Complaint Created Successfully" << endl;
        return 1;
    }
    cout << "Complaint already exists!" << endl;
    return 0;
}   

int CreateNewProduct()
{
    char product[11];
    cout << "===Create Product===" << endl;
    cout << "Enter the new product name (10 max characters): ";
    cin.getline(product, 10);
    if (ProductError(product)) return 0;
    cout << endl;

    char choice;
    cout << "Confirm to create product (Y/N): ";
    cin >> choice;
    if (choice == 'N') 
    {
        cout << "Complaint Creation Canceled" << endl;
        return 0;
    }

    // if (ValidateProduct(CreateProduct(NULL, NULL)))
    // {
    //     CommitProduct(CreateProduct(NULL, NULL));
    //     cout << "Product Created Successfully" << endl;
    //     return 1;
    // }
    cout << "Product already exists!" << endl;
    return 0;
}

int CreateNewProductRel()
{
    char product[11];
    char date[11];
    char relID[9];

    cout << "===Create Product Release===" << endl;
    cout << "Enter the product name (10 max characters): ";
    cin.getline(product, 10);
    if (ProductError(product)) return 0;
    // if (ValidateProduct() == 0) return 0;
    cout << endl;

    cout << "Enter the anticipated release date (YYYY-MM-DD): ";
    cin.getline(date,10);
    if (DateError(date)) return 0;
    cout << endl;

    cout << "Enter the new releaseID (8 max characters): " << endl;
    cin.getline(relID, 8);
    if (ReleaseIDError(relID)) return 0;
    cout << endl;

    char choice;
    cout << "Confirm to create product release (Y/N): ";
    cin >> choice;
    if (choice == 'N') 
    {
        cout << "Product Release Creation Canceled" << endl;
        return 0;
    }

    // if (ValidateProduct(relID, date))
    // {
    //     CommitProduct(CreateProduct(product, relID, date));
    //     cout << "Product Release Created Successfully" << endl;
    //     return 1;
    // }
    return 0;
}

int UpdateSpecificChange()
{
    char changeID[7];
    cout << "===ChangeID===" << endl;
    cout << "Enter the ChangeID (6 Digit ID): ";
    cin.getline(changeID,6);
    if (ChangeIDError(changeID)) return 0;

    return UpdateChangeInfo(atoi(changeID));
}

int ListAndSelectChange()
{
    int changeID;
    cout << "LATEST CHANGES" << endl << endl;
    
    // display 10 changes

    return UpdateChangeInfo(changeID);;
}

int UpdateChangeInfo(int changeID)
{
    char product[11];
    char desc[31];
    char state[11];
    int priority;
    char relID[9];
    char choice;

    cout << "Updating product " << " Product Name" << endl << endl;
    cin.getline(product, 10);
    // if (!ValidateProduct()) return 0;
    
    cout << "Update the description (Y/N)? ";
    cin >> choice;
    cout << endl;
    if (choice == 'Y')
    {
        cout << "Old Description: " << "[old description]" << endl;
        cout << "New Description: ";
        cin.getline(desc, 30);
        if (DescError(desc)) return 0;
        // Update desc
    }
    cout << endl;

    cout << "Current state: " << "[current state]" << " Update the state (Y/N)? ";
    cin >> choice;
    cout << endl;
    if (choice == 'Y')
    {
        cout << "New State (CANCELED/INPROGRESS/DONE): ";
        cin.getline(state, 10);
        if (StateError(state)) return 0;
        // Update status
    }
    cout << endl;

    cout << "Current priority: " << "[current priority]" << ". Update the priority (Y/N)? ";
    cin >> choice;
    cout << endl;
    if (choice == 'Y')
    {
        cout << "New Priority (Number between 1 and 5): ";
        cin >> priority;
        if (PriorityError(priority)) return 0;
        // Update priority
    }
    cout << endl;

    cout << "Current anticipated releaseID: " << "[current releaseID]" << ". Update anticipated releaseID (Y/N)? ";
    cin >> choice;
    cout << endl;
    if (choice == 'Y')
    {
        cout << "New releaseID (maximum 8 characters): ";
        cin >> relID;
        if (ReleaseIDError(relID)) return 0;
        // Update relID
    }
    cout << endl;

    cout << "Updated product " << "[Product Name]" << " successfully" << endl;
    return 1;
}

int DisplayChangeReport()
{
    int start = 1;
    int end = 11;
    int choice;

    cout << "CHANGE REPORT" << endl << endl;
    // if (end of line)
    // {
    //     cout << "No changes to show!" << endl;
    //     return 0;
    // }
    while (start < end /*&& !EOL*/ )
    {
        // display upto 10 items 
        cout << "Type 1 to show next list, 0 to quit: ";
        cin >> choice;
        cout << endl;
        if (DisplayPageError(choice) != 1) break;
        start = end;
        end = end + 10;
    }
    return 1;
}

int ProductOnChange()
{
    char relID[9];
    int start = 1;
    int end = 11;
    int choice;

    cout << "===ReleaseID===" << endl;
    cout << "Enter the ReleaseID (max 8 characters): ";
    cin.getline(relID, 8);
    if (ReleaseIDError(relID)) return 0;
    cout << endl;

    cout << "ANTICIPATED CHANGES FOR " << "Product Name" << endl << endl;
    do 
    {
        // if (end of line)
        // {
        //     cout << "No changes to show!" << endl;
        //     return 0;
        // }
        while (start < end /*&& !EOL*/ )
        {
            // display upto 10 changes
        }
        cout << "Type 1 to show next list, 0 to quit: ";
        cin >> choice;
        cout << endl;

        start = end;
        end = end + 10;
    } while (DisplayPageError(choice) == 1);
    return 1;
}

int UserOnChange()
{
    char product[9];
    int changeID[10];
    char input[3];
    int choice;
    int start = 1;
    int end = 11;

    cout << "===Product Name===" << endl;
    cout << "Enter the product name: ";
    cin.getline(product, 10);
    // if (!ValidateProduct()) return 0
    cout << endl;

    cout << "List of changes" << endl;
    do 
    {
        // if (end of line)
        // {
        //     cout << "No changes to show!" << endl;
        //     return 0;
        // }
        while (start < end /*&& !EOL*/ )
        {
            // display upto 10 changes
        }
        cout << "Type the number to the left of Change to select. ('1' to show the next list, '0' to quit): ";
        cin.getline(input, 3);
        choice = atoi(input);
        cout << endl;
        
        choice = SearchPageError(choice, start, end);
        start = end;
        end = end + 10;
    } while (choice == 1);

    if (choice == -1) return 0;
    choice = 0;

    do 
    {
        // if (end of line)
        // {
        //     cout << "No changes to show!" << endl;
        //     return 0;
        // }
        while (start < end /*&& !EOL*/ )
        {
            // display upto 10 users
        }
        cout << "Press '1' to go to the next page or '1' to quit viewing ";
        cin >> choice;
        cout << endl;
        
        start = end;
        end = end + 10;
    } while (DisplayPageError(choice) == 1);
    return 1;
}