/* Record.hpp
REVISION HISTORY:
Rev. 1 - 24/07/04 Original by Sanchit Jain
----------------------------------------------------------------------
This module, Record.hpp, hides the implementation of the class template. 
Record.hpp keeps its high cohesion by encapsulating all possible product entries in the system.
----------------------------------------------------------------------*/
#include "Globals.hpp"

template <class T>
class Record
{
    private:

        char *id;
        T data;

    public:
    
        Record(const char *id, T data): id(id), data(data){}

        char *getId() const;
        T getData() const;
        void setID(const char *id);
        void setData(T &data);
};



