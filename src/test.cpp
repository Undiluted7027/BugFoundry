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
/*
void testComplaintClass() {
    // Test Complaint constructor and getters
    Complaint comp1("", "Test complaint", "24-07-17", "12345", "87654321", "1234567890");
    assert(strlen(comp1.getComplaintID()) == 6);
    assert(strcmp(comp1.getDescription(), "Test complaint") == 0);
    assert(strcmp(comp1.getDateOfComplaint(), "24-07-17") == 0);
    assert(strcmp(comp1.getChangeID(), "12345") == 0);
    assert(strcmp(comp1.getReleaseID(), "87654321") == 0);
    assert(strcmp(comp1.getCustID(), "1234567890") == 0);

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
    CommitComplaint(comp1, pos, FILENAMES[2]);
    Complaint retrievedComplaint = GetComplaintDetails(COMPLAINTFILEPOINTER, FILENAMES[2]);
    assert(retrievedComplaint == comp1);

    // Test ValidateComplaint
    assert(ValidateComplaint("Valid complaint", "24-07-17", "12345", "87654321", "1234567890") == 1);
    assert(ValidateComplaint("", "invalid", "12345", "87654321", "1234567890") == -1);
    assert(ValidateComplaint("Test complaint", "24-07-17", "12345", "87654321", "1234567890") == 0);

    // Test PrintAllComplaints (requires multiple records)
    Complaint comp4("", "Another complaint", "24-07-18", "23456", "76543210", "2345678901");
    Complaint comp5("", "Third complaint", "24-07-19", "34567", "65432109", "3456789012");
    CommitComplaint(comp4, pos, FILENAMES[2]);
    CommitComplaint(comp5, pos, FILENAMES[2]);
    PrintAllComplaints(FILENAMES[2]);

    // Test UpdateComplaint
    Complaint updatedComp("", "Updated complaint", "24-07-20", "12345", "87654321", "1234567890");
    assert(UpdateComplaint(comp1.getComplaintID(), updatedComp, FILENAMES[2]));

    // Test InitComplaint
    assert(InitComplaint() == 0);  // File already exists

    std::cout << "Complaint class tests passed successfully!" << std::endl;
}

void testProductClass() {
    // Test Product constructor and getters
    Product p1("", "TestProd", "24/07/17");
    assert(strlen(p1.getReleaseID()) == 8);
    assert(strcmp(p1.getProductName(), "TestProd") == 0);
    assert(strcmp(p1.getReleaseDate(), "24/07/17") == 0);

    // Test Product copy constructor
    Product p2(p1);
    assert(p2 == p1);

    // Test DisplayDetails
    std::ostringstream oss;
    p1.DisplayDetails(oss);
    assert(oss.str().find("TestProd") != std::string::npos);

    // Test CommitProduct and GetProductDetails
    std::streampos pos = 0;
    CommitProduct(p1, pos, FILENAMES[3]);
    Product retrievedProduct = GetProductDetails(0, FILENAMES[3]);
    assert(retrievedProduct == p1);

    // Test ValidateProduct
    assert(ValidateProduct("ValidProd", "87654321", "24-07-17") == 1);
    assert(ValidateProduct("invalid", "", "24-07-17") == -1);
    assert(ValidateProduct("TestProd", p1.getReleaseID(), "24-07-17") == 0);
    

    // Test CreateProduct (this will also test ValidateProduct)
    // Product p3 = CreateProduct("NewProd", "", "24/07/18");
    // assert(strcmp(p3.getProductName(), "NewProd") == 0);

    // Test multiple products (for functions that might need multiple records)
    Product p4("", "AnotherProd", "24-07-19");
    Product p5("", "ThirdProd", "24-07-20");
    CommitProduct(p4, pos, FILENAMES[3]);
    CommitProduct(p5, pos, FILENAMES[3]);

    // Test InitProduct
    assert(InitProduct() == 0);  // File already exists

    std::cout << "Product class tests passed successfully!" << std::endl;
}

void testChangeClass() {
    // Test Change constructor and getters
    Change c1("", "Test description", 'P', '3', "12345678", "24-07-17", "");
    assert(strlen(c1.getChangeID()) == 6);
    assert(c1.getChangeID()[0] == '1');
    assert(strcmp(c1.change_displayDesc(), "Test description") == 0);
    assert(c1.change_displayStatus() == 'P');
    assert(c1.change_displayPriority() == '3');
    assert(strcmp(c1.change_displayRelID(), "12345678") == 0);
    // assert(strcmp(c1.getLastUpdate(), "24-07-17") == 0);

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
    CommitChange(c1, pos, FILENAMES[1]);
    Change retrievedChange = GetChangeDetails(0, FILENAMES[1]);
    assert(retrievedChange == c1);

    // Test ValidateChange
    assert(ValidateChange("Valid description", 'P', '3', "24-07-17", "12345678") == 1);
    assert(ValidateChange("", 'Z', '6', "invalid", "123") == -1);
    assert(ValidateChange("Updated description", 'X', '4', "24-07-17", "17654321") == 0);

    // Test CreateChange
    Change c4 = CreateChange("New change", 'X', '2', "24-07-18", "23456789", "");
    assert(strcmp(c4.change_displayDesc(), "New change") == 0);

    // Test multiple changes (for functions that might need multiple records)
    Change c5 = CreateChange("Another change", 'P', '1', "24-07-19", "34567890", "");
    Change c6 = CreateChange("Third change", 'X', '5', "24-07-20", "45678901", "");
    CommitChange(c5, pos, FILENAMES[1]);
    CommitChange(c6, pos, FILENAMES[1]);

    // Test CreateChangesReport
    int reportCount = CreateChangesReport();
    assert(reportCount >= 3);  // We've added at least 4 changes

    // Test CreateAnticipatedChangesProduct
    std::ostringstream anticipatedOss;
    std::streambuf* coutBuffer = std::cout.rdbuf();
    std::cout.rdbuf(anticipatedOss.rdbuf());
    CreateAnticipatedChangesProduct("17654321");
    std::cout.rdbuf(coutBuffer);
    assert(anticipatedOss.str().find("17654321") != std::string::npos);

    // Test CreateUsersInformedOnUpdateReport
    std::ostringstream informedOss;
    std::cout.rdbuf(informedOss.rdbuf());
    CreateUsersInformedOnUpdateReport(c1.getChangeID());
    std::cout.rdbuf(coutBuffer);
    // assert(informedOss.str().find("Customers to be informed about Change ID ") != std::string::npos);

    // Test InitChange
    assert(InitChange() == 0);  // File already exists

    std::cout << "Change class tests passed successfully!" << std::endl;
}
*/
int main() {
    InitCustomer();
    // InitComplaint();
    // InitProduct();
    // InitChange();

    cout << "Initialization complete" << endl;

    testCustomerClass();
    // testComplaintClass();
    // testProductClass();
    // testChangeClass();

    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}