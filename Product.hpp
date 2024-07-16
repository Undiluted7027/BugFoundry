#ifndef PRODUCT_HPP
#define PRODUCT_HPP

/* Product.hpp
REVISION HISTORY:
Rev. 1 - 24/07/03 Original by Sanchit Jain
Rev. 2 - 24/07/14 Revised by Seoyoung Kim
----------------------------------------------------------------------
This module, Customer.hpp, hides the implementation of Product class. 
Customer.hpp keeps its high cohesion by encapsulating all possible product entries in the system.
----------------------------------------------------------------------*/
#include <iostream>
#include <filesystem>
#include <string>
#include "Globals.hpp"

using namespace std;

/*----------------------------------------------------------------------
// Exported constants/types/variables
Tpyes:
 - Object of Class Product

----------------------------------------------------------------------*/
class Product
{
    public:
        Product(
            // int &ReleaseID,     // in
            //                     // ReleaseID of the product
            const char *ReleaseDate // in
                                // ReleaseDate of the product
        );
        /* Product(int &ReleaseID, string &ReleaseDate) creates a Product object. 
        ----------------------------------------------------------------------*/
        void DisplayDetails(
            ostream &out       // in/out
                               // ostream object to handle << operation
        ) const;
        /* void DisplayDetails(ostream &out) handles printing of Product type objects. 
        The data of each customer object is properly formatted, and indented with spaces. 
        This will come handy when displaying reports or details from the UI. 
        This function will fail if the calling Customer object is a dangling pointer.
        ----------------------------------------------------------------------*/
        bool operator==(const Product &other) const;
    private:
        char releaseID[9];
        char releaseDate[11];
};

//----------------------------------------------------------------------
int ValidateProduct(
    const char *ReleaseID,       // in
                                // ReleaseID of the product
    const char *ReleaseDate   // in
                                // ReleaseDate of the product
);
/* int validateProduct() checks if ReleaseID has 4 digits and ReleaseDate is of the form YY/MM/DD and matches the naming convention. 
If it doesn't match, it returns false otherwise it returns true. ReleaseID must not be NULL for this function to work. If same data already exists in system it returns 0, if the format is invalid it returns -1 else 1.
----------------------------------------------------------------------*/
Product CreateProduct(
    const char *ReleaseID,       // in
                                // ReleaseID of the product
    const char *ReleaseDate   // in
                                // ReleaseDate of the product
    );
/* Product CreateProduct(int &ReleaseID, string &ReleaseDate) is a function used for creating a product object. 
This function will be called from ScenarioControl.hpp. 
This function internally calls ValidateProduct(int &ReleaseID, string &ReleaseDate) to check if details of the product are valid. 
If it is invalid then it raises the following exceptions:
    - FailedToCreateProduct: Invalid ReleaseID or ReleaseDate
    - FailedToCreateProduct: Product with same ReleaseID already exists!
This function returns a Product object.
----------------------------------------------------------------------*/
void CommitProduct(
    const Product &product,                      // in
                                                // Product object to be written into Products.bin
    streampos &startPos = PRODUCTFILEPOINTER,   // in
                                                // startPos is the position in Products.bin for writing into the file (PRODUCTFILEPOINTER).
    const string &FILENAME = FILENAMES[3]       // in
                                                // FILENAME is the name of the file to read from. By default it is FILENAMES[3] which is "Products.bin"
);
/* void CommitProduct(streampos &startpos, const string &FILENAME, const Product &product) uses the global variables streampos PRODUCTFILEPOINTER, FILENAME, and a Product object to find the location to add Product record in Customers binary file. If file does not exist, a new one is created and a confirmation message is shown to the user. If a record already exists, a message is displayed to the user saying that the record already exists. Further, if file I/O fails, an exception is raised:
FileWriteFailed: There was an error in writing to the file.
Otherwise, the Product object is added into the file. 
---------------------------------------------------*/
Product GetProductDetails(
    streampos startPos = PRODUCTFILEPOINTER,// in
                                            // startPos is the position in Products.bin for reading the file (PRODUCTFILEPOINTER).
    const string &FILENAME = FILENAMES[3]   // in
                                            // FILENAME is the name of the file to read from. By default it is FILENAMES[3] which is "Products.bin"
); 
/* Product GetProductDetails(streampos startPos, const string &FILENAME) uses the global variables streampos PRODUCTFILEPOINTER and FILENAME to find the location to read records from. 
It reads the information to create a product object. 
This function will work only if there is atleast 1 record of a product in the binary file else an exception will be raised:
    FileReadFailed: There was an error in reading the file.
----------------------------------------------------------------------*/
int InitProduct(){
    filesystem::create_directory(DIRECTORY);
    if (!filesystem::exists(DIRECTORY + FILENAMES[3]))
    {
        ofstream file(DIRECTORY + FILENAMES[3], ios::binary);
        if (!file)
        {
            return -1;
        } else
        {
            return 1;
        } 
        file.close();
    } 
    else
    {
        return 0;
    }
    return -1;
}
/* int InitProduct() uses the global variables streampos PRODUCTFILEPOINTER and FILENAMES[3] to check if binary file "Products.bin" exist in the DIRECTORY to essentially check if the program is being run for the first time. If it does, then it returns 0, if it doesn't then the file is created. If file was created successfully, it returns 1 else -1. The function does not fail.
----------------------------------------------------------------------*/
#endif