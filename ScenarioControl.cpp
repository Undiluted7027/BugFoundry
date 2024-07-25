#include "ScenarioControl.hpp"
#include "Customer.cpp"
#include "Change.cpp"
#include "Product.cpp"
#include "ErrorMessages.cpp"
#include <iostream>
#include <cstring>

int ScenarioControl(int choice, int subchoice)
{
    switch (choice)
    {
    case 0:
        break;

    case 1:
        if (subchoice == 1)
            return NewCustomer();
        if (subchoice == 2)
            return CreateNewComplaint();
        if (subchoice == 3)
            return CreateNewProduct();
        if (subchoice == 4)
            return CreateNewProductRel();
        break;

    case 2:
        if (subchoice == 1)
            return UpdateSpecificChange();
        if (subchoice == 2)
            return ListAndSelectChange();
        break;

    case 3:
        if (subchoice == 1)
            return DisplayChangeReport();
        if (subchoice == 2)
            return ProductOnChange();
        if (subchoice == 3)
            return UserOnChange();
        break;

    default:
        std::cout << "Error: Your option is not an available choice" << std::endl;
        return 0;
    }
    return 1;
}

int NewCustomer()
{
    char name[31], email[25], phone[15];

    std::cout << "===Creating a User===" << std::endl;
    std::cout << "Enter full name (30 max characters): ";
    std::cin.getline(name, 30);
    std::cout << "Enter email (24 max characters): ";
    std::cin.getline(email, 24);
    std::cout << "Enter phone (eg. 1 604-723-1023): ";
    std::cin.getline(phone, 14);

    char choice;
    std::cout << "Confirm to create user (Y/N): ";
    std::cin >> choice;
    if (choice == 'N')
    {
        std::cout << "User Creation Canceled" << std::endl;
        return 0;
    }

    try
    {
        Customer newCustomer = CreateCustomer(name, email, phone);
        std::streampos pos = CUSTOMERFILEPOINTER;
        CommitCustomer(newCustomer, pos, FILENAMES[0]);
        std::cout << "New UserID: " << newCustomer.getCustID() << std::endl;
        std::cout << "User Successfully Created" << std::endl;
        return 1;
    }
    catch (const std::runtime_error &e)
    {
        std::cout << e.what() << std::endl;
        return 0;
    }
}

int CreateNewComplaint()
{
    char userID[11], relID[9], desc[31], product[11];

    std::cout << "===Creating a Complaint===" << std::endl;
    std::cout << "Enter your UserID (10 digits): ";
    std::cin.getline(userID, 11);
    std::cout << "Enter the Product the bug was found on: ";
    std::cin.getline(product, 11);
    std::cout << "Enter the Product ReleaseID that the bug was found on (8 letters): ";
    std::cin.getline(relID, 9);
    std::cout << "Enter Description of your complaint (30 max characters): ";
    std::cin.getline(desc, 31);

    char choice;
    std::cout << "Confirm to create complaint (Y/N): ";
    std::cin >> choice;
    if (choice == 'N')
    {
        std::cout << "Complaint Creation Canceled" << std::endl;
        return 0;
    }

    try
    {
        char date[9];
        // Get current date in format YY-MM-DD
        time_t now = time(0);
        strftime(date, sizeof(date), "%y-%m-%d", localtime(&now));

        Complaint newComplaint = CreateComplaint(desc, date, "", relID, userID);
        std::streampos pos = COMPLAINTFILEPOINTER;
        CommitComplaint(newComplaint, pos, FILENAMES[2]);

        Change newChange = CreateChange(desc, '-', '3', date, relID, "");
        pos = CHANGEFILEPOINTER;
        CommitChange(newChange, pos, FILENAMES[1]);

        std::cout << "Complaint Created Successfully" << std::endl;
        return 1;
    }
    catch (const std::runtime_error &e)
    {
        std::cout << e.what() << std::endl;
        return 0;
    }
}

// Implement other functions (CreateNewProduct, CreateNewProductRel, UpdateSpecificChange, etc.) similarly...

int DisplayChangeReport()
{
    int start = 0;
    int end = 10;
    int choice;

    std::cout << "CHANGE REPORT" << std::endl
              << std::endl;

    std::cout << std::left
              << std::setw(12) << "Product"
              << std::setw(32) << "Description"
              << std::setw(10) << "ChangeID"
              << std::setw(12) << "Date"
              << std::setw(11) << "Status"
              << std::setw(10) << "Priority"
              << std::setw(9) << "ReleaseID" << std::endl;

    do
    {
        std::streampos pos = CHANGEFILEPOINTER;
        for (int i = start; i < end; i++)
        {
            try
            {
                Change change = GetChangeDetails(pos, FILENAMES[1]);
                change.DisplayDetails(std::cout);
                pos = pos + static_cast<std::streamoff>(sizeof(Change));
            }
            catch (const std::runtime_error &e)
            {
                break;
            }
        }

        std::cout << "Type 1 to show next list, 0 to quit: ";
        std::cin >> choice;
        std::cout << std::endl;

        start = end;
        end = end + 10;
    } while (choice == 1);

    return 1;
}

int CreateNewProduct()
{
    char productName[11];
    std::cout << "===Create Product===" << std::endl;

    std::cout << "Enter the new product name (10 max characters): ";
    std::cin.getline(productName, 11);

    char choice;
    std::cout << "Confirm to create product (Y/N): ";
    std::cin >> choice;
    if (choice == 'N')
    {
        std::cout << "Product Creation Canceled" << std::endl;
        return 0;
    }

    try
    {
        Product newProduct = CreateProduct(productName, "", "");
        std::streampos pos = PRODUCTFILEPOINTER;
        CommitProduct(newProduct, pos, FILENAMES[3]);
        std::cout << "Product Created Successfully" << std::endl;
        return 1;
    }
    catch (const std::runtime_error &e)
    {
        std::cout << e.what() << std::endl;
        return 0;
    }
}

int CreateNewProductRel()
{
    char productName[11], releaseDate[11], releaseID[9];

    std::cout << "===Create Product Release===" << std::endl;
    std::cout << "Enter the product name (10 max characters): ";
    std::cin.getline(productName, 11);
    std::cout << "Enter the anticipated release date (YY/MM/DD): ";
    std::cin.getline(releaseDate, 11);
    std::cout << "Enter the new releaseID (8 max characters): ";
    std::cin.getline(releaseID, 9);

    char choice;
    std::cout << "Confirm to create product release (Y/N): ";
    std::cin >> choice;
    if (choice == 'N')
    {
        std::cout << "Product Release Creation Canceled" << std::endl;
        return 0;
    }

    try
    {
        Product newProductRelease = CreateProduct(productName, releaseID, releaseDate);
        std::streampos pos = PRODUCTFILEPOINTER;
        CommitProduct(newProductRelease, pos, FILENAMES[3]);
        std::cout << "Product Release Created Successfully" << std::endl;
        return 1;
    }
    catch (const std::runtime_error &e)
    {
        std::cout << e.what() << std::endl;
        return 0;
    }
}

int UpdateSpecificChange()
{
    char changeID[7];
    std::cout << "===ChangeID===" << std::endl;
    std::cout << "Enter the ChangeID (6 Digit ID): ";
    std::cin.getline(changeID, 7);

    try
    {
        std::streampos pos = CHANGEFILEPOINTER;
        Change changeToUpdate = GetChangeDetails(pos, FILENAMES[1]);
        while (strcmp(changeToUpdate.getChangeID(), changeID) != 0)
        {
            pos += sizeof(Change);
            changeToUpdate = GetChangeDetails(pos, FILENAMES[1]);
        }
        return UpdateChangeInfo(changeID, pos);
    }
    catch (const std::runtime_error &e)
    {
        std::cout << "Error: " << e.what() << std::endl;
        return 0;
    }
}

int ListAndSelectChange()
{
    int start = 0;
    int end = 10;
    char input[3];
    int choice;

    std::cout << "LATEST CHANGES" << std::endl
              << std::endl;

    std::cout << std::left
              << std::setw(2) << " "
              << std::setw(12) << "Product"
              << std::setw(32) << "Description"
              << std::setw(10) << "ChangeID"
              << std::setw(12) << "Date"
              << std::setw(11) << "Status"
              << std::setw(10) << "Priority"
              << std::setw(9) << "ReleaseID" << std::endl;

    do
    {
        std::streampos pos = CHANGEFILEPOINTER;
        for (int i = start; i < end; i++)
        {
            try
            {
                Change change = GetChangeDetails(pos, FILENAMES[1]);
                std::cout << std::setw(2) << i + 1 << " ";
                change.DisplayDetails(std::cout);
                pos += sizeof(Change);
            }
            catch (const std::runtime_error &e)
            {
                break;
            }
        }

        std::cout << "Type the number to select a change, '1' to show the next list, '0' to quit: ";
        std::cin.getline(input, 3);
        choice = atoi(input);

        if (choice > 0 && choice <= (end - start))
        {
            std::streampos selectedPos = CHANGEFILEPOINTER + static_cast<std::streamoff>((choice - 1) * sizeof(Change));
            Change selectedChange = GetChangeDetails(selectedPos, FILENAMES[1]);
            return UpdateChangeInfo(selectedChange.getChangeID(), selectedPos);
        }

        start = end;
        end += 10;
    } while (choice != 0);

    return 0;
}

int UpdateChangeInfo(const char *changeID, std::streampos position)
{
    Change theChange = GetChangeDetails(position, FILENAMES[1]);
    char description[31];
    char status;
    int priority;
    char releaseID[9];

    std::cout << "Updating Change " << changeID << std::endl;

    std::cout << "Current Description: " << theChange.change_displayDesc() << std::endl;
    std::cout << "Enter new Description (or press Enter to keep current): ";
    std::cin.getline(description, 31);
    if (description[0] == '\0')
    {
        strcpy(description, theChange.change_displayDesc());
    }

    std::cout << "Current Status: " << theChange.change_displayStatus() << std::endl;
    std::cout << "Enter new Status (P/X/-) (or press Enter to keep current): ";
    std::cin >> status;
    std::cin.ignore();
    if (status == '\n')
    {
        status = theChange.change_displayStatus();
    }

    std::cout << "Current Priority: " << theChange.change_displayPriority() << std::endl;
    std::cout << "Enter new Priority (1-5) (or press Enter to keep current): ";
    std::string priorityInput;
    std::getline(std::cin, priorityInput);
    if (priorityInput.empty())
    {
        priority = theChange.change_displayPriority() - '0';
    }
    else
    {
        priority = std::stoi(priorityInput);
    }

    std::cout << "Current ReleaseID: " << theChange.change_displayRelID() << std::endl;
    std::cout << "Enter new ReleaseID (or press Enter to keep current): ";
    std::cin.getline(releaseID, 9);
    if (releaseID[0] == '\0')
    {
        strcpy(releaseID, theChange.change_displayRelID());
    }

    theChange.UpdateChange(changeID, description, status, priority + '0', releaseID);

    CommitChange(theChange, position, FILENAMES[1]);

    std::cout << "Change updated successfully" << std::endl;
    return 1;
}

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
    if (ReleaseIDError(relID))
        return 0;
    cout << endl;

    cout << "ANTICIPATED CHANGES FOR " << "Product Name" << endl
         << endl;
    do
    {
        // if (CHANGEFILEPOINTER == Dummy)
        // {
        //     cout << "No changes to show!" << endl;
        //     return 0;
        // }
        while (count < end /*&& CHANGEFILEPOINTER != Dummy*/)
        {
            std::streampos changePos = CHANGEFILEPOINTER - static_cast<std::streamoff>(start * sizeof(Change));
            Change getChange = GetChangeDetails(changePos, FILENAMES[1]);
            // if (getChange.releaseID == relID)
            // {
            //     PrintChangeB(count, getChage.description, getChange.changeID, getChange.date, getChange.state, getChange.priority, getChange.ReleaseID);
            //     count++;
            // }
            start++;
        }
        cout << "Type 1 to show next list, 0 to quit: ";
        cin >> choice;
        cout << endl;
        end = end + 10;
    } while (DisplayPageError(choice) == 1);
    return 1;
}

/*
Gets a specific changeID input from the user and see people associated with the change.
User can see the list of people.
This function uses linear search to find all users that are related to the releaseID
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
        while (start < end /*&& CHANGEFILEPOINTER != Dummy*/)
        {
            std::streampos changePos = CHANGEFILEPOINTER - static_cast<std::streamoff>(start * sizeof(Change));
            Change getChange = GetChangeDetails(changePos, FILENAMES[1]);
            // if (getChange.ProductName == product)
            // {
            //     PrintChangeB(count, getChage.description, getChange.changeID, getChange.date, getChange.state, getChange.priority, getChange.ReleaseID);
            //     count++;
            // }
            start++;
        }
        cout << "Type the number to the left of Change to select. ('1' to show the next list, '0' to quit): ";
        cin.getline(input, 3);
        choice = atoi(input);
        cout << endl;

        choice = SearchPageError(choice, start, end);
        end = end + 10;
    } while (choice == 1);

    if (choice == -1)
        return 0;
    std::streampos changePos = CHANGEFILEPOINTER - static_cast<std::streamoff>(start * sizeof(Change));
    Change theChange = GetChangeDetails(changePos, FILENAMES[1]);
    choice = 0;
    count = 1;
    start = 1;
    end = 11;

    do
    {
        // if (COMPLAINTFILEPOINTER == Dummy)
        // {
        //     cout << "No users to show!" << endl;
        //     return 0;
        // }
        while (start < end /*&& COMPLAINTFILEPOINTER != Dummy*/)
        {

            std::streampos complaintPos = COMPLAINTFILEPOINTER - static_cast<std::streamoff>(sizeof(Complaint) * start);
Complaint getComplaint = GetComplaintDetails(complaintPos, FILENAMES[2]);
            // if (getComplaint.changeID == theChange.changeID)
            // {
            //     PrintUser(getComplaint.UserID.name, getComplaint.UserID.email);
            //     count++;
            // }
            start++;
        }
        cout << "Press '1' to go to the next page or '1' to quit viewing ";
        cin >> choice;
        cout << endl;

        start = end;
        end = end + 10;
    } while (DisplayPageError(choice) == 1);
    return 1;
}


int InitControl(){
    int CustomerStart = InitCustomer();
    int ComplaintStart = InitComplaint();
    int ChangeStart = InitChange();
    int ProductStart = InitProduct();
    if (CustomerStart == -1 || ComplaintStart == -1 || ChangeStart == -1 || ProductStart == -1)
        return 0;
    return 1;
}