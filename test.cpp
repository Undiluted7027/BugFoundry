#include "Customer.cpp"

int main(){
    Customer dummy = CreateCustomer("Sanchit", "san@gmail.com", "1 604-318-5470");
    writeRecord(FILENAMES[0], CUSTOMERFILEPOINTER, dummy);
    // deleteRecord(FILENAMES[0], );
    return 0;
}
