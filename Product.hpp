#ifndef PRODUCT_HPP
#define PRODUCT_HPP

/* Product.hpp
REVISION HISTORY:
Rev. 1 - 24/07/03 Original by Sanchit Jain
Rev. 2 - 24/07/14 Revised by Seoyoung Kim
Rev. 3 - 24/07/17 Refined based on Change and Complaint patterns
----------------------------------------------------------------------
This module, Product.hpp, hides the implementation of Product class. 
It keeps its high cohesion by encapsulating all possible product entries in the system.
----------------------------------------------------------------------*/

#include <iostream>
#include <filesystem>
#include <string>
#include "Globals.hpp"

class Product
{
public:
    Product();
    Product(const char* releaseID, const char *productName, const char *ReleaseDate);
    
    void DisplayDetails(std::ostream &out) const;
    bool operator==(const Product &other) const;

    // Getters
    const char* getProductName() const { return productName; }
    const char* getReleaseID() const { return releaseID; }
    const char* getReleaseDate() const { return releaseDate; }

private:
    char productName[11];
    char releaseID[9];
    char releaseDate[11];
};

int ValidateProduct(const char *productName, const char *ReleaseID, const char *ReleaseDate);

Product CreateProduct(const char *productName, const char *ReleaseID, const char *ReleaseDate);

void CommitProduct(
    const Product &product,
    std::streampos &startPos = PRODUCTFILEPOINTER,
    const std::string &FILENAME = FILENAMES[3]
);

Product GetProductDetails(
    std::streampos startPos = PRODUCTFILEPOINTER,
    const std::string &FILENAME = FILENAMES[3]
);

int InitProduct();

#endif // PRODUCT_HPP