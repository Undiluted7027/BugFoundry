#include "Product.hpp"
#include "Globals.hpp"
#include "drivers.cpp"
#include <cstring>
#include <iostream>

using namespace std;

Product::Product(const char *ReleaseDate){
    this->ReleaseID = IDGenerator<int>('9', 8);
    strcpy(this->ReleaseDate, ReleaseDate);
    this->ReleaseDate[sizeof(this->ReleaseDate) - 1] = '\0';
}

void Product::DisplayDetails(ostream &out) const{
    if (strlen(ReleaseDate) != 8)
        out << "Error in reading Release Date : Does not have valid value" << endl;
        // RAISE ERROR
        // exit(1);
    else{
        out << "ReleaseID : " << ReleaseID << endl;
        out << "ReleaseDate : " << ReleaseDate << endl;
    }
}   

int ValidateProduct(const int &ReleaseID, const char *ReleaseDate){
    if (strlen(ReleaseDate) != 8) return -1;
    if (ReleaseDate[2] != '-' || ReleaseDate[5] != '-') return -1;
    string date = string(ReleaseDate);
    //01 2 34 5 67
    
    string yy = date.substr(0, 2);
    string mm = date.substr(3, 2);
    string dd = date.substr(6, 2);

    int year, month, day;
    year = stoi(yy);
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
    Product dummy(ReleaseDate);

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
    writeRecord(FILENAME, startPos, product);
}

Product GetProductDetails(streampos &startPos = PRODUCTFILEPOINTER, const string &FILENAME = FILENAMES[3]){
    Product newprod = readRecord<Product>(FILENAME, startPos);
    return newprod;
}