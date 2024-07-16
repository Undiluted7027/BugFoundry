#include "Product.hpp"
#include "Globals.hpp"
#include "drivers.cpp"
#include <cstring>
#include <iostream>

using namespace std;

Product::Product(const char *productName, const char *ReleaseDate){
    strcpy(this->productName, productName);
    this->productName[sizeof(this->productName) - 1] = '\0';
    const char *generatedID = IDGenerator<const char *>('4', 9);
    strcpy(this->releaseID, generatedID);
    this->releaseID[sizeof(this->releaseID) - 1] = '\0';
    strcpy(this->releaseDate, ReleaseDate);
    this->releaseDate[sizeof(this->releaseDate) - 1] = '\0';
}

bool Product::operator==(const Product &other) const{
    // assuming 2 products can be released on same date
    return (releaseID == other.releaseID || releaseDate == other.releaseDate);
}

void Product::DisplayDetails(ostream &out) const{
    if (strlen(releaseDate) != 8)
        out << "Error in reading Release Date : Does not have valid value" << endl;
        // RAISE ERROR
        // exit(1);
    else{
        out << "ProductName: " << productName << endl;
        out << "ReleaseID : " << releaseID << endl;
        out << "ReleaseDate : " << releaseDate << endl;
    }
}   

int ValidateProduct(const char *productName, const char *ReleaseID, const char *ReleaseDate){
    if (strlen(ReleaseDate) != 10) return -1;
    if (ReleaseDate[4] != '-' || ReleaseDate[7] != '-') return -1;
    string date = string(ReleaseDate);
    //0123 4 56 7 89
    
    string yyyy = date.substr(0, 4);
    string mm = date.substr(5, 2);
    string dd = date.substr(8, 2);

    int year, month, day;
    year = stoi(yyyy);
    month = stoi(mm);
    day = stoi(dd);

    if (year < 24 || year > 99 || month < 1 || month > 12 || day < 1 || day > 31){
        return -1;
    }
    if (month == 2){
        bool isLeapYear = (year % 4 == 0);
        if (isLeapYear && day > 29) return -1;
        if (!isLeapYear && day > 28) return -1;
    }
    //2,4,6,9,11
    if (day == 31){
        switch(month){
            case 4:
            case 6:
            case 9:
            case 11:
                return -1;
        }
    }
    
    

    //check if record already exists
    Product *dataptr = readFile<Product>(FILENAMES[0], PRODUCTFILEPOINTER);
    Product dummy(productName, ReleaseDate);

    size_t size = sizeof(dataptr) / sizeof(dataptr[0]);

    for(int i = 0; i < size; i++){
        if(dataptr[i] == dummy){
            delete[] dataptr;
            cout << "Record already exists" << endl;
            return 0;
            //break;
        }
    }
    delete[] dataptr;
    cout << "Record is Valid" << endl;

    return 1;

}

Product CreateProduct(const char* productName, const char *ReleaseID, const char *ReleaseDate){
    if (ValidateProduct(productName, ReleaseID, ReleaseDate)){
        Product newProd(productName, ReleaseDate);
        return newProd;
    }
    else{
         // RAISE EXCEPTION
        cout << "Could not create a new product!" << endl;
    }
}

void CommitProduct(const Product &product, streampos &startPos = PRODUCTFILEPOINTER, const string &FILENAME = FILENAMES[3]){
    writeRecord(FILENAME, startPos, product);
}

Product GetProductDetails(streampos &startPos = PRODUCTFILEPOINTER, const string &FILENAME = FILENAMES[3]){
    Product newprod = readRecord<Product>(FILENAME, startPos);
    return newprod;
}