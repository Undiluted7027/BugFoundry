/* Record.hpp
REVISION HISTORY:
Rev. 1 - 24/07/04 Original by Sanchit Jain
----------------------------------------------------------------------
This module, Record.hpp, hides the implementation of the class template. 
Record.hpp keeps its high cohesion by encapsulating all possible product entries in the system.
----------------------------------------------------------------------*/
#include "Globals.hpp"

template <class T, class Q>
class Record
{
    private:
        T id;
        Q data;
    public:
        Record(T id, Q data): id(id), data(data){}

        T getId() const;
        Q getData() const;
        void setID(T id);
        void setData(Q data);
};



