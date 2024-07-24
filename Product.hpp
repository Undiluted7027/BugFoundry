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

class Product
{
public:
    Product(); // Default constructor
    Product(const char* releaseID, const char *productName, const char *ReleaseDate); // Parameterized constructor
    
    void DisplayDetails(std::ostream &out) const; // Method to display product details
    bool operator==(const Product &other) const; // Equality operator overload

    // Getters for private member variables
    const char* getProductName() const { return productName; }
    const char* getReleaseID() const { return releaseID; }
    const char* getReleaseDate() const { return releaseDate; }

private:
    char productName[11];
    char releaseID[9];
    char releaseDate[11];
};

int ValidateProduct(const char *productName, const char *ReleaseID, const char *ReleaseDate); // Function to validate product data

Product CreateProduct(const char *productName, const char *ReleaseID, const char *ReleaseDate); // Function to create a new Product object

void CommitProduct(
    const Product &product,
    std::streampos &startPos = PRODUCTFILEPOINTER,
    const std::string &FILENAME = FILENAMES[3]
); // Function to commit Product object to file

Product GetProductDetails(
    std::streampos startPos = PRODUCTFILEPOINTER,
    const std::string &FILENAME = FILENAMES[3]
); // Function to retrieve Product details from file

int InitProduct(); // Placeholder function declaration for initializing product data

#endif // PRODUCT_HPP
