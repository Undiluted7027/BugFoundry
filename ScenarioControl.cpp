/* ScenarioControl.hpp
REVISION HISTORY:
Rev. 2 - 24/07/11 Functions implementations and comments by Jason Lee
Rev. 1 - 24/07/03 Original by Jason Lee 
--------------------------------------------------------------------*/
#include "ScenarioControl.hpp"

int ScenarioControl(int choice, int subchoice)
{
    // Run the function of user's choice
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
            cout << "Error: Your option is not an available choice" << endl;
            break;
    }
    return 1;
}
/*
Executes the selected function by obtaining user's choice and subchoice.
No noticeable algorithm or data structure used.
--------------------------------------------------------------------*/
int NewCustomer()
{
    char name[31];
    char email[25];
    char phone[12];
    char dept;

    cout << "===Creating a User===" << endl;

    // Get user's name and checks the format 
    cout << "Enter full name (30 max characters): ";
    cin.getline(name, 30);
    if (NameError(name)) return 0;
    cout << endl;

    // Get user's email and checks the format
    cout << "Enter email (24 max characters): ";
    cin.getline(email, 24);
    if (EmailError(email)) return 0;
    cout << endl;

    // Get user's phone and checks the format
    cout << "Enter phone (eg. [1]6047231023): ";
    cin.getline(phone, 11);
    if (PhoneError(phone)) return 0;
    cout << endl;

    // Get user's department and checks the format
    cout << "Enter department (software engineer, marketer, customer)" << endl;
    cout << "(S/M/∅): ";
    cin >> dept;
    if (DeptError(dept)) return 0;
    cout << endl;

    // Confirm the action
    char choice;
    cout << "Confirm to create user (Y/N): ";
    cin >> choice;
    if (choice == 'N') 
    {
        cout << "User Creation Canceled" << endl;
        return 0;
    }

    // Write the new user to the file after user duplication check
    if (ValidateCustomer(name, email, phone)) 
    {
        CommitCustomer(CreateCustomer(name, email, phone), CUSTOMERFILEPOINTER, FILENAMES[0]);
        cout << "New UserID: " << endl;
        cout << "User Successfully Created" << endl;
        return 1;
    }
    cout << "User already exists!" << endl;
    return 0;
}
/*
Gathers new user's info. 
Checks if each of info attributes are in the correct format.
No noticeable algorithm or data structure used.
--------------------------------------------------------------------*/
int CreateNewComplaint()
{
    char userID[11];
    char relID[9];
    char desc[31];
    char product[11];

    cout << "===Creating a Complaint===" << endl;

    // Get requester's userID and checks the existance
    cout << "Enter your UserID (9 digit): ";
    cin.getline(userID ,9);
    //ValidateCustomer(userID);
    cout << endl;

    // Get the specific product to be complained and checks the existance
    cout << "Enter the Product the bug was found on: ";
    cin.getline(product, 10);
    // ValidateProduct(product);
    cout << endl;

    // Get the product's releaseID and checks the existance
    cout << "Enter the Product ReleaseID that the bug was found on" << endl;
    cout << "(max 8 letters releaseID): ";
    cin.getline(relID, 8);
    // ValidateProduct()
    cout << endl;

    // Check if releaseID and Product match

    // Get the description of complaint and checks the format
    cout << "Enter Description of your complaint (30 max characters):" << endl;
    cin.getline(desc, 30);
    if (DescError(desc)) return 0;
    cout << endl;
    
    // Confirm the action
    char choice;
    cout << "Confirm to create complaint (Y/N): ";
    cin >> choice;
    if (choice == 'N') 
    {
        cout << "Complaint Creation Canceled" << endl;
        return 0;
    }

    // Write the complaint and create the change after existance check
    CommitComplaint(CreateComplaint(desc, "date", NULL, relID, userID));
    if (ValidateChange(desc, '-', 1, "date", NULL))
    {
        Change newChange = CreateChange(desc, '-', 1, "date", NULL, NULL);
        CommitChange(newChange, CHANGEFILEPOINTER, FILENAMES[1]);
        cout << "Complaint Created Successfully" << endl;
        return 1;
    }
    cout << "Complaint already exists!" << endl;
    return 0;
}   
/*
Gathers new complaint's info. 
Checks if each of info attributes are in the correct format.
No noticeable algorithm or data structure used.
--------------------------------------------------------------------*/
int CreateNewProduct()
{
    char product[11];
    cout << "===Create Product===" << endl;
    
    // Get the product name and checks the format
    cout << "Enter the new product name (10 max characters): ";
    cin.getline(product, 10);
    if (ProductError(product)) return 0;
    cout << endl;

    // Confirm the action
    char choice;
    cout << "Confirm to create product (Y/N): ";
    cin >> choice;
    if (choice == 'N') 
    {
        cout << "Complaint Creation Canceled" << endl;
        return 0;
    }

    // Write the product to the file after duplication check
    if (ValidateProduct(product, NULL, NULL))
    {
        CommitProduct(CreateProduct(product, NULL, NULL));
        cout << "Product Created Successfully" << endl;
        return 1;
    }
    cout << "Product already exists!" << endl;
    return 0;
}
/*
Create a product by getting product name input from the user.
No noticeable algorithm or data structure used.
--------------------------------------------------------------------*/
int CreateNewProductRel()
{
    char product[11];
    char date[11];
    char relID[9];

    cout << "===Create Product Release===" << endl;

    // Get the product name and check the existance
    cout << "Enter the product name (10 max characters): ";
    cin.getline(product, 10);
    if (ProductError(product)) return 0;
    // if (!ValidateProduct(product)) return 0;
    cout << endl;

    // Get the anticipated release date and check the format
    cout << "Enter the anticipated release date (YYYY-MM-DD): ";
    cin.getline(date,10);
    if (DateError(date)) return 0;
    cout << endl;

    // Get the releaseID and check the format
    cout << "Enter the new releaseID (8 max characters): " << endl;
    cin.getline(relID, 8);
    if (ReleaseIDError(relID)) return 0;
    cout << endl;

    // Confirm the action
    char choice;
    cout << "Confirm to create product release (Y/N): ";
    cin >> choice;
    if (choice == 'N') 
    {
        cout << "Product Release Creation Canceled" << endl;
        return 0;
    }

    // Write the releaseID to the file after duplication check
    if (ValidateProduct(product, relID, NULL))
    {
        CommitProduct(CreateProduct(product, relID, NULL));
        cout << "Product Release Created Successfully" << endl;
        return 1;
    }
    return 0;
}
/*
Create a new product releaseID by getting product name input from the user.
Checks if each of info attributes are in the correct format.
No noticeable algorithm or data structure used.
--------------------------------------------------------------------*/
int UpdateSpecificChange()
{
    char changeID[7];
    cout << "===ChangeID===" << endl;

    // Get the changeID and check for existance
    cout << "Enter the ChangeID (6 Digit ID): ";
    cin.getline(changeID,6);
    if (ChangeIDError(changeID)) return 0;
    // if (!ValidateChange(changeID)) return 0;

    return UpdateChangeInfo(atoi(changeID));
}
/*
Gets a specific changeID input from the user to update the change.
Checks if it exists and in right format
No noticeable algorithm or data structure used.
--------------------------------------------------------------------*/
int ListAndSelectChange()
{
    int start = 1;
    int end = 11;
    char input[3];
    int choice;
    
    cout << "LATEST CHANGES" << endl << endl;
    
    cout.width(2); cout << left << " ";
    cout.width(12); cout << left << "Product";
    cout.width(32); cout << left << "Description";
    cout.width(10); cout << left << "ChangeID";
    cout.width(12); cout << left << "Date";
    cout.width(11); cout << left << "Status";
    cout.width(10); cout << left << "Priority";
    cout.width(9); cout << left << "ReleaseID" << endl;

    do 
    {
        // Check if change file is empty
        if (CHANGEFILEPOINTER == NULL)
        {
            cout << "No changes to show!" << endl;
            return 0;
        }
        // While it hasn't displayed 10 datas or hasn't reached to the end of file, display the datas
        while (start < end && CHANGEFILEPOINTER != NULL)
        {
            Change getChange = GetChangeDetails(CHANGEFILEPOINTER - start * sizeof(Change), FILENAMES[1]);
            cout.width(2); cout << left << start << " ";
            getChange.DisplayDetails(cout);
            start++;
        }
        // Get user choice
        cout << "Type the number to the left of Change to select. ('1' to show the next list, '0' to quit): ";
        cin.getline(input, 3);
        choice = atoi(input);
        cout << endl;
        
        choice = SearchPageError(choice, start, end);
        end = end + 10;

        // Continue display more or quit depending on the user's choice
    } while (DisplayPageError(choice) == 1);

    Change theChange = GetChangeDetails(CHANGEFILEPOINTER - choice * sizeof(Change), FILENAMES[1]);
    return UpdateChangeInfo(theChange.getChangeID(), choice);;
}
/*
Lists out 10 latest changes. 
Allow users to see more changes, select a change, or quit
No noticeable algorithm or data structure used.
--------------------------------------------------------------------*/
int UpdateChangeInfo(char* changeID, int location)
{
    Change theChange = GetChangeDetails(CHANGEFILEPOINTER - location * sizeof(Change), FILENAMES[1]);
    char product[11];
    char desc[31];
    char state[11];
    int priority;
    char relID[9];
    char choice;

    cout << "Updating product ";
    theChange.change_displayProductName();
    cout << endl << endl;
    cin.getline(product, 10);
    // if (!ValidateProduct()) return 0;
    
    // Description update option
    cout << "Update the description (Y/N)? ";
    cin >> choice;
    cout << endl;
    if (choice == 'Y')
    {
        cout << "Old Description: ";
        theChange.change_displayDesc();
        cout << endl;
        cout << "New Description: ";
        cin.getline(desc, 30);
        if (DescError(desc)) return 0;
    }
    cout << endl;

    // State update option
    cout << "Current state: "; 
    theChange.change_displayStatus();
    cout << " Update the state (Y/N)? ";
    cin >> choice;
    cout << endl;
    if (choice == 'Y')
    {
        cout << "New State (CANCELED/INPROGRESS/DONE): ";
        cin.getline(state, 10);
        if (StateError(state)) return 0;
    }
    cout << endl;

    // Priority update option
    cout << "Current priority: "; 
    theChange.change_displayPriority();
    cout << ". Update the priority (Y/N)? ";
    cin >> choice;
    cout << endl;
    if (choice == 'Y')
    {
        cout << "New Priority (Number between 1 and 5): ";
        cin >> priority;
        if (PriorityError(priority)) return 0;
    }
    cout << endl;

    // releaseID update
    cout << "Current anticipated releaseID: "; 
    theChange.change_displayRelID();
    cout << ". Update anticipated releaseID (Y/N)? ";
    cin >> choice;
    cout << endl;
    if (choice == 'Y')
    {
        cout << "New releaseID (maximum 8 characters): ";
        cin >> relID;
        if (ReleaseIDError(relID)) return 0;
    }
    cout << endl;

    // theChange.UpdateChange(changeID, desc, status, priority, relID);

    cout << "Updated product ";
    theChange.change_displayProductName();
    cout << " successfully" << endl;
    return 1;
}
/*
Let user update the attributes of change
Checks if it exists and in right format
No noticeable algorithm or data structure used.
--------------------------------------------------------------------*/
int DisplayChangeReport()
{
    int start = 1;
    int end = 11;
    int choice;

    cout << "CHANGE REPORT" << endl << endl;
    
    cout.width(2); cout << left << " ";
    cout.width(12); cout << left << "Product";
    cout.width(32); cout << left << "Description";
    cout.width(10); cout << left << "ChangeID";
    cout.width(12); cout << left << "Date";
    cout.width(11); cout << left << "Status";
    cout.width(10); cout << left << "Priority";
    cout.width(9); cout << left << "ReleaseID" << endl;
    
    do 
    {
        // Check if file is empty
        if (CHANGEFILEPOINTER == NULL)
        {
            cout << "No changes to show!" << endl;
            return 0;
        }
        // While it hasn't displayed 10 datas or hasn't reached to the end of file, display the datas
        while (start < end || CHANGEFILEPOINTER != NULL)
        {
            Change getChange = GetChangeDetails(CHANGEFILEPOINTER - start * sizeof(Change), FILENAMES[1]);
            cout.width(2); cout << left << start << " ";
            getChange.DisplayDetails(cout);
            start++;
        }
        // Get user choice
        cout << "Type 1 to show next list, 0 to quit: ";
        cin >> choice;
        cout << endl;
        end = end + 10;

        // Continue display more or quit depending on the user's choice
    } while (DisplayPageError(choice) == 1);
    return 1;
}
/*
Displays 10 latest changes.
Allow user to see more changes or quit.
No noticeable algorithm or data structure used.
--------------------------------------------------------------------*/
int ProductOnChange()
{
    char relID[9];
    int start = 1;
    int count = 1;
    int end = 11;
    int choice;

    cout << "===ReleaseID===" << endl;
    cout << "Enter the ReleaseID (max 8 characters): ";
    cin.getline(relID, 8);
    if (ReleaseIDError(relID)) return 0;
    Change dummy = Change("", ' ', '-', relID, "", "", "");
    cout << endl;

    cout << "ANTICIPATED CHANGES FOR " << "Product Name" << endl << endl;

    cout.width(2); cout << left << " ";
    cout.width(32); cout << left << "Description";
    cout.width(10); cout << left << "ChangeID";
    cout.width(12); cout << left << "Date";
    cout.width(11); cout << left << "Status";
    cout.width(10); cout << left << "Priority";
    cout.width(9); cout << left << "ReleaseID" << endl;

    do 
    {
        // Check if file is empty or not
        if (CHANGEFILEPOINTER == NULL)
        {
            cout << "No changes to show!" << endl;
            return 0;
        }
        // While it hasn't displayed 10 datas or hasn't reached to the end of file, display the datas
        while (count < end && CHANGEFILEPOINTER != NULL)
        {
            Change getChange = GetChangeDetails(CHANGEFILEPOINTER - start * sizeof(Change), FILENAMES[1]);
            if (getChange == dummy)
            {
                cout.width(2); cout << left << count << " ";
                getChange.DisplayDetails(cout);
                count++;
            }
            start++;
        }
        // Get user's choice
        cout << "Type 1 to show next list, 0 to quit: ";
        cin >> choice;
        cout << endl;
        end = end + 10;

        // Continue display more or quit depending on the user's choice
    } while (DisplayPageError(choice) == 1);
    return 1;
}
/*
Display changes for a specific releaseID.
Allow user to input a specific releaseID and look at the changes. 
This function uses linear search to find all changes that are related to the releaseID
--------------------------------------------------------------------*/
int UserOnChange()
{
    char product[9];
    int changeID[10];
    char input[3];
    int choice;
    int start = 1;
    int count = 1;
    int end = 11;

    // Gets the product
    cout << "===Product Name===" << endl;
    cout << "Enter the product name: ";
    cin.getline(product, 10);
    // if (!ValidateProduct()) return 0;
    Change changedummy = Change("", ' ', ' ', "", "", "", product);
    cout << endl;

    // List of the product's changes
    cout << "List of changes" << endl;

    cout.width(2); cout << left << " ";
    cout.width(32); cout << left << "Description";
    cout.width(10); cout << left << "ChangeID";
    cout.width(12); cout << left << "Date";
    cout.width(11); cout << left << "Status";
    cout.width(10); cout << left << "Priority";
    cout.width(9); cout << left << "ReleaseID" << endl;

    do 
    {
        // Check if the data file is empty or not
        if (CHANGEFILEPOINTER == NULL)
        {
            cout << "No changes to show!" << endl;
            return 0;
        }
        // While it hasn't displayed 10 datas or hasn't reached to the end of file, display the datas
        while (start < end && CHANGEFILEPOINTER != NULL)
        {
            Change getChange = GetChangeDetails(CHANGEFILEPOINTER - start * sizeof(Change), FILENAMES[1]);
            if (getChange == changedummy)
            {
                cout.width(2); cout << left << count << " ";
                getChange.DisplayDetails(cout);
                count++;
            }
            start++;
        }
        cout << "Type the number to the left of Change to select. ('1' to show the next list, '0' to quit): ";
        cin.getline(input, 3);
        choice = atoi(input);
        cout << endl;
        
        // Get user's choice
        choice = SearchPageError(choice, start, end);
        end = end + 10;

        // Continue display more or quit depending on the user's choice
    } while (choice == 1);

    if (choice == -1) return 0;
    Change theChange = GetChangeDetails(CHANGEFILEPOINTER - choice * sizeof(Change), FILENAMES[1]);
    Complaint complaintdummy = Complaint("", "", theChange.getChangeID(), "", ""); 
    choice = 0;
    count = 1;
    start = 1;
    end = 11;
    int iteration = 1;

    do 
    {
        // Check if file is empty or not
        if (CHANGEFILEPOINTER == NULL)
        {
            cout << "No changes to show!" << endl;
            return 0;
        }
        // Record first 10 userID who are associated with the changeID
        char *userIDlist[10]; 
        count = 0;
        // While the file pointer is not at the end or found less than 10 datas, keep tries to fetch the matching userID
        while (count < 10 && COMPLAINTFILEPOINTER != NULL )
        {
            Complaint getComplaint = GetComplaintDetails(COMPLAINTFILEPOINTER - sizeof(Complaint) * iteration, FILENAMES[2]);
            if (getComplaint == complaintdummy)
            {
                cout.width(2); cout << left << count;
                userIDlist[count] = getComplaint.getCustID();
                count++;
            }
            iteration++;
        }

        // Display the first 10 user information
        int iditeration = 1;
        int idcount = 0;
        // While the file pointer is not at the end or displayed less than 10 datas, keep tries to display the user information
        while (idcount < count && CUSTOMERFILEPOINTER != NULL)
        {
            Customer getCustomer = GetCustomerDetails(CUSTOMERFILEPOINTER - sizeof(Customer) * iditeration, FILENAMES[0]);
            if (getCustomer == userIDlist[count])
            {
                cout.width(2); cout << left << idcount;
                getCustomer.DisplayDetails(cout);
                idcount++;
            }
            iditeration++;
        }

        // Get user's choice
        cout << "Press '1' to go to the next page or '1' to quit viewing ";
        cin >> choice;
        cout << endl;
        
        start = end;
        end = end + 10;

        // Continue display more or quit depending on the user's choice
    } while (DisplayPageError(choice) == 1);
    return 1;
}
/*
Gets a specific changeID input from the user and see people associated with the change.
User can see the list of people.
This function uses linear search to find all users that are related to the releaseID
--------------------------------------------------------------------*/