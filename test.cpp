#include "Customer.cpp"

int main(){
    InitCustomer();
    cout << getFileSize("data/"+FILENAMES[0]) << endl;
    Customer dummy = Customer("", "Sanchit", "sanchit@gmail.com", "1 604-318-5470");
    writeRecord<Customer>(FILENAMES[0], CUSTOMERFILEPOINTER, dummy);
    cout << getFileSize("data/"+FILENAMES[0]) << endl;
    cout << CUSTOMERFILEPOINTER << endl;
    // Customer c = GetCustomerDetails(CUSTOMERFILEPOINTER, FILENAMES[0]);
    PrintAllCustomers(FILENAMES[0]);
    
   
    // deleteRecord(FILENAMES[0], );
    return 0;
}
