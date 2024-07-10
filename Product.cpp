#include "Product.hpp"
#include "Globals.hpp"
#include "drivers.cpp"
#include <cstring>
#include <iostream>

using namespace std;

Product::Product(const char *ReleaseDate): Record<const int>(IDGenerator<const int>('9',9)){
    strcpy(this->ReleaseDate, ReleaseDate);
    this->ReleaseDate[sizeof(this->ReleaseDate) - 1] = '\0';
}

void Product::DisplayDetails(ostream &out) const{
    if (strlen(ReleaseDate) == 0)
        out << "Error in reading Release Date : Does not have value" << endl;
        // RAISE ERROR
        // exit(1);
    else{
        out << "ReleaseID : " << getId() << endl;
        out << "ReleaseDate : " << ReleaseDate << endl;
    }
}   

Product CreateProduct(const int &ReleaseID, const char *ReleaseDate){
    if (ValidateProduct(ReleaseID, ReleaseDate)){
        Product newProd(ReleaseDate);
        return newProd;
    }
    else{
         // RAISE EXCEPTION
        cout << "Could not create a new product!" << endl;
    }
}

void CommitProduct(const Product &product, streampos &startPos = PRODUCTFILEPOINTER, const string &FILENAME = FILENAMES[3]){
    writeFile(FILENAME, startPos, product);
}

Product GetProductDetails(streampos &startPos = PRODUCTFILEPOINTER, const string &FILENAME = FILENAMES[3]){
    Record<Product> newprodRecord = readFile<Product>(FILENAME, startPos);
    Product newprod = newprodRecord.getId();
    return newprod;
}