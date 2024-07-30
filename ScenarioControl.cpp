#include "ScenarioControl.hpp"
#include "Customer.cpp"
#include "Change.cpp"
#include "Product.cpp"
#include "ErrorMessages.cpp"
#include <iostream>
#include <cstring>

// 967774000
// 144721

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
    std::string name;
    std::string email;
    std::string phone;

    std::cout << "===Creating a User===" << std::endl;
    std::cin.ignore();
    std::cout << "Enter full name (30 max characters): ";
    std::getline(std::cin, name);
    std::cout << "Enter email (24 max characters): ";
    std::getline(std::cin, email);
    std::cout << "Enter phone (eg. [1]6047231023): ";
    std::getline(std::cin, phone);

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
        Customer newCustomer = CreateCustomer(name.data(), email.data(), phone.data());
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
    // char* generatedID = IDGenerator('3', 6);
    // cout << endl << generatedID << endl;

    std::string userID;
    std::string relID;
    std::string desc;
    std::string product;

    std::cout << "===Creating a Complaint===" << std::endl;
    std::cin.ignore();
    PrintAllCustomers(FILENAMES[0]);
    std::cout << "Enter your UserID (9 digits): ";
    std::getline(std::cin, userID);
    std::cout << "Enter the Product the bug was found on: ";
    std::getline(std::cin, product);
    std::cout << "Enter the Product ReleaseID that the bug was found on (8 letters): ";
    std::getline(std::cin, relID);
    std::cout << "Enter Description of your complaint (30 max characters): ";
    std::getline(std::cin, desc);

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
        char date[11];
        // Get current date in format YYYY-MM-DD
        time_t now = time(0);
        strftime(date, sizeof(date), "%Y-%m-%d", localtime(&now));

        Complaint newComplaint = CreateComplaint(desc.data(), date, relID.data(), userID.data());
        // std::streampos pos = COMPLAINTFILEPOINTER;
        // CommitComplaint(newComplaint, pos, FILENAMES[2]);

        // Change newChange = CreateChange(desc.data(), '-', '3', date, relID.data());
        // pos = CHANGEFILEPOINTER;
        // CommitChange(newChange, pos, FILENAMES[1]);

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
              << std::setw(10) << "ChangeID"
              << std::setw(15) << "Product Name"
              << std::setw(32) << "Description"
              << std::setw(12) << "Last Update"
              << std::setw(7) << "Status"
              << std::setw(10) << "Priority"
              << std::setw(32) << "ReleaseID/Anticipated ReleaseID" << std::endl;
    std::cout << std::string(118, '-') << std::endl;

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

    std::cin.ignore();
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
    std::string productName;
    std::string releaseDate;
    std::string releaseID;
    PrintAllProducts(FILENAMES[3]);
    std::cout << "===Create Product Release===" << std::endl;
    std::cin.ignore();
    std::cout << "Enter the product name (10 max characters): ";
    std::getline(std::cin, productName);
    std::cout << "Enter the anticipated release date (YYYY-MM-DD): ";
    std::getline(std::cin, releaseDate);
    std::cout << "Enter the new/anticipated releaseID (8 max characters): ";
    std::getline(std::cin, releaseID);

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
        Product newProductRelease = CreateProduct(productName.data(), releaseID.data(), releaseDate.data());
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
    std::string changeID;
    std::cout << "===ChangeID===" << std::endl;
    std::cin.ignore();
    std::cout << "Enter the ChangeID (6 Digit ID): ";
    std::getline(std::cin, changeID);

    try
    {
        std::streampos pos = CHANGEFILEPOINTER;
        Change changeToUpdate = GetChangeDetails(pos, FILENAMES[1]);
        while (strcmp(changeToUpdate.getChangeID(), changeID.data()) != 0)
        {
            pos += sizeof(Change);
            changeToUpdate = GetChangeDetails(pos, FILENAMES[1]);
        }
        return UpdateChangeInfo(changeID.data(), pos);
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
              << std::setw(10) << "ChangeID"
              << std::setw(15) << "Product Name"
              << std::setw(32) << "Description"
              << std::setw(12) << "Last Update"
              << std::setw(7) << "Status"
              << std::setw(10) << "Priority"
              << std::setw(32) << "ReleaseID/Anticipated ReleaseID" << std::endl;
    std::cout << std::string(118, '-') << std::endl;

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
        std::cin.ignore();
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
    char status;
    int priority;

    std::string description;
    std::string releaseID;

    std::cout << "Updating Change " << changeID << std::endl;

    std::cout << "Current Description: " << theChange.change_displayDesc() << std::endl;
    std::cout << "Enter new Description (or press Enter to keep current): ";
    std::getline(std::cin, description);
    if (description[0] == '\0')
    {
        strcpy(description.data(), theChange.change_displayDesc());
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
    std::getline(std::cin, releaseID);
    if (releaseID[0] == '\0')
    {
        strcpy(releaseID.data(), theChange.change_displayRelID());
    }

    theChange.UpdateChange(changeID, description.data(), status, priority + '0', releaseID.data());

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
    std::string changeID;
    PrintAllComplaints(FILENAMES[2]);
    PrintAllChanges(FILENAMES[1]);
    std::cout << "Enter Change ID (max 5 digits starting with 1): ";
    std::cin.ignore();
    std::getline(std::cin, changeID);
    // if (strlen(changeID.data()) > 6) validation for incorrect changeID
    CreateUsersInformedOnUpdateReport(changeID.data());
    return 1;
}

int InitControl()
{
    int CustomerStart = InitCustomer();
    int ComplaintStart = InitComplaint();
    int ChangeStart = InitChange();
    int ProductStart = InitProduct();
    if (CustomerStart == -1 || ComplaintStart == -1 || ChangeStart == -1 || ProductStart == -1)
        return 0;
    return 1;
}