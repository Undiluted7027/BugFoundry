/* test.cpp
REVISION HISTORY:
Rev. 1 - 24/07/16 Original by Sanchit Jain
----------------------------------------------------------------------
This CPP file called test.cpp handles tests on the program.
--------------------------------------------------------------------*/

#include "UI.cpp"
#include <cassert>

using namespace std;

void testCustomerClass() 
{
    // Test Customer constructor and getters
    Customer c1("123456789", "John Doe", "john@example.com", "2345678901");
    assert(strcmp(c1.getCustID(), "123456789") == 0);
    assert(strcmp(c1.getName(), "John Doe") == 0);
    assert(strcmp(c1.getEmail(), "john@example.com") == 0);
    assert(strcmp(c1.getPhone(), "2345678901") == 0);

    // Test Customer copy constructor
    Customer c2(c1);
    assert(c2 == c1);

    // Test Customer assignment operator
    Customer c3;
    c3 = c1;
    assert(c3 == c1);

    // Test DisplayDetails
    std::ostringstream oss;
    c1.DisplayDetails(oss);
    assert(oss.str().find("John Doe") != std::string::npos);

    // Test CommitCustomer and GetCustomerDetails
    std::streampos pos = 0;
    try
    {
        ValidateCustomer("John Doe", "john@example.com", "12345678901");
        CommitCustomer(c1, pos, FILENAMES[0]);
    }
    catch (const DuplicateRecordException &e)
    {
        LogException(e);
        cout << "Duplicate customer detection successful" << endl << endl;
    }

    Customer temp;
    Customer retrievedCustomer;
    std::fstream file(FILENAMES[0], std::ios::binary | std::ios::in | std::ios::out);
    while (file.read(reinterpret_cast<char *>(&temp), sizeof(Customer)))
    {
        if (strcmp(temp.getCustID(), c1.getCustID()) == 0)
        {
            retrievedCustomer = temp;
            break;
        }
    }
    file.close();
    assert(retrievedCustomer == c1);

    // Test ValidateCustomer
    assert(ValidateCustomer("Jane Doe", "jane@example.com", "9876543210") == 1);
    assert(ValidateCustomer("", "invalid@email", "1234567890") == -1);
    try
    {
        ValidateCustomer("John Doe", "john@example.com", "12345678901");
    }
    catch (const DuplicateRecordException &e)
    {
        LogException(e);
        cout << "Duplicate customer detection successful" << endl << endl;
    }

    // Test PrintAllCustomers (requires multiple records)
    Customer c4("2345678901", "Alice Smith", "alice@example.com", "3456789012");
    Customer c5("3456789012", "Bob Johnson", "bob@example.com", "4567890123");
    try
    {
        ValidateCustomer("Alice Smith", "alice@example.com", "3456789012");
        ValidateCustomer("Bob Johnson", "bob@example.com", "4567890123");
        CommitCustomer(c4, pos, FILENAMES[0]);
        CommitCustomer(c5, pos, FILENAMES[0]);
    }
    catch (const DuplicateRecordException &e)
    {
        LogException(e);
        cout << "Duplicate customer detection successful" << endl << endl;
    }
    PrintAllCustomers(FILENAMES[0]);

    // Test InitCustomer
    assert(InitCustomer() == 0);  // File already exists

    std::cout << std::endl;
    std::cout << "=========================================" << std::endl;
    std::cout << "Customer class tests passed successfully!" << std::endl;
    std::cout << "=========================================" << std::endl;
    std::cout << std::endl;
}


void testComplaintClass() {
    // Test Complaint constructor and getters
    Complaint comp1("", "Test complaint", "2024-07-17", "12345", "abc", "123456789");
    assert(strlen(comp1.getComplaintID()) == 6);
    assert(strcmp(comp1.getDescription(), "Test complaint") == 0);
    assert(strcmp(comp1.getDateOfComplaint(), "2024-07-17") == 0);
    assert(strcmp(comp1.getChangeID(), "12345") == 0);
    assert(strcmp(comp1.getReleaseID(), "abc") == 0);
    assert(strcmp(comp1.getCustID(), "123456789") == 0);

    // Test Complaint copy constructor
    Complaint comp2(comp1);
    assert(comp2 == comp1);

    // Test Complaint assignment operator
    Complaint comp3;
    comp3 = comp1;
    assert(comp3 == comp1);
    
    // Test DisplayDetails
    std::ostringstream oss;
    comp1.DisplayDetails(oss);
    assert(oss.str().find("Test complaint") != std::string::npos);
    
    // Test CommitComplaint and GetComplaintDetails
    std::streampos pos = 0;
    try
    {
        ValidateComplaint("Test complaint", "2024-07-17", "abc", "123456789");
        CommitComplaint(comp1, pos, FILENAMES[2]);
    }
    catch (const DuplicateRecordException &e)
    {
        LogException(e);
        cout << "Duplicate complaint detection successful" << endl << endl;
    }
    catch (const NoRecordFound &e)
    {
        LogException(e);
        cout << "No product with that releaseID yet" << endl << endl;
    }

    Complaint temp;
    Complaint retrievedComplaint;
    std::fstream file(FILENAMES[2], std::ios::binary | std::ios::in | std::ios::out);
    while (file.read(reinterpret_cast<char *>(&temp), sizeof(Complaint)))
    {
        if (strcmp(temp.getComplaintID(), comp1.getComplaintID()) == 0)
        {
            retrievedComplaint = temp;
            break;
        }
    }
    file.close();
    assert(retrievedComplaint == comp1);

    // Test ValidateComplaint
    try
    {
        assert(ValidateComplaint("Valid complaint", "2024-07-17", "abc", "123456789") == 1);
        assert(ValidateComplaint("invalid", "12345", "abc", "1234567890") == -1);
        assert(ValidateComplaint("Test complaint", "2024-07-17", "abc", "123456789") == 0);   
    }
    catch (const DuplicateRecordException &e)
    {
        LogException(e);
        cout << "Duplicate complaint detection" << endl << endl;
    }
    catch (const NoRecordFound &e)
    {
        LogException(e);
        cout << "No product with that releaseID yet" << endl << endl;
    }
    catch (const InvalidDataException &e)
    {
        LogException(e);
        cout << "Invalid data format detection" << endl << endl;
    }
    
    // Test PrintAllComplaints (requires multiple records)
    Complaint comp4("", "Another complaint", "2024-07-18", "23456", "abc", "234567890");
    Complaint comp5("", "Third complaint", "2024-07-19", "34567", "abc", "345678901");

    try
    {
        ValidateComplaint("Another complaint", "2024-07-18", "abc", "234567890");
        ValidateComplaint("Third complaint", "2024-07-19", "abc", "345678901");
        CommitComplaint(comp4, pos, FILENAMES[2]);
        CommitComplaint(comp5, pos, FILENAMES[2]);
    }
    catch (const DuplicateRecordException &e)
    {
        LogException(e);
        cout << "Duplicate complaint detection successful" << endl << endl;
    }
    catch (const NoRecordFound &e)
    {
        LogException(e);
        cout << "No product with that releaseID yet" << endl << endl;
    }

    PrintAllComplaints(FILENAMES[2]);
    
    // Test UpdateComplaint
    Complaint updatedComp("", "Updated complaint", "2024-07-20", "12345", "abc", "123456789");
    assert(UpdateComplaint(comp1.getComplaintID(), updatedComp, FILENAMES[2]));

    // Test InitComplaint
    assert(InitComplaint() == 0);  // File already exists

    std::cout << "Complaint class tests passed successfully!" << std::endl;
}

void testProductClass() {
    // Test Product constructor and getters
    Product p1("", "TestProd", "2024/07/17");
    assert(strlen(p1.getReleaseID()) == 8);
    assert(strcmp(p1.getProductName(), "TestProd") == 0);
    assert(strcmp(p1.getReleaseDate(), "2024/07/17") == 0);

    // Test Product copy constructor
    Product p2(p1);
    assert(p2 == p1);

    // Test DisplayDetails
    std::ostringstream oss;
    p1.DisplayDetails(oss);
    assert(oss.str().find("TestProd") != std::string::npos);

    // Test CommitProduct and GetProductDetails
    std::streampos pos = 0;
    

    try
    {
        ValidateProduct(p1.getProductName(), p1.getReleaseID(), p1.getReleaseDate());
        CommitProduct(p1, pos, FILENAMES[3]);
    }
    catch (const DuplicateRecordException &e)
    {
        LogException(e);
        cout << "Duplicate Product Detection" << endl << endl;
    }

    Product temp;
    Product retrievedProduct;
    std::fstream file(FILENAMES[3], std::ios::binary | std::ios::in | std::ios::out);
    while (file.read(reinterpret_cast<char *>(&temp), sizeof(Product)))
    {
        if (strcmp(temp.getReleaseID(), p1.getReleaseID()) == 0)
        {
            retrievedProduct = temp;
            break;
        }
    }
    file.close();

    assert(retrievedProduct == p1);

    // Test ValidateProduct
    
    try
    {
        assert(ValidateProduct("ValidProd", "87654321", "2024-07-17") == 1);
        assert(ValidateProduct("invalid!!!!!!!!!!!", "", "2024-07-17") == -1);
        assert(ValidateProduct("TestProd2", "99999999", "2024-07-170") == -1);
    }
    catch (const DuplicateRecordException &e)
    {
        LogException(e);
        cout << "Duplicate Product Detection" << endl << endl;
    }
    catch (const InvalidDataException &e)
    {
        LogException(e);
        cout << "Incorrect data format" << endl << endl;
    }


    // Test CreateProduct (this will also test ValidateProduct)
    // Product p3 = CreateProduct("NewProd", "", "24/07/18");
    // assert(strcmp(p3.getProductName(), "NewProd") == 0);

    // Test multiple products (for functions that might need multiple records)
    Product p4("", "AnotherProd", "2024-07-19");
    Product p5("", "ThirdProd", "2024-07-20");
    
    try
    {
        ValidateProduct(p4.getProductName(), p4.getReleaseID(), p4.getReleaseDate());
        ValidateProduct(p5.getProductName(), p5.getReleaseID(), p5.getReleaseDate());
        CommitProduct(p4, pos, FILENAMES[3]);
        CommitProduct(p5, pos, FILENAMES[3]);
    }
    catch (const DuplicateRecordException &e)
    {
        LogException(e);
        cout << "Duplicate Product Detection" << endl << endl;
    }

    // Test InitProduct
    assert(InitProduct() == 0);  // File already exists

    std::cout << "Product class tests passed successfully!" << std::endl;
}

void testChangeClass() {
    // Test Change constructor and getters
    Change c1("", "Test description", 'P', '3', "12345678", "2024-07-17", "");
    assert(strlen(c1.getChangeID()) == 6);
    assert(c1.getChangeID()[0] == '1');
    assert(strcmp(c1.change_displayDesc(), "Test description") == 0);
    assert(c1.change_displayStatus() == 'P');
    assert(c1.change_displayPriority() == '3');
    assert(strcmp(c1.change_displayRelID(), "12345678") == 0);

    // Test Change copy constructor
    Change c2(c1);
    assert(c2 == c1);

    // Test Change assignment operator
    Change c3;
    c3 = c1;
    assert(c3 == c1);

    // Test DisplayDetails
    std::ostringstream oss;
    c1.DisplayDetails(oss);
    assert(oss.str().find("Test description") != std::string::npos);

    // Test UpdateChange
    c1.UpdateChange(c1.getChangeID(), "Updated description", 'X', '4', "17654321", "2024-01-01");
    assert(strcmp(c1.change_displayDesc(), "Updated description") == 0);
    assert(c1.change_displayStatus() == 'X');
    assert(c1.change_displayPriority() == '4');
    assert(strcmp(c1.change_displayRelID(), "17654321") == 0);

    // Test CommitChange and GetChangeDetails
    std::streampos pos = 0;
    
    try
    {
        ValidateChange(c1.change_displayDesc(), c1.change_displayStatus(), c1.change_displayPriority(), "2024-01-01", c1.change_displayRelID());
        CommitChange(c1, pos, FILENAMES[1]);
    }
    catch (const DuplicateRecordException &e)
    {
        LogException(e);
        cout << "Duplicate Product Detection" << endl << endl;
    }

    Change temp;
    Change retrievedChange;
    std::fstream file(FILENAMES[1], std::ios::binary | std::ios::in | std::ios::out);
    while (file.read(reinterpret_cast<char *>(&temp), sizeof(Change)))
    {
        if (strcmp(temp.change_displayDesc(), c1.change_displayDesc()) == 0)
        {
            retrievedChange = temp;
            break;
        }
    }
    file.close();
    assert(retrievedChange == c1);

    // Test ValidateChange
    try
    {
        assert(ValidateChange("Valid description", 'P', '3', "2024-07-17", "12345678") == 1);
        assert(ValidateChange("", 'Z', '6', "invalid", "123") == -1);
        assert(ValidateChange("Updated description", 'X', '4', "2024-07-17", "17654321") == 0);
    }
    catch (const DuplicateRecordException &e)
    {
        LogException(e);
        cout << "Duplicate Product Detection" << endl << endl;
    }
    catch (const InvalidDataException &e)
    {
        LogException(e);
        cout << "Incorrect data format" << endl << endl;
    }

    // Test CreateChange
    try
    {
        Change c4 = CreateChange("New change", 'X', '2', "2024-07-18", "23456789", "");
        assert(strcmp(c4.change_displayDesc(), "New change") == 0);
        
        // Test multiple changes (for functions that might need multiple records)
        Change c5 = CreateChange("Another change", 'P', '1', "2024-07-19", "34567890", "");
        Change c6 = CreateChange("Third change", 'X', '5', "2024-07-20", "45678901", "");

        ValidateChange(c5.change_displayDesc(), c5.change_displayStatus(), c5.change_displayPriority(), "2024-07-19", c5.change_displayRelID());
        CommitChange(c5, pos, FILENAMES[1]);
        
        ValidateChange(c6.change_displayDesc(), c6.change_displayStatus(), c6.change_displayPriority(), "2024-07-20", c6.change_displayRelID());
        CommitChange(c6, pos, FILENAMES[1]);
    }
    catch (const DuplicateRecordException &e)
    {
        LogException(e);
        cout << "Duplicate Product Detection" << endl << endl;
    }
    catch (const InvalidDataException &e)
    {
        LogException(e);
        cout << "Incorrect data format" << endl << endl;
    }

    // Test CreateChangesReport
    int reportCount = CreateChangesReport();
    assert(reportCount >= 3);  // We've added at least 3 changes

    /*
    Test for CreateAnticipatedChangesProduct and CreateUsersInformedOnUpdateReport
    needs to be modified to take another input to be tested.
    */

    // Test CreateAnticipatedChangesProduct
    // std::ostringstream anticipatedOss;
    // std::streambuf* coutBuffer = std::cout.rdbuf();
    // std::cout.rdbuf(anticipatedOss.rdbuf());
    // CreateAnticipatedChangesProduct("abc");
    // std::cout.rdbuf(coutBuffer);
    // assert(anticipatedOss.str().find("17654321") == std::string::npos);

    // Test CreateUsersInformedOnUpdateReport
    // std::ostringstream informedOss;
    // std::cout.rdbuf(informedOss.rdbuf());
    // CreateUsersInformedOnUpdateReport(c1.getChangeID());
    // std::cout.rdbuf(coutBuffer);
    // assert(informedOss.str().find("Customers to be informed about Change ID ") != std::string::npos);

    // Test InitChange
    assert(InitChange() == 0);  // File already exists

    std::cout << "Change class tests passed successfully!" << std::endl;
}

int main() {

    InitCustomer();
    InitComplaint();
    InitProduct();
    InitChange();

    cout << "Initialization complete" << endl;

    testCustomerClass();
    testComplaintClass();
    testProductClass();
    testChangeClass();

    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}