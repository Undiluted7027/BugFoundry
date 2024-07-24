/* Product.cpp
REVISION HISTORY:
Rev. 1 - 24/07/15 Original by Seoyoung Kim
----------------------------------------------------------------------
This CPP file called Changes.cpp handles the changes of the program.
--------------------------------------------------------------------*/
#include "Product.hpp"
#include <cstring>
#include <iostream>
#include <fstream>
#include <iomanip>


Product::Product() : releaseID{0}, releaseDate{0} {
    memset(productName, 0, sizeof(productName));
}

Product::Product(const char* releaseID, const char* productName, const char* ReleaseDate) {
    safeStrCopy(this->productName, productName, sizeof(this->productName));
    safeStrCopy(this->releaseDate, ReleaseDate, sizeof(this->releaseDate));
    
    // Generate ReleaseID
    if (strlen(releaseID) != 0) {
        safeStrCopy(this->releaseID, releaseID, sizeof(this->releaseID));
    } else {
        // Assuming IDGenerator returns a char*
        char* generatedID = IDGenerator('4', 9);
        safeStrCopy(this->releaseID, generatedID, sizeof(this->releaseID));
        delete[] generatedID;
        }
}
/*
Create Product object using attrbibutes provided. 
No noticeable algorithm or data structure used.
--------------------------------------------------------------------*/
void Product::DisplayDetails(std::ostream& out) const {
    out << std::left
        << std::setw(11) << productName
        << std::setw(9) << releaseID
        << std::setw(11) << releaseDate << std::endl;
}
/*
Print the attribute details of the Product object to the console.
No noticeable algorithm or data structure used.
--------------------------------------------------------------------*/
bool Product::operator==(const Product& other) const {
    return (strcmp(releaseID, other.releaseID) == 0 || strcmp(releaseDate, other.releaseDate) == 0);
}
  /*
Checks if two Product objects are equal based on releaseID or releaseDate.
No noticeable algorithm or data structure used.
--------------------------------------------------------------------*/

int ValidateProduct(const char* productName, const char* ReleaseID, const char* ReleaseDate) {
    if (strlen(productName) == 0 || strlen(productName) > 10) {
        std::cout << "Invalid product name length" << std::endl;
        return -1;
    }  
    cout <<strlen(ReleaseID) << endl;
    if (strlen(ReleaseID) != 8) {
        std::cout << "Invalid ReleaseID length" << std::endl;
        return -1;
    }

    if (strlen(ReleaseDate) != 8) {
        std::cout << "Invalid ReleaseDate format" << std::endl;
        return -1;
    }

    // Check ReleaseDate format (YY-MM-DD)
    if (ReleaseDate[2] != '-' || ReleaseDate[5] != '-') {
        std::cout << "Invalid ReleaseDate format" << std::endl;
        return -1;
    }

    // Check for duplicate product
    std::ifstream file( FILENAMES[3], std::ios::binary);
    if (!file) {
        std::cerr << "Error: Could not open file for reading" << std::endl;
        return -1;
    }

    Product currentProduct;
    while (file.read(reinterpret_cast<char*>(&currentProduct), sizeof(Product))) {
        if (strcmp(currentProduct.getReleaseID(), ReleaseID) == 0) {
            std::cout << "Product already exists" << std::endl;
            file.close();
            return 0;
        }
    }

    file.close();
    std::cout << "Product is valid!" << std::endl;
    return 1;
}
/*
Validates that the Product object attributes are acceptable and makes sure no duplicate Product records exists.
A linear search algorithm is used to iterate through the Product records.
--------------------------------------------------------------------*/

Product CreateProduct(const char* productName, const char* ReleaseID, const char* ReleaseDate) {
    int validationResult = ValidateProduct(productName, ReleaseID, ReleaseDate);
    if (validationResult == 1) {
        return Product("", productName, ReleaseDate);
    } else if (validationResult == 0) {
        throw std::runtime_error("FailedToCreateProduct: Product with same ReleaseID already exists!");
    } else {
        throw std::runtime_error("FailedToCreateProduct: Invalid ReleaseID or ReleaseDate");
    }
}
/*
Create new Product object and also validates it.
No noticeable algorithm or data structure used.
--------------------------------------------------------------------*/
void CommitProduct(const Product& product, std::streampos& startPos, const std::string& FILENAME) {
    std::ofstream file( FILENAME, std::ios::binary | std::ios::in | std::ios::out);
    if (!file) {
        throw std::runtime_error("FileWriteFailed: Could not open file for writing");
        }
    file.seekp(startPos);
    file.write(reinterpret_cast<const char*>(&product), sizeof(Product));
    if (file.fail()) {
        throw std::runtime_error("FileWriteFailed: There was an error in writing to the file");
    }
    startPos = file.tellp();
}
/*
Writes a Product object to a specified file at a given position.
Uses the unsorted records data structure to add the Product object.
--------------------------------------------------------------------*/
Product GetProductDetails(std::streampos startPos, const std::string& FILENAME) {
    std::ifstream file( FILENAME, std::ios::binary);
    if (!file) {
        throw std::runtime_error("FileReadFailed: Could not open file for reading");
    }
    file.seekg(startPos);
    Product product;
    if (!file.read(reinterpret_cast<char*>(&product), sizeof(Product))) {
        throw std::runtime_error("FileReadFailed: There was an error in reading the file");
    }
    return product;
}
/*
Reads a Product object from a specified file at a given position and returns it.
Uses the unsorted records data structure to read the Product object.
--------------------------------------------------------------------*/

int InitProduct() {
    std::filesystem::create_directory(DIRECTORY);
    if (!std::filesystem::exists( FILENAMES[3])) {
        std::ofstream file( FILENAMES[3], std::ios::binary);
        if (!file) {
            return -1;
        }
        file.close();
        return 1;
    }
    return 0;
}