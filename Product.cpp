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
    if (strlen(ReleaseDate) == 0 || strlen(ReleaseDate) < 8)
        out << "Error in reading Release Date : Does not have valid value" << endl;
        // RAISE ERROR
        // exit(1);
    else{
        out << "ReleaseID : " << getId() << endl;
        out << "ReleaseDate : " << ReleaseDate << endl;
    }
}   

int ValidateProduct(const int &ReleaseID, const char *ReleaseDate){
    if (strlen(ReleaseDate) < 8) return -1;
    string date = string(ReleaseDate);
    //01 2 34 5 67
    string yy, mm, dd;
    yy = date.substr(0, 2);
    mm = date.substr(3, 5);
    dd = date.substr(6, 8);

    int year, month, day;
    year = stoi(yy);
    month = stoi(mm);
    day = stoi(dd);

    if (year < 24 || year > 99 || month < 1 || month > 12 || day < 1 || day > 31){
        return -1;
    }
    else {
        if (month == 2){
            if (year % 4 == 0 && day > 29) return -1;
            else if (day > 28) return -1;
        }
        //2,4,6,9,11
        if (day == 31){
            switch(month){
                case 4:
                    return -1;
                case 6:
                    return -1;
                case 9:
                    return -1;
                case 11:
                    return -1;
            };
        }
    }

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
    writeFile(FILENAME, startPos, product);
}

Product GetProductDetails(streampos &startPos = PRODUCTFILEPOINTER, const string &FILENAME = FILENAMES[3]){
    Record<Product> newprodRecord = readFile<Product>(FILENAME, startPos);
    Product newprod = newprodRecord.getId();
    return newprod;
}