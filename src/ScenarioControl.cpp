/* ScenarioControl.cpp
REVISION HISTORY:
Rev. 2 - 24/07/11 Edited by Sanchit Jain
Rev. 1 - 24/07/03 Original by Jason Lee
----------------------------------------------------------------------*/

#include <iostream>
#include <cstring>
#include "../include/ScenarioControl.hpp"

//----------------------------------------------------------------------

/*
Handles which scenario to run based on the choices made by the user.
----------------------------------------------------------------------*/
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

/*
Creating new customer scenario.
Gets all information of the new customer, validates all information.
If validates, proceed to create new customer object and store the object into the data file
--------------------------------------------------------------------------*/
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

/*
Creating new complaint scenario.
Gets all information of the new complaint, validates all information.
If validates, proceed to create new complaint object and store the object into the data file
----------------------------------------------------------------------*/
int CreateNewComplaint()
{
    std::string userID;
    std::string relID;
    std::string desc;
    std::string product;

    std::cout << std::endl << "===Creating a Complaint===" << std::endl;
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

/*
Display changes report scenario.
Gets all change object and present its information to the user.
-----------------------------------------------------------------------------------------------*/
int DisplayChangeReport()
{
    std::cout << "CHANGE REPORT" << std::endl
              << std::endl;

    try
    {
        CreateChangesReport();
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
Creating new product scenario.
Gets all information of the new product, validates all information.
If validates, proceed to create new product object and store the object into the data file
--------------------------------------------------------------------------------*/
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

/*
Creating new product release scenario.
Gets all information of the new product release object and validates all information.
If validates, proceed to create new product release object and store the object into the data file
------------------------------------------------------------------------------------------------*/
int CreateNewProductRel()
{
    std::string productName;
    std::string releaseDate;
    std::string releaseID;
    PrintAllProducts(FILENAMES[3]);
    std::cout << std::endl << "===Create Product Release===" << std::endl;
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

/*
Updating a specific change scenario.
Find a change object in the data file that the user want to update its attribute information
------------------------------------------------------------------------------------*/
int UpdateSpecificChange()
{
    int start = 0;
    int end = 10;
    int choice;
    string input;
    std::streampos pos = CHANGEFILEPOINTER;
    Change change;

    std::cout << "===Update Specific Change===" << std::endl;

    // Display changes in a paginated manner
    do
    {
        pos = CHANGEFILEPOINTER;
        std::cout << std::endl << "AVAILABLE CHANGES" << std::endl
                  << std::endl;
        std::cout << std::left
                  << std::setw(7) << " "
                  << std::setw(10) << "ChangeID"
                  << std::setw(15) << "Product Name"
                  << std::setw(32) << "Description"
                  << std::setw(12) << "Last Update"
                  << std::setw(7) << "Status"
                  << std::setw(10) << "Priority"
                  << std::setw(32) << "ReleaseID" << std::endl;
        std::cout << std::string(123, '-') << std::endl;
        bool hasMoreChanges = false;

        for (int i = start; i < end; i++)
        {
            try
            {
                change = GetChangeDetails(pos, FILENAMES[1]);
                std::cout << std::setw(6) << i + 1 << " ";
                change.DisplayDetails(std::cout);
                std::cout << std::string(123, '-') << std::endl;

                pos += sizeof(Change);
                hasMoreChanges = true;
            }
            catch (const NoRecordFound &e)
            {
                hasMoreChanges = false;
            }
            catch (const AppException &e)
            {
                LogException(e);
                return -1;
            }
        }

        if (hasMoreChanges)
            std::cout << "Type the number to select a change, 'N' to show the next list, '0' to quit: ";
        else
            std::cout << "Type the number to select a change, '0' to quit: ";

        do
        {
            // std::cin.ignore();
            std::getline(std::cin, input);
            choice = char(input[0]);
            if (choice == 'N' && !hasMoreChanges)
            {
                std::cout << "No more changes to show. Can't use 'N'" << std::endl;
                std::cout << "Type the number to select a change, '0' to quit: ";
            }
            else if (choice == 'N' || choice == '0')
                break;
        } while (choice < '0' || choice > '9');

        if (choice != 'N' && choice != '0')
        {
            int selectedIndex = choice - '0';

            if (selectedIndex > 0 && selectedIndex <= (end - start))
            {
                std::streampos selectedPos = CHANGEFILEPOINTER + static_cast<std::streamoff>((selectedIndex - 1) * sizeof(Change));
                try
                {
                    Change selectedChange = GetChangeDetails(selectedPos, FILENAMES[1]);
                    std::string changeID = selectedChange.getChangeID();
                    return UpdateChangeInfo(changeID.data(), selectedPos);
                }
                catch (const AppException &e)
                {
                    LogException(e);
                    return -1;
                }
            }
        }

        start = end;
        end += 10;
    } while (choice != '0');

    return 0;
}

/*
Display a list of recent changes and allow user to select one of changes
they want to edit its attribute information.
------------------------------------------------------------------------------------*/
int ListAndSelectChange()
{
    int start = 0;
    int end = 10;
    string input;
    int choice;
    bool hasMoreChanges = true;

    std::cout << "LATEST CHANGES" << std::endl
              << std::endl;

    std::cout << std::left
              << std::setw(6) << " "
              << std::setw(10) << "ChangeID"
              << std::setw(15) << "Product Name"
              << std::setw(32) << "Description"
              << std::setw(12) << "Last Update"
              << std::setw(7) << "Status"
              << std::setw(10) << "Priority"
              << std::setw(32) << "ReleaseID" << std::endl;
    std::cout << std::string(118, '-') << std::endl;

    do
    {
        std::streampos pos = CHANGEFILEPOINTER;
        for (int i = start; i < end; i++)
        {
            try
            {
                Change change = GetChangeDetails(pos, FILENAMES[1]);
                std::cout << std::setw(6) << i + 1 << " ";
                change.DisplayDetails(std::cout);
                std::cout << std::string(118, '-') << std::endl;

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
                hasMoreChanges = false;
                break;
            }
        }
        if (hasMoreChanges)
            std::cout << "Type the number to select a change, 'N' to show the next list, '0' to quit: ";
        else
            std::cout << "Type the number to select a change, '0' to quit: ";
        do
        {
            // std::cin.ignore();
            std::getline(std::cin, input);
            choice = char(input[0]);
            if (choice == 'N' && !hasMoreChanges)
            {
                std::cout << "No more changes to show. Can't use 'N'" << std::endl;
                std::cout << "Type the number to select a change, '0' to quit: ";
            }
            else if (choice == 'N' || choice == '0')
                break;
        } while (choice < '0' || choice > '9');

        if (choice != 'N' && choice != '0')
        {
            int selectedIndex = choice - '0';

            if (selectedIndex > 0 && selectedIndex <= (end - start))
            {
                std::streampos selectedPos = CHANGEFILEPOINTER + static_cast<std::streamoff>((selectedIndex - 1) * sizeof(Change));
                try
                {
                    Change selectedChange = GetChangeDetails(selectedPos, FILENAMES[1]);
                    return UpdateChangeInfo(selectedChange.getChangeID(), selectedPos);
                }
                catch (const AppException &e)
                {
                    LogException(e);
                    return -1;
                }
            }
        }

        start = end;
        end += 10;
    } while (choice != '0');

    return 0;
}

/*
Given the changeID of a change object to update its attribute,
get new attribute information, validate the new information, and apply the information
to the change object.
-------------------------------------------------------------------------------------------*/
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
            // cout << "Change found!" << endl;
            changeFound = true;
            break;
        }
    }
    if (changeFound)
    {
        std::string description, releaseID, productName, status, priority_input;
        char priority = '\0';

        cout << endl << "Updating Change with ChangeID: " << changeID << endl;
        cout << "Current Description: " << currentChange.change_displayDesc() << endl;
        cout << "Enter new Description (or press Enter to keep current): ";
        std::getline(std::cin, description);
        if (description == "")
            description = currentChange.change_displayDesc();
        cout << endl << "Current Status: " << currentChange.change_displayStatus() << endl;
        cout << "Enter new Status (P/X/-) (or press Enter to keep current): ";
        std::getline(std::cin, status);
        if (status.empty())
            status = currentChange.change_displayStatus();
        cout << endl << "Current Priority: " << currentChange.change_displayPriority() << endl;
        cout << "Enter new Priority (1-5) (or press Enter to keep current): ";

        do
        {
            // cin.ignore();
            std::getline(std::cin, priority_input);
            if (priority_input.empty())
                break;
            priority = priority_input[0];
        } while (priority < 48 || priority > 54);
        if (priority == '\0')
            priority = currentChange.change_displayPriority();
        cout << endl << "Current ReleaseID: " << currentChange.change_displayRelID() << endl;
        cout << "Enter new ReleaseID (or press Enter to keep current): ";
        // std::getline(std::cin, releaseID);
        do
        {
            // cout << "Product doesn't exist." << endl;
            // cin.ignore();
            std::getline(std::cin, releaseID);
            if (releaseID.empty())
                break;
        } while (checkDupProduct(releaseID.data()));

        if (releaseID.empty())
            releaseID = currentChange.change_displayRelID();
        try
        {
            char date[11];
            // Get current date in format YYYY-MM-DD
            time_t now = time(0);
            strftime(date, sizeof(date), "%Y-%m-%d", localtime(&now));
            currentChange.UpdateChange(currentChange.getChangeID(), description.data(), status[0], priority, releaseID.data(), date);
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

/*
Creates a report of all changes object that is associated with a particular product object.
This function uses linear search to find all changes that are related to the prduct.
---------------------------------------------------------------------------------------------*/
int ProductOnChange()
{
    int start = 0;
    int end = 10;
    int cc = 0;
    string input;
    char choice;
    std::streampos pos;
    Product product;

    do
    {
        pos = PRODUCTFILEPOINTER;
        std::cout << "AVAILABLE PRODUCTS" << std::endl
                  << std::endl;
        std::cout << std::left
                  << std::setw(6) << " "
                  << std::setw(15) << "Product Name"
                  << std::setw(25) << "ReleaseID"
                  << std::setw(18) << "ReleaseDate" << std::endl;
        std::cout << std::string(123, '-') << std::endl;
        bool hasMoreProducts = false;

        for (int i = start; i < end; i++)
        {
            try
            {
                product = GetProductDetails(pos, FILENAMES[3]);
                std::cout << i + 1 << std::setw(5) << " ";
                product.DisplayDetails(std::cout);
                std::cout << std::string(123, '-') << std::endl;

                pos += sizeof(Product);
                hasMoreProducts = true;
            }
            catch (const NoRecordFound &e)
            {
                hasMoreProducts = false;
            }
        }

        if (hasMoreProducts)
        {
            std::cout << "Type the number to select a product, 'N' to show the next list, '0' to quit: ";
        }
        else
        {
            std::cout << "Type the number to select a product, '0' to quit: ";
        }

        do
        {
            std::getline(std::cin, input);
            choice = input[0];
            if (choice == 'N' && !hasMoreProducts)
            {
                std::cout << "No more products to show. Can't use 'N'" << std::endl;
                std::cout << "Type the number to select a product, '0' to quit: ";
            }
            else if (choice == 'N')
                break;
        } while (choice < '0' || choice > '9');

        if (choice != 'N' && choice != '0')
        {
            cc = choice - '0';

            if (cc > 0 && cc <= (end - start))
            {
                std::streampos selectedPos = PRODUCTFILEPOINTER + static_cast<std::streamoff>((cc - 1) * sizeof(Product));
                try
                {
                    Product selectedProduct = GetProductDetails(selectedPos, FILENAMES[3]);
                    std::string relID = selectedProduct.getReleaseID();
                    CreateAnticipatedChangesProduct(relID.c_str());
                    return 1;
                }
                catch (const AppException &e)
                {
                    LogException(e);
                    return -1;
                }
            }
        }
        else
            break;

        start = end;
        end += 10;
    } while (cc != 0);

    return 0;
}

/*
Gets a specific changeID input from the user and see people associated with the change.
User can see the list of people.
This function uses linear search to find all users that are related to the releaseID
--------------------------------------------------------------------*/
int UserOnChange()
{
    int start = 0;
    int cc = 0;
    int end = 10;
    string input;
    char choice;
    std::streampos pos;
    Change change;

    do
    {
        pos = CHANGEFILEPOINTER;
        std::cout << "AVAILABLE CHANGES" << std::endl
                  << std::endl;
        std::cout << std::left
                  << std::setw(7) << " "
                  << std::setw(10) << "ChangeID"
                  << std::setw(15) << "Product Name"
                  << std::setw(32) << "Description"
                  << std::setw(12) << "Last Update"
                  << std::setw(7) << "Status"
                  << std::setw(10) << "Priority"
                  << std::setw(32) << "ReleaseID" << std::endl;
        std::cout << std::string(123, '-') << std::endl;
        bool do10 = true;
        for (int i = start; i < end; i++)
        {
            try
            {
                change = GetChangeDetails(pos, FILENAMES[1]);
                std::cout << std::setw(6) << i + 1 << " ";
                change.DisplayDetails(std::cout);
                std::cout << std::string(123, '-') << std::endl;

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
                do10 = false;
            }
        }
        if (do10)
            std::cout << "Type the number to select a change, 'N' to show the next list, '0' to quit: ";
        else
            std::cout << "Type the number to select a change, '0' to quit: ";

        do
        {
            std::getline(std::cin, input);
            choice = input[0];
            if (choice == 'N' && !do10)
            {
                std::cout << "No more products to show. Can't use 'N'" << std::endl;
                std::cout << "Type the number to select a product, '0' to quit: ";
            }
            else if (choice == 'N')
                break;
        } while (choice < '0' || choice > '9');
        if (choice != 'N' && choice != '0')
        {
            cc = choice - '0';

            if (cc > 0 && cc <= (end - start))
            {
                std::streampos selectedPos = CHANGEFILEPOINTER + static_cast<std::streamoff>((cc - 1) * sizeof(Change));
                try
                {
                    Change selectedChange = GetChangeDetails(selectedPos, FILENAMES[1]);
                    std::string changeID = selectedChange.getChangeID();
                    CreateUsersInformedOnUpdateReport(changeID.c_str());
                    return 1;
                }
                catch (const AppException &e)
                {
                    LogException(e);
                    return -1;
                }
            }
        }
        else
            break;

        start = end;
        end += 10;
    } while (cc != 0);

    return 0;
}

/*
Initializes all data classes: customer, complaint, change, and product.
-----------------------------------------------------------------------*/
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