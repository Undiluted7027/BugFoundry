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
#include "Exceptions.hpp"

//---------------------------------------------------------------------------------------

class Product
{
public:

    /*
    This is the default constructor for Product class
    -----------------------------------------------------------------------------------*/
    Product(

    );
    /*
    This is a parameterized constructor for Product class. 
    Takes in all attributes as parameters to create a Product object. 
    -----------------------------------------------------------------------------------*/ 
    Product(
        const char* releaseID,      // in: the releaseID of the Product class
        const char *productName,    // in: the productName of the Product class
        const char *ReleaseDate     // in: the ReleaseDate of the Product class
    );
    
    /*
    Displays a detail of this Product class.
    -----------------------------------------------------------------------------------*/
    void DisplayDetails(
        std::ostream &out   // in: output location for Product object to be displayed on
    ) const;
    /*
    The equality operator overloader for Product class.
    -----------------------------------------------------------------------------------*/ 
    bool operator==(
        const Product &other    // in: Compare the Product object with this 'other' product object
    ) const; 

    // Gets the productName of the Product object
    const char* getProductName() const { return productName; }

    // Gets the releaseID of the Product object
    const char* getReleaseID() const { return releaseID; }

    // Gets the releaseDate of the Product object
    const char* getReleaseDate() const { return releaseDate; }

private:

    char productName[11];   // The productName of the Product class
    char releaseID[9];      // The releaseID of the Product class
    char releaseDate[11];   // The releaseDate of the Product class
};

/*
Check and validate each product object's attribute
--------------------------------------------------------------------------------------*/
int ValidateProduct(
    const char *productName,    // in: To check the format of productName of a Product object 
    const char *ReleaseID,      // in: To check the format of ReleaseID of a Product object
    const char *ReleaseDate     // in: To check the format of ReleaseDate of a product object
); 
/*
Creates a new Product object. 
Checks the correctness of each attributes for the object before creating it.
--------------------------------------------------------------------------------------*/
Product CreateProduct(
    const char *productName,    // in: The productName for the new Product object
    const char *ReleaseID,      // in: The ReleaseID for the new Product object
    const char *ReleaseDate     // in: The ReleaseDate for the new Product object
);
/*
Writes and store the Product object onto the data file.
--------------------------------------------------------------------------------------*/
void CommitProduct(
    const Product &product,                         // in: The Product object to store in the file
    std::streampos &startPos = PRODUCTFILEPOINTER,  // inout: The location (file descriptor) in data file. Indicates the location where the object will be placed
    const std::string &FILENAME = FILENAMES[3]      // in: The datafile for the Product objects
);
/*
Gets a Product object with all attribute datas from the data file
--------------------------------------------------------------------------------------*/
Product GetProductDetails(
    std::streampos startPos = PRODUCTFILEPOINTER,   // in: The location where the Product object is stored in data file.
    const std::string &FILENAME = FILENAMES[3]      // in: The datafile for the Product objects
);
/*
Checks if there is another Product object exists with the same releaseID
--------------------------------------------------------------------------------------*/
bool checkDupProduct(
    const char *otherReleaseID  // in: The releaseID to look for
);

/*
--------------------------------------------------------------------------------------*/
void PrintAllProducts(
    const std::string &FILENAME
);
/* 
Checks and initializes the data file for Product objects and file descriptor
--------------------------------------------------------------------------------------*/
int InitProduct(

);

#endif // PRODUCT_HPP
