/* Record.hpp
REVISION HISTORY:
Rev. 1 - 24/07/04 Original by Sanchit Jain
----------------------------------------------------------------------
This module, Record.hpp, hides the implementation of the class template. 
Record.hpp keeps its high cohesion by encapsulating all possible product entries in the system.
----------------------------------------------------------------------*/
#include "Globals.hpp"

template <class T>
class Record{
    
    private:

        char *id;       // the ID of the record
        T data;         // the data of the record of type T
    
    public:

        Record(
            const char *id,         // the id of the record
            T data                  // the data of the record of type T 
        ): id(id), data(data){}

        char *getId() const;
        /*
        getId is used to return the ID of the record
        -----------------------------------------------------------------*/
        T getData() const;
        /*
        getData is used to return the data of the record
        -----------------------------------------------------------------*/
        void setID(
            const char *id      // the id used to set a data 
        );
        /*
        setID is used to set an ID with the ID provided in function parameter
        -----------------------------------------------------------------*/
        void setData(
            T &data     // the data used to set a data
        );
        /*
        setData is used to set a data with the data provided in function parameter
        -----------------------------------------------------------------*/
};



