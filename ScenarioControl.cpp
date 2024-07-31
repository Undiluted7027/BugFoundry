#include "ScenarioControl.hpp"
#include "Customer.cpp"
#include "Change.cpp"
#include "Product.cpp"
#include "ErrorMessages.cpp"
#include "Exceptions.hpp"
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
    catch (const FileException &e)
    {
        LogException(e);
        return -1;
    }
    catch (const InvalidDataException &e)
    {
        LogException(e);
        return -1;
    }
    catch (const DuplicateRecordException &e)
    {
        LogException(e);
        return 0;
    }
    catch (const NoRecordFound &e)
    {
        LogException(e);
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

        Complaint newComplaint = CreateComplaint(desc.data(), date, relID.data(), userID.data(), product.data());
        std::cout << "Complaint Created Successfully" << std::endl;
        return 1;
    }
    catch (const FileException &e)
    {
        LogException(e);
        return -1;
    }
    catch (const InvalidDataException &e)
    {
        LogException(e);
        return -1;
    }
    catch (const DuplicateRecordException &e)
    {
        LogException(e);
        return 0;
    }
    catch (const NoRecordFound &e)
    {
        LogException(e);
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
    catch (const FileException &e)
    {
        LogException(e);
        return -1;
    }
    catch (const InvalidDataException &e)
    {
        LogException(e);
        return -1;
    }
    catch (const DuplicateRecordException &e)
    {
        LogException(e);
        return 0;
    }
    catch (const NoRecordFound &e)
    {
        LogException(e);
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
    catch (const FileException &e)
    {
        LogException(e);
        return -1;
    }
    catch (const InvalidDataException &e)
    {
        LogException(e);
        return -1;
    }
    catch (const DuplicateRecordException &e)
    {
        LogException(e);
        return 0;
    }
    catch (const NoRecordFound &e)
    {
        LogException(e);
        return 0;
    }
}

int UpdateSpecificChange()
{
    std::string changeID;
    PrintAllChanges(FILENAMES[1]);
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
    catch (const FileException &e)
    {
        LogException(e);
        return -1;
    }
    catch (const InvalidDataException &e)
    {
        LogException(e);
        return -1;
    }
    catch (const DuplicateRecordException &e)
    {
        LogException(e);
        return 0;
    }
    catch (const NoRecordFound &e)
    {
        LogException(e);
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
            catch (const FileException &e)
            {
                LogException(e);
                return -1;
            }
            catch (const InvalidDataException &e)
            {
                LogException(e);
                return -1;
            }
            catch (const DuplicateRecordException &e)
            {
                LogException(e);
                return 0;
            }
            catch (const NoRecordFound &e)
            {
                LogException(e);
                return 0;
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
    std::fstream file(FILENAMES[1], std::ios::in | std::ios::out | std::ios::binary);
    if (!file)
    {
        std::cerr << "Error: could not open file for reading" << std::endl;
        return -1;
    }
    Change currentChange;
    bool changeFound = false;
    while (file.read(reinterpret_cast<char *>(&currentChange), sizeof(Change)))
    {
        if (strcmp(currentChange.getChangeID(), changeID) == 0)
        {
            cout << "Change found!" << endl;
            changeFound = true;
            break;
        }
    }
    if (changeFound)
    {
        std::string description, releaseID, productName, status;
        char priority;

        cout << "Updating Change with ChangeID: " << changeID << endl;
        cout << "Current Description: " << currentChange.change_displayDesc() << endl;
        cout << "Enter new Description (or press Enter to keep current): ";
        std::getline(std::cin, description);
        if (description == "")
            description = currentChange.change_displayDesc();
        cout << "Current Status: " << currentChange.change_displayStatus() << endl;
        cout << "Enter new Status (P/X/-) (or press Enter to keep current): ";
        std::getline(std::cin, status);
        if (status.empty())
            status = currentChange.change_displayStatus();
        cout << "Current Priority: " << currentChange.change_displayPriority() << endl;
        cout << "Enter new Priority (1-5) (or press Enter to keep current): ";

        do
        {
            cin >> priority;
        } while (priority == '\0' || priority < 48 || priority > 54);
        if (priority == '\0')
            priority = currentChange.change_displayPriority();
        cout << "Current ReleaseID: " << currentChange.change_displayRelID() << endl;
        cout << "Enter new ReleaseID (or press Enter to keep current): ";
        // std::getline(std::cin, releaseID);
        do
        {
            // cout << "Product doesn't exist." << endl;
            cin.ignore();
            std::getline(std::cin, releaseID);
            if (releaseID.empty())
                break;
        } while (checkDupProduct(releaseID.data()));

        if (releaseID.empty())
            releaseID = currentChange.change_displayRelID();
        try
        {
            currentChange.UpdateChange(currentChange.getChangeID(), description.data(), status[0], priority, releaseID.data());
            CommitUpdatedChange(currentChange, FILENAMES[1]);
        }
        catch (const FileException &e)
        {
            LogException(e);
            return -1;
        }
        catch (const InvalidDataException &e)
        {
            LogException(e);
            return -1;
        }
        catch (const DuplicateRecordException &e)
        {
            LogException(e);
            return 0;
        }
        catch (const NoRecordFound &e)
        {
            LogException(e);
            return 0;
        }
    }

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
    cin.ignore();
    cin.getline(relID, 8);
    if (!checkDupProduct(relID))
    {
        cout << "Product doesn't exist." << endl;
        return -1;
    }
    cout << endl;

    cout << "ANTICIPATED CHANGES FOR " << "Product with ReleaseID: " << relID << endl
         << endl;
    try
    {
        CreateAnticipatedChangesProduct(relID);
    }
    catch (const FileException &e)
    {
        LogException(e);
        return -1;
    }
    catch (const InvalidDataException &e)
    {
        LogException(e);
        return -1;
    }
    catch (const DuplicateRecordException &e)
    {
        LogException(e);
        return 0;
    }
    catch (const NoRecordFound &e)
    {
        LogException(e);
        return 0;
    }
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
    try
    {
        CreateUsersInformedOnUpdateReport(changeID.data());
    }
    catch (const FileException &e)
    {
        LogException(e);
        return -1;
    }
    catch (const InvalidDataException &e)
    {
        LogException(e);
        return -1;
    }
    catch (const DuplicateRecordException &e)
    {
        LogException(e);
        return 0;
    }
    catch (const NoRecordFound &e)
    {
        LogException(e);
        return 0;
    }
    return 1;
}

int InitControl()
{
    try
    {
        InitCustomer();
        InitComplaint();
        InitChange();
        InitProduct();
        return 1;
    }
    catch (const FileException &e)
    {
        LogException(e);
        return 0;
    }
}