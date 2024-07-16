#include "Globals.hpp"

template <class T, class Q>
class Record{
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



