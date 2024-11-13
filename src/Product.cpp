/* Product.cpp
REVISION HISTORY:
Rev. 1 - 24/07/15 Original by Seoyoung Kim
----------------------------------------------------------------------
This CPP file called Changes.cpp handles the changes of the program.
--------------------------------------------------------------------*/

#include <cstring>
#include <iostream>
#include <fstream>
#include <iomanip>

#include "../include/Product.hpp"

//--------------------------------------------------------------------

/*
Default constrctor for the Product class
--------------------------------------------------------------------*/
Product::Product() : releaseID{0}, releaseDate{0}
{
    memset(productName, 0, sizeof(productName));
}

/*
Parameterized constructor for Product class.
Create Product object using attrbibutes provided.
No algorithm or data structure used.
--------------------------------------------------------------------*/
Product::Product(const char *releaseID, const char *productName, const char *ReleaseDate)
{
    safeStrCopy(this->productName, productName, sizeof(this->productName));
    safeStrCopy(this->releaseDate, ReleaseDate, sizeof(this->releaseDate));

    // Generate ReleaseID
    if (strlen(releaseID) != 0)
    {
        safeStrCopy(this->releaseID, releaseID, sizeof(this->releaseID));
    }
    else
    {
        // Assuming IDGenerator returns a char*
        char *generatedID = IDGenerator('4', 9);
        safeStrCopy(this->releaseID, generatedID, sizeof(this->releaseID));
        delete[] generatedID;
    }
}

/*
Print the attribute details of the Product object to the console.
No algorithm or data structure used.
--------------------------------------------------------------------*/
void Product::DisplayDetails(std::ostream &out) const
{
    out << std::left
        << std::setw(11) << productName
        << std::right

        << std::setw(19) << releaseID
                  << std::right

        << std::setw(24) << releaseDate << std::endl;
}

/*
Equality operator overloader for Product class.
Checks if two Product objects are equal based on releaseID or releaseDate.
No noticeable algorithm or data structure used.
--------------------------------------------------------------------*/
bool Product::operator==(const Product &other) const
{
    return (strcmp(releaseID, other.releaseID) == 0 || strcmp(releaseDate, other.releaseDate) == 0);
}

/*
Validates that the Product object attributes are acceptable and makes sure no duplicate Product records exists.
A linear search algorithm is used to iterate through the Product records.
--------------------------------------------------------------------*/
int ValidateProduct(const char *productName, const char *ReleaseID, const char *ReleaseDate)
{
    if (strlen(productName) == 0 || strlen(productName) > 10)
    {
        throw InvalidDataException("ProductName field must be at least 1 and at most 9 characters");
    }
    // cout << strlen(ReleaseID) << endl;
    if (strlen(ReleaseID) > 8 && strlen(ReleaseID) && strlen(ReleaseID) != 0)
    {
        throw InvalidDataException("ReleaseID field can be of 8 characters at max.");
    }

    if (strlen(ReleaseDate) != 10 && strlen(ReleaseDate) != 0)
    {
        throw InvalidDataException("ReleaseDate field can only have value in the format of YYYY-MM-DD.");
    }

    // Check ReleaseDate format (YYYY-MM-DD)
    int year = (ReleaseDate[0] - '0') * 1000 + (ReleaseDate[1] - '0') * 100 + (ReleaseDate[2] - '0') * 10 + (ReleaseDate[3] - '0');
    int month = (ReleaseDate[5] - '0') * 10 + (ReleaseDate[6] - '0');
    int day = (ReleaseDate[8] - '0') * 10 + (ReleaseDate[9] - '0');
    if (year < 2024 || year > 2099 || month < 1 || month > 12 || day < 1 || day > 31)
    {
        throw InvalidDataException("ReleaseDate field can only have value in the format of YYYY-MM-DD.");
    }

    if ((year % 4 != 0 && month == 02 && day > 30) || (year % 4 == 0 &&month == 2 && day > 29))
    {
        throw InvalidDataException("Invalid date");
    }
    if (day > 30)
    {
        switch (month)
        {
            case 4:
            case 6:
            case 9:
            case 11:
                throw InvalidDataException("Invalid date");
        }
    }

    // Check for duplicate product
    std::ifstream file(FILENAMES[3], std::ios::binary);
    if (!file)
    {
        std::cerr << "Error: Could not open file for reading" << std::endl;
        return -1;
    }

    Product currentProduct;
    while (file.read(reinterpret_cast<char *>(&currentProduct), sizeof(Product)))
    {
        if (strcmp(currentProduct.getReleaseID(), ReleaseID) == 0)
        {
            throw DuplicateRecordException("Duplicate Product record found.");
            break;
        }
    }

    file.close();
    std::cout << "Validation of data for 'Product' record succeeded!" << std::endl;

    return 1;
}

/*
Create new Product object and also validates it.
No noticeable algorithm or data structure used.
--------------------------------------------------------------------*/
Product CreateProduct(const char *productName, const char *ReleaseID, const char *ReleaseDate)
{
    ValidateProduct(productName, ReleaseID, ReleaseDate);
    return Product(ReleaseID, productName, ReleaseDate);
}

/*
Writes a Product object to a specified file at a given position.
Uses the unsorted records data structure to add the Product object.
--------------------------------------------------------------------*/
void CommitProduct(const Product &product, std::streampos &startPos, const std::string &FILENAME)
{
    std::ofstream file(FILENAME, std::ios::binary | std::ios::in | std::ios::out);
    if (!file)
    {
        throw FileException("Could not open file 'Products.bin' for writing when adding a Change record to the file.");
    }

    file.seekp(0, std::ios::end);
    startPos = file.tellp();
    file.write(reinterpret_cast<const char *>(&product), sizeof(Product));

    if (file.fail())
    {
        throw FileException("Could not open file 'Products.bin' for writing when adding a Change record to the file.");
    }
    startPos = file.tellp();
}

/*
Reads a Product object from a specified file at a given position and returns it.
Uses the unsorted records data structure to read the Product object.
--------------------------------------------------------------------*/
Product GetProductDetails(std::streampos startPos, const std::string &FILENAME)
{
    std::ifstream file(FILENAME, std::ios::binary);
    if (!file)
    {
        throw std::runtime_error("FileReadFailed: Could not open file for reading");
    }

    file.seekg(startPos);
    Product product;

    if (!file.read(reinterpret_cast<char *>(&product), sizeof(Product)))
    {
        throw NoRecordFound("FileReadFailed: There was an error in reading the file.");
    }
    return product;
}

/*
Displays all Product objects with their attribute information.
Uses unsorted records data structure to read the Product object.
------------------------------------------------------------------------------------------*/
void PrintAllProducts(const std::string &FILENAME)
{
    std::ifstream file(FILENAME, std::ios::binary);
    if (!file)
    {
        throw FileException("Could not open file 'Products.bin' during reading.");
    }

    Product product;
    int recordCount = 0;
    int batchSize = 10;
    char input[3];
    int choice = 1;

    std::cout << std::left
              << std::setw(5) << " "
              << std::setw(13) << "Product Name"
              << std::setw(31) << "ReleaseID/AnticipatedReleaseID"
              << std::setw(12) << "ReleaseDate"
              << std::endl;
    std::cout << std::string(94, '-') << std::endl;

    while (file.read(reinterpret_cast<char *>(&product), sizeof(product)))
    {
        std::cout << std::left
                  << std::setw(5) << recordCount + 1 << " "
                  << std::setw(13) << product.getProductName()
                  << std::setw(31) << product.getReleaseID()
                  << std::setw(12) << product.getReleaseDate()
                  << std::endl;
        recordCount++;

        if (recordCount % batchSize == 0)
        {
            std::cout << std::string(94, '-') << std::endl;
            std::cout << "Displayed 10 records." << std::endl;
            std::cout << "Do you want to view the next 10 products? (1 for Yes, 0 for No): ";
            do
            {
                std::cin.getline(input, 3);
                choice = atoi(input);
            } while (choice != 0 || choice != 1);

            if (choice == 0)
            {
                break;
            }
            else if (choice == 1)
            {
                std::cout << std::left
                          << std::setw(13) << "Product Name"
                          << std::setw(31) << "ReleaseID/AnticipatedReleaseID"
                          << std::setw(12) << "ReleaseDate"
                          << std::endl;
                std::cout << std::string(89, '-') << std::endl;
            }
        }
    }

    std::cout << std::string(89, '-') << std::endl;
    std::cout << "Total records Displayed: " << recordCount << std::endl << std::endl;

    if (file.eof())
    {
        file.clear(); // Clear EOF flag
    }
    else if (file.fail())
    {
        throw FileException("Could not read file 'Products.bin' during printing.");
    }

    file.close();
}

/*
Check if there is a Product object with the same ReleaseID in the Product data file.
Uses linear search through the data file to check for the duplicate.
------------------------------------------------------------------------------------------------*/
bool checkDupProduct(const char *otherReleaseID)
{
    std::ifstream file(FILENAMES[3], std::ios::binary);
    if (!file)
    {
        throw FileException("Could not open file 'Products.bin' for checking duplicate releaseID.");
    }
    Product temp;
    while (file.read(reinterpret_cast<char *>(&temp), sizeof(Product)))
    {
        if (strcmp(temp.getReleaseID(), otherReleaseID) == 0)
        {
            file.close();
            return 1;
        }
    }
    file.close();
    return 0;
}

/*
Initialization for Product class.
Set up the data file for Product class and file descriptor if they hasn't been set up yet.
------------------------------------------------------------------------------------------------*/
int InitProduct()
{
    std::filesystem::create_directory(DIRECTORY);
    if (!std::filesystem::exists(FILENAMES[3]))
    {
        std::ofstream file(FILENAMES[3], std::ios::binary);
        if (!file)
        {
            throw FileException("Startup failed while creating 'Products.bin' file.");
        }
        file.close();
        return 1;
    }
    return 0;
}