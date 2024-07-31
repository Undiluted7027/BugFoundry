#ifndef PRODUCT_HPP
#define PRODUCT_HPP

/* Product.hpp
REVISION HISTORY:
Rev. 1 - 24/07/03 Original by Sanchit Jain
Rev. 2 - 24/07/14 Revised by Seoyoung Kim
Rev. 3 - 24/07/17 Revised by Sanchit Jain
----------------------------------------------------------------------
This module, Product.hpp, hides the implementation of Product class.
It keeps its high cohesion by encapsulating all possible product entries in the system.
----------------------------------------------------------------------*/

#include <iostream>
#include <filesystem> // Added for filesystem operations (assuming C++17 or later)
#include <string>
#include "Globals.hpp"

//----------------------------------------------------------------------
class Product
{
    public:

        Product();
        /*
        Product() is the default constructor for the Product class. It initializes all member variables to their default values.
        ------------------------------------------------------------------*/
        Product(
            const char* releaseID,      // in: the unique releaseID for this product
            const char *productName,    // in: the name of this product
            const char *ReleaseDate     // in: contains year, month, date of when the product is released
        );
        /*
        This is the non-default constructor for the Product class. 
        It takes in details of a product, and creates the product object. 
        ------------------------------------------------------------------*/
        void DisplayDetails(std::ostream &out) const;
        /*
        DisplayDetail is a helper function to display details of a Product object using << operator. 
        It fails to show the required output if any of the member variables/C-strings have only null-character in them.
        ------------------------------------------------------------------*/
        bool operator==(const Product &other) const;
        /*
        Equality overloading operator for Product class. 
        Uses releaseID or releaseDate attribute to check the equality 
        ------------------------------------------------------------------*/
        const char* getProductName() const { return productName; }
        /*
        getProductName is a helper function that returns the Product object's productName attribute
        ------------------------------------------------------------------*/
        const char* getReleaseID() const { return releaseID; }
        /*
        getReleaseID is a helper function that returns the Product object's releaseID attribute
        ------------------------------------------------------------------*/
        const char* getReleaseDate() const { return releaseDate; }
        /*
        getReleaseDate is a helper function that returns the Product object's releaseDate attribute
        ------------------------------------------------------------------*/

    private:

        char productName[11];   // The name of the product
        char releaseID[9];      // The unique releaseID of the product
        char releaseDate[11];   // Contains year, month, day of when the product is released
};

int ValidateProduct(
    const char *productName,    // in: the name of the product
    const char *ReleaseID,      // in: the unique releaseID of the product
    const char *ReleaseDate     // in: contains year, month, day of when the product is released
); // Function to validate product data
/*
If same data already exists in system it returns 0, if the format is invalid it returns -1 else 1. 
This function performs checks on formats of productName, releaseID, and releaseDate in product object. 
Call this function with details of the product to check whether the info is valid.
------------------------------------------------------------------*/
Product CreateProduct(
    const char *productName,    // in: the name of the product
    const char *ReleaseID,      // in: the unique releaseID of the product
    const char *ReleaseDate     // in: contains year, month, day of when the product is released
); // Function to create a new Product object
/*
CreateProduct takes in details of the Product, 
checks if input is valid by calling ValidateProduct and returns a Product object. 
If the input is invalid, a message is displayed.
------------------------------------------------------------------*/
void CommitProduct(
    const Product &product,                             // in: the product to commit
    std::streampos &startPos = PRODUCTFILEPOINTER,      // in out: the file pointer that points to the end of file
    const std::string &FILENAME = FILENAMES[3]          // in: the binary file 
); // Function to commit Product object to file
/*
CommitProduct takes in a product object, 
file pointer, and name of file and adds a record in the binary file. 
This function fails if there is an error in writing to the file.
------------------------------------------------------------------*/
Product GetProductDetails(
    std::streampos startPos = PRODUCTFILEPOINTER,       // in out: the file pointer that points to the end of file
    const std::string &FILENAME = FILENAMES[3]          // in: the binary file
); // Function to retrieve Product details from file
/*
GetProductDetails takes in a file pointer,
reads the file and returns the record at startPos by converting to Product object. 
This function fails if there is an error in reading the file or casting information.
------------------------------------------------------------------*/
bool checkDupProduct(const char *otherReleaseID);
int InitProduct(); // Placeholder function declaration for initializing product data
/*
InitProduct uses the global variables streampos PRODUCTFILEPOINTER and FILENAMES[3] 
to check if binary file "Products.bin" exist in the DIRECTORY to essentially check if the program is being run for the first time. 
If it does, then it returns 0, if it doesn't then the file is created. 
If file was created successfully, it returns 1 else -1. The function does not fail.
------------------------------------------------------------------*/
#endif // PRODUCT_HPP
