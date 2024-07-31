/* ScenarioControl.hpp
REVISION HISTORY:
Rev. 2 - 24/07/16 Revised by Sanchit Jain
Rev. 1 - 24/07/03 Original by Jason Lee
----------------------------------------------------------------------
This CPP file called ScenarioControl.cpp all possible scenarios in the program.
--------------------------------------------------------------------*/
#include "ScenarioControl.hpp"
#include "Customer.cpp"
#include "Change.cpp"
#include "Product.cpp"
#include "ErrorMessages.cpp"
#include "Exceptions.hpp"
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
ScenarioControl identifies which scenario is chosen and execute that scenario
No noticeable algorithm or data structure used. 
----------------------------------------------------------------*/
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
Takes new user's information input and tries to commit the new customer into file
No noticeable algorithm or data structure used. 
----------------------------------------------------------------*/
int CreateNewComplaint()
{
    int start = 0;
    int end = 10;
    int choice;
    std::string input;
    Customer customer;
    std::string userID;
    std::string relID;
    std::string desc;
    std::string product;
        std::streampos pos = CUSTOMERFILEPOINTER + static_cast<std::streamoff>(sizeof(int));

    std::cout << "===Creating a Complaint===" << std::endl;

    // Display customers in a paginated manner
    do
    {
        std::cout << "AVAILABLE CUSTOMERS" << std::endl
                  << std::endl;
        std::cout << std::left
                  << std::setw(5) << " "
                  << std::setw(10) << "UserID"
                  << std::setw(20) << "Name"
                  << std::setw(15) << "Email"
                  << std::setw(15) << "Phone Number" << std::endl;
        std::cout << std::string(60, '-') << std::endl;
        bool hasMoreCustomers = false;

        for (int i = start; i < end; i++)
        {
            try
            {
                customer = GetCustomerDetails(pos, FILENAMES[0]);
                std::cout << std::setw(5) << i + 1 << " ";
                customer.DisplayDetails(std::cout);
                pos += sizeof(Customer);
                hasMoreCustomers = true;
            }
            catch (const NoRecordFound &e)
            {
                hasMoreCustomers = false;
                break;
            }
            catch (const AppException &e)
            {
                LogException(e);
                return -1;
            }
        }

        if (hasMoreCustomers)
            std::cout << "Type the number to select a customer, 'N' to show the next list, '0' to quit: ";
        else
            std::cout << "Type the number to select a customer, '0' to quit: ";

        do
        {
            std::getline(std::cin, input);
            choice = input[0];
            if (choice == 'N' && !hasMoreCustomers)
            {
                std::cout << "No more customers to show. Can't use 'N'" << std::endl;
                std::cout << "Type the number to select a customer, '0' to quit: ";
            }
            else if (choice == 'N')
                break;
        } while (choice < '0' || choice > '9');

        if (choice != 'N' && choice != '0')
        {
            int selectedIndex = choice - '0';

            if (selectedIndex > 0 && selectedIndex <= (end - start))
            {
                std::streampos p = CUSTOMERFILEPOINTER; // Skipping total records

                std::streampos selectedPos = p + static_cast<std::streamoff>((selectedIndex - 1) * static_cast<std::streamoff>(sizeof(Change)));
                try
                {
                    Customer selectedCustomer = GetCustomerDetails(selectedPos, FILENAMES[0]);
                    userID = selectedCustomer.getCustID();
                    break;
                }
                catch (const AppException &e)
                {
                    LogException(e);
                    return -1;
                }
            }
        }
        else if (choice == '0')
        {
            std::cout << "Complaint Creation Canceled" << std::endl;
            return 0;
        }

        start = end;
        end += 10;
    } while (choice != '0');

    std::cout << "Enter the Product the bug was found on: ";
    std::getline(std::cin, product);
    std::cout << "Enter the Product ReleaseID that the bug was found on (8 letters): ";
    std::getline(std::cin, relID);
    std::cout << "Enter Description of your complaint (30 max characters): ";
    std::getline(std::cin, desc);

    char confirm;
    std::cout << "Confirm to create complaint (Y/N): ";
    std::cin >> confirm;
    if (confirm == 'N')
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
Takes new complaint information input and tries to commit the new complaint into file
No noticeable algorithm or data structure used.
----------------------------------------------------------------*/
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
Displays the recent 10 changes. User can choose to display the next 10 changes
Goes through the unsorted change file to get the change data
----------------------------------------------------------------*/
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
Gets new product information input and tries to commit the new product in file
No noticeable algorithm or data structure used.
----------------------------------------------------------------*/
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
/*
Gets new product release information input and tries to commit it in file
No noticeable algorithm or data structure used.
----------------------------------------------------------------*/
int UpdateSpecificChange()
{
    std::string changeID;
    PrintAllChanges(FILENAMES[1]);
    std::cout << "===ChangeID===" << std::endl;
    std::cin.ignore();
    int dupFound = 0;
    do
    {
        std::cout << "Enter the ChangeID (6 Digit ID): ";

        std::getline(std::cin, changeID);
        dupFound = checkChangeDup(changeID.data());
        if (dupFound == 0)
            std::cout << "Invalid ChangeID. Please enter a valid ChangeID." << endl;
    } while (dupFound != 1);

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
    string input;
    std::streampos pos = CHANGEFILEPOINTER + static_cast<std::streamoff>(sizeof(int)); // Start after total records field
    int choice;
    bool hasMoreChanges = true;

    std::cout << "LATEST CHANGES" << std::endl
              << std::endl;

    std::cout << std::left
              << std::setw(5) << " "
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
        pos = CHANGEFILEPOINTER + static_cast<std::streamoff>(sizeof(int)) + start * static_cast<std::streamoff>(sizeof(Change)); // Adjust pos for new start
        for (int i = start; i < end; i++)
        {
            try
            {
                Change change = GetChangeDetails(pos, FILENAMES[1]);
                std::cout << std::setw(5) << i + 1 << " ";
                // Display the details of the change (assuming you have a method to do so)
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
        std::cin.ignore();
        std::getline(std::cin, input);
        if (input.empty())
        {
            std::cout << "Invalid input, please try again." << std::endl;
            continue;
        }

        choice = input[0];

        if (choice == 'N' || choice == 'n')
        {
            if (!hasMoreChanges)
            {
                std::cout << "No more changes to show. Can't use 'N'" << std::endl;
                continue;
            }
        }
        else if (choice == '0')
        {
            break; // Exit the loop
        }
        else if (isdigit(choice))
        {
            int selectedIndex = choice - '0';

            if (selectedIndex > 0 && selectedIndex <= (end - start))
            {
                std::streampos p = CHANGEFILEPOINTER + static_cast<std::streamoff>(sizeof(int)); // Start after total records
                std::streampos selectedPos = p + static_cast<std::streamoff>((selectedIndex - 1 + start) * sizeof(Change));

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
            else
            {
                std::cout << "Invalid selection, please try again." << std::endl;
            }
        }
        else
        {
            std::cout << "Invalid input, please enter a number or 'N'." << std::endl;
        }

        start = end;
        end += 10;
    } while (true);

    return 0;
}
/*
Lists 10 latest changes and allow user to select a change from the list or 
display the next 10 changes. When a change is selected, UpdateChangeInfo gets called
with the changeID of the selected change.
This function goes through the unsorted change file to fetch the change data
----------------------------------------------------------------*/
int UpdateChangeInfo(const char *changeID, std::streampos position)
{
    std::fstream file(FILENAMES[1], std::ios::in | std::ios::out | std::ios::binary);
    if (!file)
    {
        std::cerr << "Error: could not open file for reading and writing" << std::endl;
        return -1;
    }

    Change currentChange;
    file.seekg(position);
    if (!file.read(reinterpret_cast<char *>(&currentChange), sizeof(Change)))
    {
        std::cerr << "Error: could not read the change record" << std::endl;
        return -1;
    }

    if (strcmp(currentChange.getChangeID(), changeID) != 0)
    {
        std::cerr << "Error: ChangeID does not match" << std::endl;
        return -1;
    }

    std::cout << "Change found!" << std::endl;

    std::string description, releaseID, status, priority_input;
    char priority = '\0';

    // Description
    std::cout << "Current Description: " << currentChange.change_displayDesc() << std::endl;
    std::cout << "Enter new Description (or press Enter to keep current): ";
    std::getline(std::cin, description);
    if (description.empty())
        description = currentChange.change_displayDesc();

    // Status
    std::cout << "Current Status: " << currentChange.change_displayStatus() << std::endl;
    std::cout << "Enter new Status (P/X/-) (or press Enter to keep current): ";
    std::getline(std::cin, status);
    if (status.empty())
        status = currentChange.change_displayStatus();

    // Priority
    std::cout << "Current Priority: " << currentChange.change_displayPriority() << std::endl;
    std::cout << "Enter new Priority (1-5) (or press Enter to keep current): ";
    do
    {
        std::getline(std::cin, priority_input);
        if (priority_input.empty())
            break;
        priority = priority_input[0];
    } while (priority < '1' || priority > '5');
    if (priority == '\0')
        priority = currentChange.change_displayPriority();

    // Release ID
    std::cout << "Current ReleaseID: " << currentChange.change_displayRelID() << std::endl;
    std::cout << "Enter new ReleaseID (or press Enter to keep current): ";
    std::getline(std::cin, releaseID);
    if (releaseID.empty())
        releaseID = currentChange.change_displayRelID();

    try
    {
        char date[11];
        time_t now = time(0);
        strftime(date, sizeof(date), "%Y-%m-%d", localtime(&now));

        currentChange.UpdateChange(currentChange.getChangeID(), description.data(), status[0], priority, releaseID.data(), date);

        file.seekp(position);
        file.write(reinterpret_cast<char *>(&currentChange), sizeof(Change));
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
    cout << "Change was updated successfully!" << endl;
    return 1;
}
/*
Updates a change with givin changeID.
User can choose to update specific attributes of that change.
No noticeable algorithm or data structure used.
----------------------------------------------------------------*/
int ProductOnChange()
{
    int start = 0;
    int end = 10;
    int cc = 0;
    string input;
    char choice;
    std::streampos pos = PRODUCTFILEPOINTER + static_cast<std::streamoff>(sizeof(int)); // Skip total records field
    Product product;

    do
    {
        std::cout << "AVAILABLE PRODUCTS" << std::endl
                  << std::endl;
        std::cout << std::left
                  << std::setw(5) << " "
                  << std::setw(12) << "Product Name"
                  << std::right
                  << std::setw(31) << "ReleaseID/AnticipatedReleaseID"
                  << std::setw(12) << "ReleaseDate" << std::endl;
        std::cout << std::string(123, '-') << std::endl;

        bool hasMoreProducts = false;

        for (int i = start; i < end; i++)
        {
            try
            {
                product = GetProductDetails(pos, FILENAMES[3]);
                std::cout << std::setw(5) << i + 1 << " ";
                product.DisplayDetails(std::cout);
                std::cout << std::string(123, '-') << std::endl;

                pos += sizeof(Product);
                hasMoreProducts = true;
            }
            catch (const NoRecordFound &e)
            {
                hasMoreProducts = false;
                break;
            }
        }

        if (hasMoreProducts)
        {
            std::cout << "Type the number to select a product, 'N' to show the next list, '0' to quit: ";
        }
        else
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
    int start = 0;
    int cc = 0;
    int end = 10;
    string input;
    char choice;
    std::streampos pos = CHANGEFILEPOINTER + static_cast<std::streamoff>(sizeof(int)); // Skip total records field
    Change change;

    do
    {
        std::cout << "AVAILABLE CHANGES" << std::endl
                  << std::endl;
        std::cout << std::left
                  << std::setw(5) << " "
                  << std::setw(10) << "ChangeID"
                  << std::setw(15) << "Product Name"
                  << std::setw(32) << "Description"
                  << std::setw(12) << "Last Update"
                  << std::setw(7) << "Status"
                  << std::setw(10) << "Priority"
                  << std::setw(32) << "ReleaseID/Anticipated ReleaseID" << std::endl;
        std::cout << std::string(123, '-') << std::endl;

        bool hasMoreChanges = true;

        for (int i = start; i < end; i++)
        {
            try
            {
                change = GetChangeDetails(pos, FILENAMES[1]);
                std::cout << std::setw(5) << i + 1 << " ";
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
                hasMoreChanges = false;
                break;
            }
        }

        if (hasMoreChanges)
        {
            std::cout << "Type the number to select a change, 'N' to show the next list, '0' to quit: ";
        }
        else
        {
            std::cout << "No more changes to show. Type the number to select a change, '0' to quit: ";
        }
        std::cin.ignore();
        std::getline(std::cin, input);
        if (input.empty())
        {
            std::cout << "Invalid input, please try again." << std::endl;
            continue;
        }

        choice = input[0];

        if (choice == 'N' || choice == 'n')
        {
            if (!hasMoreChanges)
            {
                std::cout << "No more changes to show. Can't use 'N'" << std::endl;
                continue;
            }
        }
        else if (choice == '0')
        {
            break; // Exit the loop
        }
        else if (isdigit(choice))
        {
            cc = choice - '0';

            if (cc > 0 && cc <= (end - start))
            {
                std::streampos p = CHANGEFILEPOINTER + static_cast<std::streamoff>(sizeof(int)); // Skipping total records

                std::streampos selectedPos = p + static_cast<std::streamoff>((cc - 1 + start) * sizeof(Change));
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
            else
            {
                std::cout << "Invalid selection, please try again." << std::endl;
            }
        }
        else
        {
            std::cout << "Invalid input, please enter a number or 'N'." << std::endl;
        }

        start = end;
        end += 10;
    } while (cc != 0);

    return 0;
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
/*
Initializes customer, complaint, change, and product with their file and file pointer
----------------------------------------------------------------*/